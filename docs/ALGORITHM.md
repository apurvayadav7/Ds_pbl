# Algorithms and Complexity

## Stack operations

**Push:** Check `isFull` for the array implementation, increment `top`, and store the item. For the linked implementation, allocate a node, point it to the old top, and make it the new top.

**Pop:** Check `isEmpty`, read the top item, and decrement the array top or unlink and destroy the linked node.

**Peek:** Return the top item without changing the stack.

Push, pop, and peek are `O(1)`. Array space is `O(capacity)` and linked-stack space is `O(n)`.

## Balanced parentheses

1. Scan left to right.
2. Push every opening bracket.
3. For a closing bracket, report an error if empty; otherwise pop and compare types.
4. The expression is balanced only when the stack is empty at the end.

Time: `O(n)`. Space: `O(n)`.

## Infix conversion

Operands go directly to output. Operators are pushed after higher-precedence operators are popped. Parentheses delimit the operator stack. Unary signs have highest precedence and exponentiation is right-associative.

Time: `O(n)`. Space: `O(n)`.

## Prefix conversion

Reverse the tokens while swapping parentheses, apply operator-stack conversion, and reverse the result.

Time: `O(n)`. Space: `O(n)`.

## Expression evaluation

Postfix scans left to right; prefix scans right to left. Each operand is pushed. Each operator pops its required operands, calculates, and pushes the result. Invalid operand counts and division/modulo by zero produce errors.

Time: `O(n)`. Space: `O(n)`.

## Complete infix evaluation

Validate and convert infix input to postfix, then evaluate the generated postfix sequence using the custom operand stack.
