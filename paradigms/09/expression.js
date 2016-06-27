var binaryOperation = function(f) {
    return function(a, b) {
        return function() {
            return f(a.apply(null, arguments), b.apply(null, arguments));
        }
    }
}

var unaryOperation = function(f) {
    return function(a) {
        return function() {
            return f(a.apply(null, arguments));
        }
    }
}

function cnst(a) {
    return function() {
        return a;
    }
} 

var variables = ['x', 'y', 'z']
function variable(a) {
    return function() {
        for (i = 0; i < arguments.length; i++) {
            if (a == variables[i]) {
                return arguments[i];
            }
        }
    }
}

var add      = binaryOperation(function(a, b) { return a + b; });
var subtract = binaryOperation(function(a, b) { return a - b; });
var divide   = binaryOperation(function(a, b) { return a / b; });
var multiply = binaryOperation(function(a, b) { return a * b; });
var mod      = binaryOperation(function(a, b) { return a % b; });
var power    = binaryOperation(Math.pow);
var abs      = unaryOperation(Math.abs);
var negate   = unaryOperation(function(a) { return -a; });
var log      = unaryOperation(Math.log)


var binaryOperations = {
    "+" : add, 
    "-" : subtract, 
    "/" : divide,
    "*" : multiply,
    "%" : mod,
    "**" : power
};
var unaryOperations = {
    "negate" : negate,
    "abs" : abs,
    "log" : log
};

function isBinaryOperation(token) {
    return (token in binaryOperations);
}

function isUnaryOperation(token) {
    return (token in unaryOperations);
}

function parse(s) {
    s += ' ';
    var token = '';
    var stack = [];
    for (i = 0; i < s.length; i++) {
        if (s[i] != ' ') {
            token += s[i];
        } else {
            if (token == 'x' || token == 'y' || token == 'z') {
                stack.push(variable(token));
            } else if ((token[0] >= '0' && token[0] <= '9') || (token[0] == '-' && token.length > 1)) {
                stack.push(cnst(Number(token)));
            } else if (isUnaryOperation(token)) {
                var a = stack.pop();
                stack.push(unaryOperations[token](a));
            } else if (token in binaryOperations) {
                var a = stack.pop();
                var b = stack.pop();
                stack.push(binaryOperations[token](b, a));
            } 
            token = '';
        }
    }
    return stack.pop();
}         

    
