# Simple Programming Language Interpreter

This repository contains a lightweight interpreter for a custom programming language inspired by C++ syntax. The interpreter processes instructions written in a text file (`input.txt`) and executes them in sequence. The language supports variable declarations, basic arithmetic operations, conditional jumps, and more.

## Features

1. **Variable Declarations**:
   - Variables must start with a `$` symbol (e.g., `$var`).
   - Variables are case-sensitive.
   - Only positive integers are supported.
   - Syntax: `<value> -> $<variable_name>;`
     - Example: `5 -> $x;`

2. **Binary Operations**:
   - Supported operations: `add`, `minus`, `multiply`, `divide`, `modulus`, `power`.
   - Syntax: `<value1>,<value2> -> <operation> -> $<result_variable>;`
     - Example: `3,4 -> add -> $sum;`

3. **Unary Operations**:
   - Supported operations: `increase`, `decrease`.
   - Syntax: `<value> -> <operation>;`
     - Example: `$x -> increase;`

4. **Conditional Jumps**:
   - Supported operations: `jump_if_equal`, `jump_if_not_equal`, `jump_if_greater`, `jump_if_less`.
   - Syntax: `@<tag>,<value1>,<value2> -> <operation>;`
     - Example: `@loop,3,4 -> jump_if_less;`

5. **Tags and Unconditional Jumps**:
   - Tags are defined using `@<tag_name>;`.
   - Unconditional jumps: `@<tag_name> -> jump;`

6. **Print Statements**:
   - Syntax: `<value> -> print;`
     - Example: `$x -> print;`

7. **Exit Command**:
   - Stops program execution.
   - Syntax: `exit;`

## How It Works

1. **Input File**: Instructions are read from `input.txt`.
2. **Parsing**: Each line is parsed using regular expressions to identify and execute commands.
3. **Execution**: Operations are executed sequentially unless a jump modifies the flow.
4. **Error Handling**: The interpreter validates variable names, undefined variables, division by zero, and more.

## Example `input.txt`
```txt
5 -> $x;
3 -> $y;
$x,$y -> add -> $sum;
$sum -> print;
@loop;
$sum -> increase;
$sum,20 -> jump_if_less -> @loop;
exit;
```
**Output:**
```
8
9
...
20
```

## Setup

1. Clone this repository.
2. Compile the code using a C++ compiler:
   ```bash
   g++ -o interpreter interpreter.cpp
   ```
3. Create an `input.txt` file in the same directory as the executable.
4. Run the interpreter:
   ```bash
   ./interpreter
   ```

## Contributing
Contributions are welcome! Feel free to open an issue or submit a pull request for improvements or new features.

## License
This project is licensed under the MIT License. See the LICENSE file for details.

