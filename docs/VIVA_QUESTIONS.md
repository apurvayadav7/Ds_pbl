# Viva Questions and Answers

1. **What is LIFO?** Last In, First Out; the newest item is removed first.
2. **Why are stacks used in expressions?** Operators and operands need temporary storage in reverse processing order.
3. **What is stack overflow?** Pushing into a full fixed-capacity stack.
4. **What is underflow?** Popping or peeking an empty stack.
5. **Array stack advantage?** Constant-time access and simple memory layout.
6. **Linked stack advantage?** Dynamic capacity without a fixed limit.
7. **Linked stack limitation?** Each node needs pointer storage and allocation.
8. **What does peek do?** Reads the top without removing it.
9. **How are brackets checked?** Push openings and match each closing bracket with the top.
10. **Why is `A+B*C` converted to `A B C * +`?** Multiplication has higher precedence.
11. **What is associativity?** The direction used when operators share precedence.
12. **Why is exponentiation right-associative?** `a^b^c` conventionally means `a^(b^c)`.
13. **What is postfix notation?** Operators appear after their operands.
14. **What is prefix notation?** Operators appear before their operands.
15. **How is postfix evaluated?** Scan left to right and apply operators to popped operands.
16. **How is prefix evaluated?** Scan right to left.
17. **Why not use `std::stack`?** The project requirement is to demonstrate the ADT implementation.
18. **How are memory leaks prevented?** Linked nodes are owned by `std::unique_ptr`.
19. **What happens on division by zero?** The evaluator returns an explicit error.
20. **What is conversion complexity?** `O(n)` time and `O(n)` space.
21. **What does unary minus mean?** A sign applied to one operand, such as `-2.5`.
22. **Why tokenize numbers?** It preserves multi-digit and decimal operands.
23. **What validates malformed expressions?** Operand count and final stack size checks.
24. **What does the trace show?** The token, operation, stack contents, and intermediate result.
25. **How can the project be extended?** Add variables, functions, GUI controls, and persistent expression history.
