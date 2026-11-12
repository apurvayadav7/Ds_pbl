#include "Expression.h"

#include "Stack.h"

#include <algorithm>
#include <cmath>
#include <cctype>
#include <iomanip>
#include <limits>
#include <sstream>
#include <stdexcept>

namespace {
enum class Kind { Number, Name, Operator, Left, Right };
struct Token {
    std::string text;
    Kind kind;
};

bool isOperator(const std::string& text) {
    return text == "+" || text == "-" || text == "*" || text == "/" ||
           text == "%" || text == "^" || text == "u+" || text == "u-";
}

bool isUnary(const std::string& text) {
    return text == "u+" || text == "u-";
}

int precedence(const std::string& op) {
    if (isUnary(op)) return 4;
    if (op == "^") return 3;
    if (op == "*" || op == "/" || op == "%") return 2;
    return 1;
}

bool rightAssociative(const std::string& op) {
    return op == "^" || isUnary(op);
}

std::vector<Token> tokenize(const std::string& expression) {
    std::vector<Token> tokens;
    bool expectOperand = true;
    for (std::size_t i = 0; i < expression.size();) {
        const char c = expression[i];
        if (std::isspace(static_cast<unsigned char>(c))) {
            ++i;
            continue;
        }
        if (std::isdigit(static_cast<unsigned char>(c)) || c == '.') {
            std::size_t start = i;
            bool dot = false;
            while (i < expression.size() &&
                   (std::isdigit(static_cast<unsigned char>(expression[i])) ||
                    expression[i] == '.')) {
                if (expression[i] == '.' && dot) {
                    throw std::invalid_argument("Invalid number: more than one decimal point");
                }
                dot = dot || expression[i] == '.';
                ++i;
            }
            const std::string value = expression.substr(start, i - start);
            if (value == ".") throw std::invalid_argument("Invalid number");
            tokens.push_back({value, Kind::Number});
            expectOperand = false;
            continue;
        }
        if (std::isalpha(static_cast<unsigned char>(c)) || c == '_') {
            std::size_t start = i++;
            while (i < expression.size() &&
                   (std::isalnum(static_cast<unsigned char>(expression[i])) ||
                    expression[i] == '_')) {
                ++i;
            }
            tokens.push_back({expression.substr(start, i - start), Kind::Name});
            expectOperand = false;
            continue;
        }
        if (c == '(') {
            tokens.push_back({"(", Kind::Left});
            expectOperand = true;
            ++i;
            continue;
        }
        if (c == ')') {
            tokens.push_back({")", Kind::Right});
            expectOperand = false;
            ++i;
            continue;
        }
        const std::string op(1, c);
        if (!isOperator(op)) throw std::invalid_argument("Invalid character: " + op);
        if ((op == "+" || op == "-") && expectOperand) {
            tokens.push_back({"u" + op, Kind::Operator});
        } else {
            tokens.push_back({op, Kind::Operator});
            expectOperand = true;
        }
        ++i;
    }
    if (tokens.empty()) throw std::invalid_argument("Expression is empty");
    return tokens;
}

std::string displayToken(const std::string& token) {
    return token;
}

std::string join(const std::vector<std::string>& values, const std::string& separator) {
    std::ostringstream output;
    for (std::size_t i = 0; i < values.size(); ++i) {
        if (i != 0) output << separator;
        output << displayToken(values[i]);
    }
    return output.str();
}

std::string stackText(const std::vector<std::string>& values) {
    return values.empty() ? "[empty]" : join(values, " ");
}

std::vector<std::string> postfixTokens(const std::vector<Token>& tokens,
                                       std::vector<TraceStep>* trace) {
    ArrayStack<std::string> operators(tokens.size() + 1);
    std::vector<std::string> output;
    auto addTrace = [&](const std::string& token, const std::string& operation) {
        if (trace) {
            TraceStep step{token, operation, stackText(operators.contents()), join(output, " ")};
            trace->push_back(step);
        }
    };
    for (const Token& token : tokens) {
        if (token.kind == Kind::Number || token.kind == Kind::Name) {
            output.push_back(token.text);
            addTrace(token.text, "Add operand");
        } else if (token.kind == Kind::Left) {
            operators.push(token.text);
            addTrace(token.text, "PUSH left parenthesis");
        } else if (token.kind == Kind::Right) {
            bool foundLeft = false;
            while (!operators.isEmpty()) {
                const std::string top = operators.pop();
                if (top == "(") {
                    foundLeft = true;
                    break;
                }
                output.push_back(top);
            }
            if (!foundLeft) throw std::invalid_argument("Mismatched closing parenthesis");
            addTrace(token.text, "POP until left parenthesis");
        } else {
            while (!operators.isEmpty() && operators.peek() != "(" &&
                   (precedence(operators.peek()) > precedence(token.text) ||
                    (precedence(operators.peek()) == precedence(token.text) &&
                     !rightAssociative(token.text)))) {
                output.push_back(operators.pop());
            }
            operators.push(token.text);
            addTrace(token.text, "PUSH operator");
        }
    }
    while (!operators.isEmpty()) {
        const std::string top = operators.pop();
        if (top == "(") throw std::invalid_argument("Missing closing parenthesis");
        output.push_back(top);
    }
    return output;
}

double parseValue(const std::string& token) {
    std::size_t used = 0;
    double value = std::stod(token, &used);
    if (used != token.size()) throw std::invalid_argument("Invalid operand: " + token);
    return value;
}

double applyOperator(const std::string& op, double left, double right) {
    if (op == "+") return left + right;
    if (op == "-") return left - right;
    if (op == "*") return left * right;
    if (op == "/") {
        if (right == 0.0) throw std::domain_error("Division by zero");
        return left / right;
    }
    if (op == "%") {
        if (right == 0.0) throw std::domain_error("Modulo by zero");
        return std::fmod(left, right);
    }
    if (op == "^") return std::pow(left, right);
    throw std::invalid_argument("Unknown operator: " + op);
}

EvaluationResult evaluateTokens(const std::vector<std::string>& tokens, bool prefix) {
    ArrayStack<double> values(tokens.size() + 1);
    std::vector<TraceStep> trace;
    auto addTrace = [&](const std::string& token, const std::string& operation, double result) {
        std::vector<std::string> contents;
        for (double value : values.contents()) contents.push_back(formatNumber(value));
        trace.push_back({token, operation, stackText(contents), formatNumber(result)});
    };
    auto process = [&](const std::string& token) {
        if (!isOperator(token)) {
            const double value = parseValue(token);
            values.push(value);
            addTrace(token, "PUSH operand", value);
            return;
        }
        if (isUnary(token)) {
            if (values.isEmpty()) throw std::invalid_argument("Missing operand for unary operator");
            const double value = values.pop();
            const double result = token == "u-" ? -value : value;
            values.push(result);
            addTrace(displayToken(token), "POP, apply unary operator, PUSH", result);
            return;
        }
        if (values.size() < 2) throw std::invalid_argument("Missing operand for operator");
        const double first = values.pop();
        const double second = values.pop();
        const double left = prefix ? first : second;
        const double right = prefix ? second : first;
        const double result = applyOperator(token, left, right);
        values.push(result);
        addTrace(token, "POP two operands, calculate, PUSH", result);
    };
    if (prefix) {
        for (auto it = tokens.rbegin(); it != tokens.rend(); ++it) process(*it);
    } else {
        for (const std::string& token : tokens) process(token);
    }
    if (values.size() != 1) throw std::invalid_argument("Malformed expression: extra operands");
    return {true, values.peek(), "", trace};
}
}  // namespace

std::string formatNumber(double value) {
    if (std::abs(value) < std::numeric_limits<double>::epsilon()) value = 0.0;
    std::ostringstream output;
    output << std::setprecision(12) << value;
    return output.str();
}

ConversionResult infixToPostfix(const std::string& expression) {
    std::vector<TraceStep> trace;
    const auto output = postfixTokens(tokenize(expression), &trace);
    return {join(output, " "), trace};
}

ConversionResult infixToPrefix(const std::string& expression) {
    const auto tokens = tokenize(expression);
    std::vector<std::string> postfix;
    ArrayStack<std::string> operators(tokens.size() + 1);
    std::vector<Token> reversed;
    for (auto it = tokens.rbegin(); it != tokens.rend(); ++it) {
        if (it->kind == Kind::Left) reversed.push_back({")", Kind::Right});
        else if (it->kind == Kind::Right) reversed.push_back({"(", Kind::Left});
        else reversed.push_back(*it);
    }
    postfix = postfixTokens(reversed, nullptr);
    std::reverse(postfix.begin(), postfix.end());
    std::vector<std::string> output;
    for (const auto& token : postfix) {
        output.push_back(token);
    }
    return {join(output, " "), {}};
}

EvaluationResult evaluatePostfix(const std::string& expression) {
    try {
        std::vector<std::string> tokens;
        std::istringstream input(expression);
        std::string token;
        while (input >> token) tokens.push_back(token);
        if (tokens.empty()) {
            throw std::invalid_argument("Expression is empty");
        }
        return evaluateTokens(tokens, false);
    } catch (const std::exception& error) {
        return {false, 0.0, error.what(), {}};
    }
}

EvaluationResult evaluatePrefix(const std::string& expression) {
    try {
        std::istringstream input(expression);
        std::vector<std::string> tokens;
        std::string token;
        while (input >> token) tokens.push_back(token);
        if (tokens.empty()) throw std::invalid_argument("Expression is empty");
        return evaluateTokens(tokens, true);
    } catch (const std::exception& error) {
        return {false, 0.0, error.what(), {}};
    }
}

EvaluationResult evaluateInfix(const std::string& expression) {
    try {
        const auto conversion = infixToPostfix(expression);
        EvaluationResult result = evaluatePostfix(conversion.expression);
        result.trace.insert(result.trace.begin(), conversion.trace.begin(), conversion.trace.end());
        return result;
    } catch (const std::exception& error) {
        return {false, 0.0, error.what(), {}};
    }
}
