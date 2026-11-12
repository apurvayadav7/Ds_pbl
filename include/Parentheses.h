#pragma once

#include <string>
#include <vector>

struct TraceStep {
    std::string token;
    std::string operation;
    std::string stack;
    std::string result;
};

struct ParenthesesResult {
    bool balanced;
    std::string message;
    std::vector<TraceStep> trace;
};

ParenthesesResult checkParentheses(const std::string& expression);
