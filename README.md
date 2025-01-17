# SimpleLangInterpreter

## Description
SimpleLangInterpreter is a lightweight interpreter for a custom scripting language. The language supports variables, arithmetic operations, conditional jumps, and basic program control. This project is designed to execute commands written in a simple syntax from a text file (`input.txt`) and display the results in the terminal. It serves as an excellent starting point for learning and experimenting with language design and interpreters.

---

## Features
- **Variable Handling:** Supports defining and using variables with a `$` prefix. Variables are case-sensitive and store positive integers.
- **Arithmetic Operations:** Includes binary operations such as addition, subtraction, multiplication, division, modulus, and power.
- **Unary Operations:** Supports increment (`increase`) and decrement (`decrease`) operations.
- **Conditional Jumps:** Allows conditional branching with commands like `jump_if_equal`, `jump_if_not_equal`, `jump_if_greater`, and `jump_if_less`.
- **Tags and Program Flow:** Enables tagging lines for jumping within the program using `@tag`.
- **Output:** Print variable values or constants using the `print` command.
- **Exit Command:** Terminates the program gracefully with the `exit` command.

---

## Syntax Overview
### 1. Variable Assignment
```txt
<value> -> $<variable_name>;
```
**Example:**
```txt
10 -> $x;
5 -> $y;
```

### 2. Binary Operations
```txt
<input1>,<input2> -> <operation> -> $<output_variable>;
```
Supported operations: `add`, `minus`, `multiply`, `divide`, `modulus`, `power`

**Example:**
```txt
$x,$y -> add -> $sum;
```

### 3. Unary Operations
```txt
<input> -> <operation>;
```
Supported operations: `increase`, `decrease`

**Example:**
```txt
$x -> increase;
```

### 4. Printing Values
```txt
<input> -> print;
```
**Example:**
```txt
$x -> print;
42 -> print;
```

### 5. Tags and Jumps
#### Defining a Tag:
```txt
@<tag>;
```
#### Unconditional Jump:
```txt
@<tag> -> jump;
```
#### Conditional Jumps:
```txt
@<tag>,<input1>,<input2> -> <conditional_jump>;
```
Supported conditional jumps: `jump_if_equal`, `jump_if_not_equal`, `jump_if_greater`, `jump_if_less`

**Example:**
```txt
@start;
$x,$y -> jump_if_equal;
@exit;
```

### 6. Exit Command
```txt
exit;
```

---

## Input File Example
Here is a sample `input.txt` file:
```txt
5 -> $x;
10 -> $y;
$x,$y -> add -> $sum;
$sum -> print;
@start,$x,$y -> jump_if_greater;
@exit;
$x -> increase;
$x -> print;
exit;
```

---

## How to Use
1. Clone the repository:
   ```bash
   git clone <repository_url>
   ```
2. Compile the code:
   ```bash
   g++ -o interpreter main.cpp
   ```
3. Create your `input.txt` file with the desired program.
4. Run the interpreter:
   ```bash
   ./interpreter
   ```

---

## Error Handling
- **Undefined Variable:** Throws an error when a variable is used without being initialized.
- **Division by Zero:** Throws an error for division or modulus operations when the divisor is zero.
- **Undefined Tag:** Throws an error if a jump is attempted to an undefined tag.
- **Unknown Operation:** Throws an error for unsupported operations.

---

## License
This project is licensed under the MIT License. Feel free to use and modify it for educational or personal purposes.

---

## Contributions
Contributions are welcome! If you have ideas for improving the interpreter or extending its functionality, feel free to submit a pull request or open an issue.

