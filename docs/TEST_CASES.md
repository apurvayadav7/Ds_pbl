# Test Cases

Run `make test` or `mingw32-make test`.

| Area | Input | Expected |
|---|---|---|
| Array push/pop | `1`, `2` | LIFO order `2`, `1` |
| Array overflow | Push into capacity 2 | Overflow exception |
| Array underflow | Pop empty stack | Underflow exception |
| Linked stack | Push `4`, `5` | Pop returns `5` |
| Brackets | `{[(())]}` | BALANCED |
| Brackets | `([)]` | NOT BALANCED |
| Brackets | `(a+b` | Missing closing bracket |
| Postfix conversion | `A+B*C` | `A B C * +` |
| Prefix conversion | `A+B*C` | `+ A * B C` |
| Postfix evaluation | `5 3 2 * +` | `11` |
| Prefix evaluation | `+ 5 * 3 2` | `11` |
| Infix evaluation | `(5+3)*2` | `16` |
| Exponentiation | `2^3` | `8` |
| Negative decimal | `-2.5*4` | `-10` |
| Division by zero | `10/0` | Error |
