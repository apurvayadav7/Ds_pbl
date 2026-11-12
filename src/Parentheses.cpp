#include "Parentheses.h"

#include "Stack.h"

#include <sstream>
#include <stdexcept>

namespace {
bool isOpening(char c) { return c == '(' || c == '[' || c == '{'; }
bool matches(char opening, char closing) {
    return (opening == '(' && closing == ')') ||
           (opening == '[' && closing == ']') ||
           (opening == '{' && closing == '}');
}
std::string stackText(const std::vector<char>& values) {
    if (values.empty()) return "[empty]";
    std::ostringstream output;
    for (char value : values) output << value << ' ';
    return output.str();
}
}

ParenthesesResult checkParentheses(const std::string& expression) {
    ArrayStack<char> stack(expression.size() + 1);
    std::vector<TraceStep> trace;
    for (char token : expression) {
        if (!isOpening(token) && token != ')' && token != ']' && token != '}') continue;
        if (isOpening(token)) {
            stack.push(token);
            trace.push_back({std::string(1, token), "PUSH opening bracket",
                             stackText(stack.contents()), ""});
        } else {
            if (stack.isEmpty()) {
                return {false, "Extra closing bracket: " + std::string(1, token), trace};
            }
            const char opening = stack.pop();
            if (!matches(opening, token)) {
                return {false, "Mismatched brackets: " + std::string(1, opening) +
                                   " and " + std::string(1, token), trace};
            }
            trace.push_back({std::string(1, token), "POP matching opening bracket",
                             stackText(stack.contents()), ""});
        }
    }
    if (!stack.isEmpty()) {
        return {false, "Missing closing bracket for " + std::string(1, stack.peek()), trace};
    }
    return {true, "BALANCED", trace};
}
