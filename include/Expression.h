#pragma once

#include <string>
#include <vector>

#include "Parentheses.h"

struct ConversionResult {
    std::string expression;
    std::vector<TraceStep> trace;
};

struct EvaluationResult {
    bool success;
    double value = 0.0;
    std::string message;
    std::vector<TraceStep> trace;
};

ConversionResult infixToPostfix(const std::string& expression);
ConversionResult infixToPrefix(const std::string& expression);
EvaluationResult evaluatePostfix(const std::string& expression);
EvaluationResult evaluatePrefix(const std::string& expression);
EvaluationResult evaluateInfix(const std::string& expression);
std::string formatNumber(double value);
