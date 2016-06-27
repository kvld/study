(defn operation [func args] (fn [vars] (func (map (fn [a] (a vars)) args))))

(defn add [& args] (operation (fn [a] (reduce + a)) args))

(defn subtract [& args] (operation (fn [a] (reduce - a)) args))

(defn multiply [& args] (operation (fn [a] (reduce * a)) args))

(defn divide [& args] (operation (fn [a] (try (reduce / a) (catch Exception e (Double/POSITIVE_INFINITY)))) args))

(defn negate [a] (fn [vars] (- (a vars))))

(defn sin [a] (fn [vars] (Math/sin (a vars))))

(defn cos [a] (fn [vars] (Math/cos (a vars))))

(defn constant [a] (fn [vars] (double a)))

(defn variable [a] (fn [vars] (double (get vars a))))

(def binary-operations {"+" add "-" subtract "*" multiply "/" divide})
(def unary-operations {"negate" negate "sin" sin "cos" cos})

(defn parseFunction [expression]
    (cond
      (string? expression) (parseFunction (read-string expression))
      (seq? expression)
      (let [expr (str (first expression))]
        (cond
          (contains? binary-operations expr) (apply (get binary-operations expr) (map parseFunction (rest expression)))
          (contains? unary-operations expr) ((get unary-operations expr) (parseFunction (second expression)))))
      (number? expression) (constant expression)
      (symbol? expression) (variable (str expression))))