# Cicero: Low-Level Compiled Language
Cicero is a simple language written in C as a learning project. It compiles to 64 bit NASM assembly and assembled and linked with GCC.

This has been among the most fun and interesting projects I've ever done, and I strongly encourage other programmers to take a crack at making a simple language of their own.
## Usage
Use "cicero <filename>" to compile a Cicero source file. On success, outputs program.asm, program.o, and program (the final executable).
### Example Cicero source file
```
word this
this : 2
word that : this + 2
word other : this + that
mark begin_loop
print other
other : other + 1
jump begin_loop
exit 0
```
The above code does the following operations:
- Declares a variable called "this", making space for it on the stack
- Declares variable "that", setting it to the value of this + 2
- Declares "other" as "this" + "that"
- Marks the beginning of a looping statement as "begin_loop"
- Prints the current value of "other"
- Iterates "other" by 1
- Jumps to the "begin_loop" mark, repeating the print and iterate statements forever.
In the above code, the "exit" statement will never be reached. There is currently no way to exit a loop in Cicero, but conditional loops are next on the docket.
## Features
Currently, a small number of features are implemented:
- Variables and literal values as 64-bit integers
- Arithmetic with proper operator precedence parsing
- Print statements
- "mark" and "jump" statements, which are labels and gotos
- Exit codes
Future features include (in rough order of planned implementation):
- Conditional jumps
- User input
- Comments
- Functions (eventually nested inside other functions to limit scope of callability)
- Pointers
- "define" statements for preprocessed string replacement
- "include" statements to include other files
- 8, 16, and 32 bit integer types
- Linking C code
## Statements
- exit <expression> - Exits the program with the evaluated expression as the exit code.
- word <identifier> - Declares a variable with the given identifier, making space for it on the stack.
- <identifier> : <expression> - Stores (defines) the evaluated expression in the variables with the given identifier.
- word <identifier> : <expression> - Shorthand for declaring and defining a variable in one line.
- mark <identifier> - Marks a point in the program that can be jumped to by referencing the identifier.
- jump <identifier> - Jumps to a point in the program with a matching mark statement.
- print <expression> - Prints the evaluated expression.
