#include "Expression.h"
#include "Parentheses.h"
#include "Stack.h"

#include <cmath>
#include <iostream>
#include <stdexcept>

namespace {
int failures = 0;
void expect(bool condition, const char* message) {
    if (!condition) { std::cerr << "FAIL: " << message << '\n'; ++failures; }
}
}

int main() {
    ArrayStack<int> array(2);
    array.push(1); array.push(2);
    expect(array.peek() == 2 && array.isFull(), "array push/peek/full");
    expect(array.pop() == 2 && array.pop() == 1 && array.isEmpty(), "array pop/empty");
    try { array.pop(); expect(false, "array underflow"); } catch (const std::underflow_error&) {}
    LinkedStack<int> linked;
    linked.push(4); linked.push(5);
    expect(linked.pop() == 5 && linked.peek() == 4, "linked stack LIFO");

    expect(checkParentheses("{[(())]}").balanced, "balanced parentheses");
    expect(!checkParentheses("([)]").balanced, "mismatched parentheses");
    expect(!checkParentheses("(a+b").balanced, "missing parenthesis");

    expect(infixToPostfix("A+B*C").expression == "A B C * +", "postfix conversion");
    expect(infixToPrefix("A+B*C").expression == "+ A * B C", "prefix conversion");
    expect(evaluatePostfix("5 3 2 * +").success &&
           std::abs(evaluatePostfix("5 3 2 * +").value - 11.0) < 1e-9, "postfix evaluation");
    expect(evaluatePrefix("+ 5 * 3 2").success &&
           std::abs(evaluatePrefix("+ 5 * 3 2").value - 11.0) < 1e-9, "prefix evaluation");
    expect(evaluateInfix("(5+3)*2").success &&
           std::abs(evaluateInfix("(5+3)*2").value - 16.0) < 1e-9, "infix evaluation");
    expect(evaluateInfix("2^3").success &&
           std::abs(evaluateInfix("2^3").value - 8.0) < 1e-9, "exponentiation");
    expect(evaluateInfix("-2.5*4").success &&
           std::abs(evaluateInfix("-2.5*4").value + 10.0) < 1e-9, "negative decimal");
    expect(!evaluateInfix("10/0").success, "division by zero");
    std::cout << (failures == 0 ? "All tests passed.\n" : "Tests failed: " + std::to_string(failures) + "\n");
    return failures == 0 ? 0 : 1;
}
