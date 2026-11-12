#include "Expression.h"
#include "Parentheses.h"
#include "Stack.h"

#include <cmath>
#include <iomanip>
#include <iostream>
#include <limits>
#include <sstream>
#include <string>

namespace {
void printBanner() {
    std::cout << "\n===============================================\n"
              << "  EXPRESSION EVALUATOR & STACK DEMONSTRATOR\n"
              << "===============================================\n";
}

void printTrace(const std::vector<TraceStep>& trace) {
    if (trace.empty()) return;
    std::cout << "\nStep-by-step trace:\n"
              << std::left << std::setw(14) << "Token"
              << std::setw(34) << "Operation"
              << std::setw(24) << "Stack"
              << "Result\n";
    std::cout << std::string(86, '-') << '\n';
    for (const auto& step : trace) {
        std::cout << std::left << std::setw(14) << step.token
                  << std::setw(34) << step.operation
                  << std::setw(24) << step.stack
                  << step.result << '\n';
    }
}

int readChoice() {
    int choice;
    if (!(std::cin >> choice)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return -1;
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return choice;
}

std::string readExpression() {
    std::string expression;
    std::cout << "Enter expression: ";
    std::getline(std::cin, expression);
    return expression;
}

void conversion(bool prefix) {
    try {
        const auto result = prefix ? infixToPrefix(readExpression()) : infixToPostfix(readExpression());
        std::cout << (prefix ? "Prefix: " : "Postfix: ") << result.expression << '\n';
        printTrace(result.trace);
    } catch (const std::exception& error) {
        std::cout << "Error: " << error.what() << '\n';
    }
}

void evaluation(bool prefix) {
    const auto result = prefix ? evaluatePrefix(readExpression()) : evaluatePostfix(readExpression());
    if (!result.success) std::cout << "Error: " << result.message << '\n';
    else {
        std::cout << "Result: " << formatNumber(result.value) << '\n';
        printTrace(result.trace);
    }
}

void stackDemo(bool linked) {
    std::cout << "\nUsing " << (linked ? "linked-list" : "array-based") << " stack.\n"
              << "Commands: push <value>, pop, peek, display, empty, full, back\n";
    if (linked) {
        LinkedStack<std::string> stack;
        std::string line;
        while (std::cout << "> " && std::getline(std::cin, line) && line != "back") {
            std::istringstream input(line);
            std::string command, value;
            input >> command >> value;
            try {
                if (command == "push") stack.push(value);
                else if (command == "pop") std::cout << "POP: " << stack.pop() << '\n';
                else if (command == "peek") std::cout << "TOP: " << stack.peek() << '\n';
                else if (command == "display") { for (const auto& item : stack.contents()) std::cout << item << ' '; std::cout << '\n'; }
                else if (command == "empty") std::cout << (stack.isEmpty() ? "YES\n" : "NO\n");
                else if (command == "full") std::cout << "NO (dynamic capacity)\n";
                else std::cout << "Unknown command\n";
            } catch (const std::exception& error) { std::cout << "Error: " << error.what() << '\n'; }
        }
    } else {
        ArrayStack<std::string> stack(5);
        std::string line;
        while (std::cout << "> " && std::getline(std::cin, line) && line != "back") {
            std::istringstream input(line);
            std::string command, value;
            input >> command >> value;
            try {
                if (command == "push") stack.push(value);
                else if (command == "pop") std::cout << "POP: " << stack.pop() << '\n';
                else if (command == "peek") std::cout << "TOP: " << stack.peek() << '\n';
                else if (command == "display") { for (const auto& item : stack.contents()) std::cout << item << ' '; std::cout << '\n'; }
                else if (command == "empty") std::cout << (stack.isEmpty() ? "YES\n" : "NO\n");
                else if (command == "full") std::cout << (stack.isFull() ? "YES\n" : "NO\n");
                else std::cout << "Unknown command\n";
            } catch (const std::exception& error) { std::cout << "Error: " << error.what() << '\n'; }
        }
    }
}
}

int main() {
    printBanner();
    bool linked = false;
    while (true) {
        std::cout << "\n1. Balanced Parentheses Checker\n2. Infix to Postfix\n"
                  << "3. Infix to Prefix\n4. Postfix Evaluation\n5. Prefix Evaluation\n"
                  << "6. Complete Infix Evaluation\n7. Stack Operations Demonstration\n"
                  << "8. Select Stack Implementation (" << (linked ? "Linked List" : "Array") << ")\n"
                  << "9. Exit\nChoose an option: ";
        switch (readChoice()) {
        case 1: {
            const auto result = checkParentheses(readExpression());
            std::cout << result.message << '\n';
            printTrace(result.trace);
            break;
        }
        case 2: conversion(false); break;
        case 3: conversion(true); break;
        case 4: evaluation(false); break;
        case 5: evaluation(true); break;
        case 6: {
            const auto result = evaluateInfix(readExpression());
            if (!result.success) std::cout << "Error: " << result.message << '\n';
            else { std::cout << "Result: " << formatNumber(result.value) << '\n'; printTrace(result.trace); }
            break;
        }
        case 7: stackDemo(linked); break;
        case 8: linked = !linked; std::cout << "Selected " << (linked ? "linked-list" : "array-based") << " stack.\n"; break;
        case 9: std::cout << "Goodbye!\n"; return 0;
        default: std::cout << "Invalid choice. Enter 1-9.\n";
        }
    }
}
