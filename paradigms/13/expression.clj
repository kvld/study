;===========

(defn constructor [ctor prototype]
  (fn [& args] (apply (partial ctor {:prototype prototype}) args)))

(defn proto-get [obj key]
  (cond
    (contains? obj key) (obj key)
    (contains? obj :prototype) (proto-get (:prototype obj) key)))

(defn proto-call [obj key & args]
  (apply (proto-get obj key) (cons obj args)))

(defn method [key]
  (fn [obj & args] (apply (partial proto-call obj key) args)))

(defn field [key]
  (fn [obj] (proto-get obj key)))

;=== Methods
(defn evaluate [expression vars] ((method :_evaluate) expression vars))
(defn diff [expression var] ((method :_diff) expression var))
(defn toString [expression] ((method :_toString) expression))

(def Add)
(def Subtract)
(def Multiply)
(def Divide)
(def Negate)
(def Sin)
(def Cos)

;=== Constant

(def Constant)

(def ConstProto
  {:_evaluate (fn [this vars] ((field :a) this))
   :_diff (fn [this var] (Constant 0.0))
   :_toString (fn [this] [this] (str (double ((field :a) this))))
   })

(defn ConstantConstruct [this a] (assoc
                                   this :a a))

(def Constant (constructor ConstantConstruct ConstProto))

;=== Variable

(def VarProto
  {:_evaluate (fn [this vars] (get vars ((field :a) this)))
   :_diff (fn [this var] (cond
                           (= var ((field :a) this)) (Constant 1.0)
                           :else (Constant 0.0)))
   :_toString (fn [this] ((field :a) this))
   })

(defn VarConstruct [this a] (assoc
                              this :a a))

(def Variable (constructor VarConstruct VarProto))

;=== BinaryOperation

(defn operands [arg] ((field :_args) arg))

(def BinaryOperationProto
  {:_evaluate (fn [this vars] ((method :_appfn) this
                                (map (fn [a] (evaluate a vars)) (operands this))))
   :_toString (fn [this] (clojure.string/join " " ["(" ((field :_sign) this) (clojure.string/join " " (map (fn [a] (toString a)) (operands this))) ")"]))
    })

(defn BinaryOperationConstruct [this args sign] (assoc
                                                  this :_args
                                                  args :_sign sign))

(def BinaryOperation (constructor BinaryOperationConstruct BinaryOperationProto))

;=== UnaryOperation

(def UnaryOperationProto
  {:_evaluate (fn [this vars] ((method :_appfn) this
                                (evaluate (operands this) vars)))
   :_toString (fn [this] (clojure.string/join " " ["(" ((field :_sign) this) (toString (operands this)) ")"]))
   })

(defn UnaryOperationConstruct [this arg sign] (assoc this :_args arg :_sign sign))

(def UnaryOperation (constructor UnaryOperationConstruct UnaryOperationProto))

;=== Add

(defn AddConstruct [this & args]
  (BinaryOperationConstruct this args "+"))

(def AddProto
  (assoc BinaryOperationProto
    :_appfn (fn [this args] (reduce + args))
    :_diff (fn [this var] (apply Add (map (fn [a] (diff a var)) (operands this))))))

(def Add (constructor AddConstruct AddProto))

;=== Subtract

(defn SubtractConstruct [this & args]
  (BinaryOperationConstruct this args "-"))

(def SubtractProto
  (assoc BinaryOperationProto
    :_appfn (fn [this args] (reduce - args))
    :_diff (fn [this var] (apply Subtract (map (fn [a] (diff a var)) (operands this))))))

(def Subtract (constructor SubtractConstruct SubtractProto))

;=== Mulitply

(defn MultiplyConstruct [this & args]
  (BinaryOperationConstruct this args "*"))

(def MultiplyProto
  (assoc BinaryOperationProto
    :_appfn (fn [this args] (reduce * args))
    :_diff (fn [this var]
            (let [u (first (operands this))
                  v (cond
                      (empty? (rest (operands this))) (Constant 1.0)
                      :else (apply Multiply (rest (operands this))))]
              (Add
                (Multiply (diff u var) v)
                (Multiply u (diff v var)))))))

(def Multiply (constructor MultiplyConstruct MultiplyProto))

;=== Divide

(defn DivideConstruct [this & args]
  (BinaryOperationConstruct this args "+"))

(def DivideProto
  (assoc BinaryOperationProto
    :_appfn (^double fn [this args] (reduce / args))
    :_diff (fn [this var]
             (let [u (first (operands this))
                   v (cond
                       (empty? (rest (operands this))) (Constant 1.0)
                       :else (apply Divide (rest (operands this))))]
               (Divide
                 (Subtract
                   (Multiply (diff u var) v)
                   (Multiply u (diff v var)))
                 (Multiply v v))))))

(def Divide (constructor DivideConstruct DivideProto))

;=== Negate

(defn NegateConstruct [this args]
  (UnaryOperationConstruct this args "negate"))

(def NegateProto
  (assoc UnaryOperationProto
    :_appfn (fn [this arg] (- arg))
    :_diff (fn [this var]
             (Negate (diff (operands this) var)))))

(def Negate (constructor NegateConstruct NegateProto))

;=== Sin

(defn SinConstruct [this args]
  (UnaryOperationConstruct this args "sin"))

(def SinProto
  (assoc UnaryOperationProto
    :_appfn (fn [this arg] (Math/sin arg))
    :_diff (fn [this var]
            (Multiply
              (Cos (operands this))
              (diff (operands this) var)))))

(def Sin (constructor SinConstruct SinProto))

;=== Cos

(defn CosConstruct [this args]
  (UnaryOperationConstruct this args "cos"))

(def CosProto
  (assoc UnaryOperationProto
    :_appfn (fn [this arg] (Math/cos arg))
    :_diff (fn [this var]
             (Multiply
               (Negate
                 (Sin (operands this)))
               (diff (operands this) var)))))

(def Cos (constructor CosConstruct CosProto))

;=== Parser

(defn parseObject [expression]
  (let [operations {"+" Add "-" Subtract "*" Multiply "/" Divide "negate" Negate "sin" Sin "cos" Cos}]
    (cond
      (string? expression) (parseObject (read-string expression))
      (seq? expression)
      (let [exp (str (first expression))]
        (cond
          (contains? operations exp) (apply (get operations exp) (map parseObject (rest expression)))))
      (number? expression) (Constant expression)
      (symbol? expression) (Variable (str expression)))))

;(println expr)
;(def expr (evaluate (Divide (Constant 1) (Constant 2) (Constant 3)) {"x" 0}))
;(println (toString expr))
;(println expr)
;(println (evaluate expr {"x" 0}))
;(println (diff (Multiply (Constant 4.0) (Constant 1.0)) "z"))