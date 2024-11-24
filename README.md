# Cicero: Low-Level Compiled Language
Cicero is a simple language written in C as a learning project. It compiles to 64 bit NASM assembly and is assembled and linked with GCC.

The compiler code is fairly straightforward and imperative, and there's a lot of cleanup to do from it's current state. It utilizes a single-pass, recursive descent parser. Operator precedence parsing is implemented using the Pratt parsing approach, which is so simple it feels like cheating. NASM code is printed directly the a .asm file while parsing. I need to do some work soon to extricate these two concerns.

This has been one of the most fun and interesting projects I've worked on, and I strongly encourage other programmers to take a crack at making a simple language of their own.
## Usage
Use **cicero \<filename>** to compile a Cicero source file. On success, outputs **program.asm**, **program.o**, and **program** (the final executable).
### Example Cicero source file
```
word this
this : 2
word that : this + 2
word other : this + that

~ This is a comment
mark begin_loop
print other
other : other + 1
if (other < 10) jump begin_loop

exit 0
```
The above code does the following operations:
- Declares a variable called **this**, making space for it on the stack
- Declares variable **that**, setting it to the value of **this + 2**
- Declares **other** as **this + that**
- Marks the beginning of a looping statement as **begin_loop**
- Prints the current value of **other**
- Iterates **other** by 1
- Jumps to the **begin_loop** mark if **other** is less than 10, repeating the print and iterate statements until that condition is satisfied.

The output is the numbers printed in order from 0 to 10 before the program exits.
## Features
Currently, a small number of features are implemented:
- Variables and literal values as 64-bit integers
- Arithmetic with operator precedence parsing (still needs parenthesis grouping)
- **print** statements
- **mark" and **jump** statements, which are labels and gotos
- **exit** statements
- Code comments

Future features include (in rough order of planned implementation):
- Conditional jumps
- User input
- Pointers
- More contextual and uniform error messages
- Functions (eventually nested inside other functions to limit scope of callability)
- **define** statements for preprocessed string replacement
- **include** statements to include other files
- 8, 16, and 32 bit integer types
- Linking C code
## Statements
- **exit \<expression>** - Exits the program with the evaluated expression as the exit code.
- **word \<identifier>** - Declares a variable with the given identifier, making space for it on the stack.
- **\<identifier> : \<expression>** - Stores (defines) the evaluated expression in the variables with the given identifier.
- **word \<identifier> : \<expression>** - Shorthand for declaring and defining a variable in one line.
- **mark \<identifier>** - Marks a point in the program that can be jumped to by referencing the identifier.
- **jump \<identifier>** - Jumps to a point in the program with a matching mark statement.
- **print \<expression>** - Prints the evaluated expression.
