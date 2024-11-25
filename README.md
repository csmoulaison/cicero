# Cicero: Low-Level Compiled Language
Cicero is a simple language written in C as a learning project. It compiles to 64 bit NASM assembly and is assembled and linked with GCC.

The compiler code is fairly straightforward and imperative, and there's a lot of cleanup to do from it's current state. It utilizes a single-pass, recursive descent parser. Operator precedence parsing is implemented using the Pratt parsing approach, which is so simple it feels like cheating. NASM code is printed directly the a .asm file while parsing. I need to do some work soon to extricate these two concerns.

This has been one of the most fun and interesting projects I've worked on, and I strongly encourage other programmers to take a crack at making a simple language of their own.
## Usage
Use **cicero \<filename>** to compile a Cicero source file. Use **cicero help** for compiler options. On success, outputs **out** executable by default.
### Example Cicero source file (examples/demo.ci)
```
~ Demonstrates all current language features
~ Comments are preceded by a tilde
~ Variable declaration and definition
word var : 3
var : 2

~ Shorthand for the above
word var2 : 4

~ Precedence parsing: Still no parentheses grouping
word parsed : var * var2 + 3 % 2 - 10 / 2

~ Print statement
print parsed

~ Jump statement referencing a later mark statement
jump skip

~ This statement will never run
print 0

~ Mark statement: can be jumped to with a jump statement
mark skip

~ Marks and jumps to implement a for loop, with a conditional if statement
word count : 0
mark loop

print count
count : count + 1

if (count < 10) jump loop

~ Exit statement
exit 0
```
## Features
Currently, a small number of features are implemented:
- Variables and literal values as 64-bit integers
- Arithmetic with operator precedence parsing (still needs parenthesis grouping)
- **print** statements
- **mark" and **jump** statements, which are labels and gotos
- Conditional statements
- **exit** statements
- Code comments

Future features include (in rough order of planned implementation):
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
- **if (\<conditional> \<statement>** - Runs the statement if the conditional is true. (Comparisons between numbers using the relevant operators { <, >, !, = }.
- **print \<expression>** - Prints the evaluated expression.
