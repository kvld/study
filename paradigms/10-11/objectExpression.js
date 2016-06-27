"use strict";

// Const
var Const = function(a) {
    this.a         = a;
    this.isSimple  = true;
}
Const.isConst              = function(obj) { return (obj instanceof Const); }
Const.prototype.equals     = function(obj) { return (Const.isConst(obj) && obj.a == this.a); }
Const.prototype.equalValue = function(i)   { return (this.a == i); } 
Const.prototype.evaluate   = function()    { return this.a; }
Const.prototype.toString   = function()    { return this.a.toString(); }
Const.prototype.diff       = function(x)   { return new Const(0); }
Const.prototype.simplify   = function()    { return this; }
Const.prototype.prefix     = Const.prototype.toString;

// Variable
var Variable = function(a) {
    this.a = a;
    this.isSimple = true;
}
Variable.prototype.evaluate = function() {
    for (var i = 0; i < arguments.length; i++) {
        if (this.a == variables[i]) {
            return arguments[i];
        }
    }
}
Variable.prototype.toString = function()  { return this.a; }
Variable.prototype.diff     = function(a) { return (a == this.a ? new Const(1) : new Const(0)); }
Variable.prototype.simplify = function()  { return new Variable(this.a); }
Variable.prototype.prefix   = Variable.prototype.toString;


// BinaryOperation
var createBinaryOperation = function() {
    var Operation = function(a, b) { BinaryOperation.call(this, a, b); }
    Operation.prototype = new BinaryOperation();
    return Operation;
}
var BinaryOperation = function(a, b) {
    this.a        = a;
    this.b        = b; 
    this.isSimple = false;
}
BinaryOperation.prototype.evaluate = function() {
    return this.operation(this.a.evaluate.apply(this.a, arguments), this.b.evaluate.apply(this.b, arguments));
}
BinaryOperation.prototype.toString  = function(a, b) { 
    var result = this.a.toString() + " " + this.b.toString() + " " + this.symbol;
    return result;
}
BinaryOperation.prototype.simplify = function() {
    if (this.isSimple) {
        return this;
    }
    // const ? const
    if (Const.isConst(this.a) && Const.isConst(this.b)) {
        return new Const(this.operation(this.a.evaluate(), this.b.evaluate()));
    }
    // other
    for (var rule in this.simplifyRules) {
        if (this.simplifyRules[rule][0](this.a, this.b)) {
            return this.simplifyRules[rule][1](this.a, this.b);
        }
    }
    var result = new binaryOperations[this.symbol](this.a.simplify(), this.b.simplify());
    if (this.a.isSimple && this.b.isSimple) {
        result.isSimple = true;
    }
    return result.simplify();
}
BinaryOperation.prototype.prefix = function() {
    var result = "(" + this.symbol + " " + this.a.prefix() + " " + this.b.prefix() + ")";
    return result;
}


// UnaryOperation
var createUnaryOperation = function() {
    var Operation = function(a, b) { UnaryOperation.call(this, a); }
    Operation.prototype = new UnaryOperation();
    return Operation;
}
var UnaryOperation = function(a, c) {
    this.a = a;
    this.name = c;
    this.isSimple = false;
}
UnaryOperation.prototype.evaluate = function() {
    return this.operation(this.a.evaluate.apply(this.a, arguments));
}
UnaryOperation.prototype.toString  = function() {
    var result = this.a.toString() + " " + this.symbol;
    return result;
}
UnaryOperation.prototype.simplify = function() {
    var result = new unaryOperations[this.symbol](this.a.simplify());
    for (var rule in this.simplifyRules) {
        if (this.simplifyRules[rule][0](this.a)) {
            return this.simplifyRules[rule][1](this.a);
        }
    }
    result.isSimple = true;
    return result;
}
UnaryOperation.prototype.prefix = function() {
    var result = "(" + this.symbol + " " + this.a.prefix() + ")";
    return result;
}

// Add
var Add                 = createBinaryOperation();
Add.prototype.symbol    = "+";
Add.prototype.operation = function(a, b) { return a + b; }
Add.prototype.diff      = function(x) { 
    return new Add(this.a.diff(x), this.b.diff(x)); 
}
Add.prototype.simplifyRules   = [
    [
        function(a, b) { return (Const.isConst(b) && b.equalValue(0)); }, 
        function(a, b) { return a.simplify(); }
    ],
    [
        function(a, b) { return (Const.isConst(a) && a.equalValue(0)); },
        function(a, b) { return b.simplify(); }
    ]
]

// Subtract
var Subtract                 = createBinaryOperation();
Subtract.prototype.symbol    = "-";
Subtract.prototype.operation = function(a, b) { return a - b; }
Subtract.prototype.diff      = function(x) { 
    return new Subtract(this.a.diff(x), this.b.diff(x)); 
}
Subtract.prototype.simplifyRules  = [
    [
        function(a, b) { return (Const.isConst(b) && b.equalValue(0)); }, 
        function(a, b) { return a.simplify(); }
    ],
]


// Multiply
var Multiply                 = createBinaryOperation();
Multiply.prototype.symbol    = "*";
Multiply.prototype.operation = function(a, b) { return a * b; }
Multiply.prototype.diff      = function(x) { 
    return new Add(new Multiply(this.a.diff(x), this.b), new Multiply(this.a, this.b.diff(x))); 
}
Multiply.prototype.simplifyRules  =  [
    [
        function(a, b) { return ((Const.isConst(a) && a.equalValue(0)) || (Const.isConst(b) && b.equalValue(0))); }, 
        function(a, b) { return new Const(0); }
    ],
    [
        function(a, b) { return (Const.isConst(a) && a.equalValue(1)); }, 
        function(a, b) { return b.simplify(); }
    ],
    [
        function(a, b) { return (Const.isConst(b) && b.equalValue(1)); }, 
        function(a, b) { return a.simplify(); }
    ],
]


// Divide
var Divide                 = createBinaryOperation();
Divide.prototype.symbol    = "/";
Divide.prototype.operation = function(a, b) { return a / b; }
Divide.prototype.diff      = function(x) { 
    return new Divide(new Subtract(new Multiply(this.a.diff(x), this.b), new Multiply(this.a, this.b.diff(x))), new Multiply(this.b, this.b)); 
} 
Divide.prototype.simplifyRules  =  [
    [
        function(a, b) { return (Const.isConst(a) && a.equalValue(0)); }, 
        function(a, b) { return new Const(0 / 1); }
    ],
    [
        function(a, b) { return (Const.isConst(b) && b.equalValue(0)); }, 
        function(a, b) { return new Const(1 / 0); }
    ],
    [
        function(a, b) { return (Const.isConst(b) && b.equalsValue(1)); }, 
        function(a, b) { return a.simplify(); }
    ],
]

// Negate
var Negate                 = createUnaryOperation();
Negate.prototype.symbol    = "negate";
Negate.prototype.operation = function(a) { return -a; }
Negate.prototype.diff      = function(x) {
    return new Multiply(new Const(-1), this.a).diff(x);
}

// Sin
var Sin                 = createUnaryOperation();
Sin.prototype.symbol    = "sin";
Sin.prototype.operation = Math.sin
Sin.prototype.diff      = function(x) {
    return new Multiply(this.a.diff(x), new Cos(this.a));
}
Sin.prototype.simplifyRules = [
    [
        function(a, b) { return (Const.isConst(a) && a.equalsValue(0)); },
        function(a, b) { return new Const(1); }
    ]
]

// Cos
var Cos                 = createUnaryOperation();
Cos.prototype.symbol    = "cos";
Cos.prototype.operation = Math.cos
Cos.prototype.diff      = function(x) {
    return new Multiply(this.a.diff(x), new Multiply(new Const(-1), new Sin(this.a)));
}
Cos.prototype.simplifyRules = [
    [
        function(a, b) { return (Const.isConst(a) && a.equalValue(0)); },
        function(a, b) { return new Const(0); }
    ]
]

// Atan
var ArcTan                 = createUnaryOperation();
ArcTan.prototype.symbol    = "atan";
ArcTan.prototype.operation = Math.atan
ArcTan.prototype.diff      = function(x) {
    return new Multiply(new Divide(new Const(1), new Add(new Const(1), new Multiply(this.a, this.a))), this.a.diff(x));
}

// Exp
var Exp                 = createUnaryOperation();
Exp.prototype.symbol    = "exp";
Exp.prototype.operation = Math.exp
Exp.prototype.diff      = function(x) {
    return new Multiply(this, this.a.diff(x));
}

//
var variables = ['x', 'y', 'z'];
var binaryOperations = {
    "+" : Add, 
    "-" : Subtract,
    "/" : Divide,
    "*" : Multiply,
};

var unaryOperations = {
    "negate" : Negate,
    "sin"    : Sin,
    "cos"    : Cos,
    "atan"   : ArcTan,
    "exp"    : Exp
};

function parse(s) {
    s += ' ';
    var token = '';
    var stack = [];
    for (var i = 0; i < s.length; i++) {
        if (s[i] != ' ') {
            token += s[i];
            continue;
        } else if (variables.indexOf(token) != -1) {
            stack.push(new Variable(token));
        } else if ((token[0] >= '0' && token[0] <= '9') || (token[0] == '-' && token.length > 1)) {
            stack.push(new Const(Number(token)));
        } else if (token in unaryOperations || token in binaryOperations) {
            processOperation(stack, token, true);
        }
        token = '';
    }
    return stack.pop();
}     

function processOperation(stack, symbol, reverse) {
    var b = stack.pop();
    if (b == undefined) {
        throw new Error("Expected first argument for operation '" + symbol + "'.");
    }
    if (symbol in binaryOperations) {
        var a = stack.pop();
        if (a == undefined) {
            throw new Error("Expected second arguments for operation '" + symbol + "'.")
        }
        if (!reverse) {
            stack.push(new binaryOperations[symbol](b, a));
        } else {
            stack.push(new binaryOperations[symbol](a, b));
        }
    } else if (symbol in unaryOperations) {
        stack.push(new unaryOperations[symbol](b));
    }
}

function isNumber(s) {
    if (!s) {
        return false;
    }
    for (var i = 0; i < s.length; i++) {
        if (!(s[i] >= '0' && s[i] <= '9')) {
            if (i == 0 && s[i] == '-' && s != '-') {
                continue;
            }
            return false;
        }
    }
    return true;
}

function parsePrefix(s) {  
    if (s.length == 0) {
        throw new Error('Empty expression.');
    } 
    s = ' ' + s;
    var token = '';
    var stack = [];
    var opStack = [];
    var balance = 0;
    var lastOp = '';
    for (var i = s.length - 1; i >= 0; i--) {
        if (s[i] != ' ' && s[i] != '(' && s[i] != ')') {
            token = s[i] + token;
            continue;
        } else if (s[i] == ')') {
            opStack.push(s[i]);
            balance++;
        } else if (s[i] == '(') {
            balance--;
            if (balance < 0) {
                throw new Error("Expected '(' at pos " + i + ".");
            }
            while (opStack[opStack.length - 1] != ')') {
                lastOp = token;
                processOperation(stack, opStack.pop());
            }
        } 
        if (variables.indexOf(token) != -1) {
            stack.push(new Variable(token));
        } else if (isNumber(token)) {
            stack.push(new Const(Number(token)));
        } else if (token in unaryOperations || token in binaryOperations) {
            lastOp = token;
            processOperation(stack, token, false);
        } else if (token) {
            throw new Error("Bad token '" + token + "' at pos " + (s.length - i) + ".");
        }
        token = '';
    }
    if (balance != 0) {
        throw new Error("Expected '(' at pos 1!");
    }
    if (stack.length == 1) {
        return stack.pop();
    } else {
        throw new Error("Wrong number arguments for operation '" + lastOp + "'.");
    }
}     
