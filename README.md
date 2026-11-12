# Expression Evaluator / Balanced-Parentheses Checker Using Stack Operations

A C++17 console application that demonstrates the **Stack ADT** using two implementations: a fixed-capacity array stack and a dynamically allocated linked-list stack. The project applies stack operations to balanced-bracket checking, infix conversion, prefix/postfix evaluation, and complete infix evaluation.

> **Data Structures Lab — Project Based Learning (PBL)**  
> B.Tech CSE-AIML, Semester 3 · Section G · Group G1  
> Delhi Technical Campus (GGSIPU) · Faculty: **Akash Bhardwaj**
>
> Project members: **Apurva Kumar Yadav** and **Vaibhav**

## Team

| Member | Enrollment No. | Contribution |
|---|---:|---|
| Apurva Kumar Yadav | 02418015625 | `[Add contribution details]` |
| Vaibhav | 00518015625 | `[Add contribution details]` |

## Features

1. **Stack implementations from scratch**
   - `ArrayStack<T>`: fixed-capacity array with `top`, overflow detection, and `isFull`.
   - `LinkedStack<T>`: dynamically allocated singly linked nodes managed with `std::unique_ptr`.
   - `push`, `pop`, `peek`, `isEmpty`, `isFull`, `size`, and stack-content inspection.
   - Explicit overflow and underflow errors.
   - No `std::stack` is used for the core algorithms.
2. **Balanced-parentheses checker**
   - Supports `()`, `[]`, and `{}`.
   - Detects extra closing brackets, mismatched pairs, and missing closing brackets.
   - Prints stack operations as a step-by-step trace.
3. **Infix-to-postfix conversion**
   - Handles precedence: `^` > `* / %` > `+ -`.
   - Handles right-associative exponentiation.
   - Supports numbers, decimal values, identifiers, parentheses, whitespace, and unary `+`/`-`.
4. **Infix-to-prefix conversion**
   - Uses the stack-based reverse, convert, and reverse approach.
5. **Postfix and prefix evaluation**
   - Supports addition, subtraction, multiplication, division, modulus, and exponentiation.
   - Supports negative numbers and decimal values.
   - Reports division by zero, modulo by zero, invalid operands, missing operands, and extra operands.
6. **Complete infix evaluation**
   - Converts infix to postfix and evaluates the generated postfix expression.
   - Displays the final result and stack trace.
7. **Trace visualization**
   - Shows the current token, operation, stack contents, and intermediate result.
8. **Interactive stack playground**
   - Supports `push`, `pop`, `peek`, `display`, `empty`, `full`, and `back`.
   - Allows switching between array-based and linked-list-based stacks.

## Project structure

```text
include/
    Expression.h       Conversion and evaluation declarations
    Parentheses.h      Bracket-checking and trace declarations
    Stack.h             ArrayStack and LinkedStack implementations

src/
    main.cpp            Console menu and user interface
    Expression.cpp      Tokenization, conversion, evaluation, formatting
    Parentheses.cpp     Balanced-parentheses algorithm

tests/
    test_main.cpp       Automated stack and expression tests

docs/
    ALGORITHM.md        Algorithms and complexity analysis
    FLOWCHART.md        Mermaid flowcharts and architecture
    PROJECT_REPORT.md   College project report
    TEST_CASES.md       Test-case reference table
    VIVA_QUESTIONS.md   Viva questions and answers

examples/
    sample_expressions.txt

.vscode/
    tasks.json          VS Code build and test tasks

CMakeLists.txt
Makefile
README.md
```

## Build and run

### Requirements

- A C++17-compatible compiler.
- Windows MinGW, Linux GCC, or another standard C++ toolchain.
- Make is optional.
- CMake is optional.

### Using Make

| Task | Windows MinGW | Linux/macOS |
|---|---|---|
| Build | `mingw32-make` | `make` |
| Run tests | `mingw32-make test` | `make test` |
| Clean | `mingw32-make clean` | `make clean` |

Run the application after building:

```powershell
.\expr_eval.exe
```

```bash
./expr_eval
```

### Without Make

From the project root:

```bash
g++ -std=c++17 -Wall -Wextra -pedantic -Iinclude src/main.cpp src/Expression.cpp src/Parentheses.cpp -o expr_eval
```

On Windows with MinGW:

```powershell
C:\msys64\ucrt64\bin\g++.exe -std=c++17 -Wall -Wextra -pedantic -Iinclude src\main.cpp src\Expression.cpp src\Parentheses.cpp -o expr_eval.exe
```

Build and run the test executable:

```bash
g++ -std=c++17 -Wall -Wextra -pedantic -Iinclude tests/test_main.cpp src/Expression.cpp src/Parentheses.cpp -o test_runner
./test_runner
```

### Using CMake

```bash
cmake -S . -B build
cmake --build build
ctest --test-dir build --output-on-failure
```

### Using VS Code

1. Open `D:\F_ds_pbl` as the workspace folder.
2. Press **Ctrl + Shift + B**.
3. Select **C/C++: Build expression evaluator**.
4. Run the program from the terminal:

```powershell
.\expr_eval.exe
```

The project task is configured in [.vscode/tasks.json](.vscode/tasks.json) and includes the `include` directory and all required source files.

## Menu

```text
1. Balanced Parentheses Checker
2. Infix to Postfix Conversion
3. Infix to Prefix Conversion
4. Postfix Evaluation
5. Prefix Evaluation
6. Complete Infix Expression Evaluation
7. Stack Operations Demonstration
8. Select Stack Implementation (Array / Linked List)
9. Exit
```

## Examples

| Input | Output |
|---|---|
| `A+B*C` to postfix | `A B C * +` |
| `A+B*C` to prefix | `+ A * B C` |
| `(10+5)*2-8/4` | `28` |
| `5 3 2 * +` postfix | `11` |
| `+ 5 * 3 2` prefix | `11` |
| `2^3` | `8` |
| `-2.5*4` | `-10` |

### Balanced bracket examples

```text
{(a+b)*[c-d]}   -> BALANCED
((10+20)*30)    -> BALANCED
([)]            -> NOT BALANCED
(a+b            -> NOT BALANCED
a+b)            -> NOT BALANCED
```

### Stack playground example

```text
Select option 7
push 10
push 20
peek
display
pop
empty
back
```

The stack follows LIFO order: `20` is returned before `10`.

### Trace example

For `(10+5)*2`, the application prints a table containing entries similar to:

```text
Token         Operation                         Stack                   Result
--------------------------------------------------------------------------------------
(             PUSH left parenthesis             (
10            Add operand                       (                       10
+             PUSH operator                     ( +                     10
5             Add operand                       ( +                     10 5
)             POP until left parenthesis        [empty]                 10 5 +
*             PUSH operator                     *                       10 5 +
2             Add operand                       *                       10 5 + 2
```

The complete trace is generated by the actual conversion and evaluation stacks.

## Input rules

- Infix input may contain numbers such as `7`, `120`, and `3.5`.
- Identifiers such as `A`, `total`, and `value1` are accepted during conversion.
- Numeric evaluation requires operands that can be parsed as numbers.
- Supported binary operators are `+`, `-`, `*`, `/`, `%`, and `^`.
- Unary `+` and `-` are accepted where an operand is expected.
- Round parentheses `()` may be used to control grouping in expressions.
- Square and curly brackets `[]` and `{}` are supported by the separate balanced-parentheses checker.
- Spaces are optional in infix expressions.
- Prefix and postfix expressions must use spaces between tokens, for example:
  - Postfix: `5 3 2 * +`
  - Prefix: `+ 5 * 3 2`
- Division and modulo by zero are rejected with an explicit error.
- Malformed expressions are rejected instead of producing a result.

## Error handling

The application reports:

- Array stack overflow.
- Stack underflow and empty-stack peek.
- Extra, missing, or mismatched brackets.
- Invalid characters and invalid numeric values.
- Missing operands.
- Extra operands.
- Division by zero.
- Modulo by zero.
- Invalid menu choices and unknown playground commands.

## Testing

The automated test suite covers:

- Array push, pop, peek, empty, full, overflow, and underflow.
- Linked-list stack LIFO behavior.
- Balanced, mismatched, and incomplete brackets.
- Infix-to-postfix conversion.
- Infix-to-prefix conversion.
- Prefix, postfix, and infix evaluation.
- Exponentiation and negative decimal values.
- Division-by-zero handling.

Run:

```bash
make test
```

or on Windows:

```powershell
mingw32-make test
```

Expected output:

```text
All tests passed.
```

## Limitations

- The interface is console-based.
- Numeric evaluation does not provide variable assignment or mathematical functions.
- Conversion accepts symbolic identifiers, but evaluation requires numeric operands.
- CMake must be installed separately if the CMake workflow is used.

## Complexity

For an input of `n` tokens:

- `push`, `pop`, and `peek`: `O(1)`.
- Balanced-parentheses checking: `O(n)` time and `O(n)` space.
- Infix-to-postfix conversion: `O(n)` time and `O(n)` space.
- Infix-to-prefix conversion: `O(n)` time and `O(n)` space.
- Prefix and postfix evaluation: `O(n)` time and `O(n)` space.
- Complete infix evaluation: `O(n)` time and `O(n)` space.

The array stack reserves fixed capacity, while the linked stack uses `O(n)` dynamically allocated nodes.

## Data Structures concepts demonstrated

- **LIFO:** The most recently pushed item is processed first.
- **Array stack:** Uses a `top` index and fixed capacity.
- **Linked stack:** Uses nodes and a pointer to the top node.
- **Operator stack:** Stores operators during expression conversion.
- **Operand stack:** Stores numeric values during evaluation.
- **Syntax stack:** Stores opening brackets during validation.

## Documentation

- [Algorithms and complexity](docs/ALGORITHM.md)
- [Flowcharts and architecture](docs/FLOWCHART.md)
- [Project report](docs/PROJECT_REPORT.md)
- [Test cases](docs/TEST_CASES.md)
- [Viva questions and answers](docs/VIVA_QUESTIONS.md)
- [Sample expressions](examples/sample_expressions.txt)

## Reference and originality

The project structure and feature goals were informed by the public [ChickenWings-0/DS-PBL reference repository](https://github.com/ChickenWings-0/DS-PBL). This implementation uses its own source organization, stack classes, parser, evaluator, tests, and documentation.

## License

This educational project is provided for academic use. Add an institution-approved open-source license before public redistribution.
