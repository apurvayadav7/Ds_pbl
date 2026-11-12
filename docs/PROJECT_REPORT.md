# Expression Evaluator & Balanced Parentheses Checker

## 1. Cover Page

**Project:** Expression Evaluator & Balanced Parentheses Checker Using Stack Operations  
**Subject:** Data Structures and Algorithms  
**Students:** Apurva Kumar Yadav (02418015625), Vaibhav (00518015625)  
**College:** `[Enter college name]`  
**Department:** `[Enter department]`  
**Faculty:** `[Enter faculty name]`  
**Academic year:** `[Enter academic year]`

## 2. Certificate

This is to certify that `[student names]` completed `[project title]` under the guidance of `[faculty name]`. Signature: `[editable placeholder]`.

## 3. Acknowledgement

We thank our instructor, department, and peers for their guidance and feedback during this educational project.

## 4. Abstract

This project demonstrates the LIFO principle through custom array-based and linked-list-based stacks. The stacks are used for bracket matching, infix conversion, prefix/postfix evaluation, and trace visualization. The program validates overflow, underflow, malformed expressions, and division by zero.

## 5. Introduction and problem statement

Expression processing requires temporary storage whose newest item must be processed first. This project solves that problem using manually implemented stacks instead of `std::stack` or evaluation shortcuts.

## 6. Objectives and scope

Objectives are to implement both stack representations, show their operations, process mathematical expressions, and provide understandable traces. The scope is a C++17 console application using numeric constants and symbolic operands for conversion.

## 7. Existing and proposed system

An existing approach may rely on library stacks or opaque evaluators. The proposed system exposes every push and pop and separates data structure, parser, converter, evaluator, interface, and tests.

## 8. Requirements

**Hardware:** Any modern computer with a C++ compiler.  
**Software:** C++17 compiler, Make or CMake, and a terminal.

## 9. Data structures

The array stack provides fixed capacity and `isFull`; the linked stack grows dynamically and owns nodes with `std::unique_ptr`. A vector is used only for display and token support, not as the core stack.

## 10. System architecture and algorithms

See [FLOWCHART.md](FLOWCHART.md) and [ALGORITHM.md](ALGORITHM.md). The menu sends input to the parentheses checker, converters, evaluators, or stack demonstration. Each algorithm uses the custom stack classes.

## 11. Implementation details

`include/Stack.h` contains both stack implementations. `src/Expression.cpp` tokenizes, converts, evaluates, and formats results. `src/Parentheses.cpp` validates all three bracket types. `src/main.cpp` provides the interactive interface.

## 12. Screenshots

Add screenshots of the menu, a balanced trace, conversion output, evaluation output, and stack demonstration here.

## 13. Testing

The automated test suite covers stack behavior, bracket errors, conversion, arithmetic, negative decimals, and division by zero. See [TEST_CASES.md](TEST_CASES.md).

## 14. Complexity

Each scan is `O(n)` time and `O(n)` auxiliary space. Push, pop, and peek are `O(1)`. Array allocation is `O(capacity)` and linked allocation is `O(n)`.

## 15. Advantages and limitations

Advantages include transparent algorithms, two stack implementations, clear errors, and reproducible tests. Limitations include console-only interaction and no variables or functions in numeric evaluation.

## 16. Applications and future enhancements

Stacks are used in compilers, calculators, undo systems, browser history, and syntax validation. Future work could add variables, functions, GUI visualization, persistent history, and additional automated property tests.

## 17. Conclusion

The project shows that stack operations provide a reliable foundation for syntax checking and expression processing while making the LIFO principle visible to students.

## 18. References

1. C++17 standard library documentation.
2. Course notes on stacks and expression processing.
3. Functional reference: [ChickenWings-0/DS-PBL](https://github.com/ChickenWings-0/DS-PBL).
