# 🧠 Hcode Lexical-Analyser

A simple yet extensible Lexical-Analyser for a custom programming language called **Hcode**, built in C++.  
It currently supports variable declarations, expressions, basic control flow (if-else, while, for), and is modular enough for future extensions like functions and classes.

## 🚀 Features
- ✅ **Variable declarations** (`let x = 10;`)
- ✅ **Arithmetic operations** (`+`, `-`, `*`, `/`)
- ✅ **Boolean expressions** (`==`, `!=`, `<`, `<=`, `>`, `>=`, `&&`, `||`)
- ✅ **Control Flow**
  - `if`, `else`
  - `while` loops
  - `for` loops
- ✅ **Braced block support** `{ ... }`
- ✅ **Error handling** with line and column info

## 📁 Project Structure
Hcode/
├── build/                # Build directory (created after compiling)
├── examples/             # Sample Hcode programs
│   ├── hello.hcode       # Simple example (let, expressions)
│   └── control.hcode     # Uses if, else, loops
├── include/
│   └── lexer.h           # Lexer header
├── src/
│   ├── main.cpp          # Entry point
│   ├── lexer.cpp         # Tokenizer logic
│   └── parser.cpp        # AST & evaluator logic
├── CMakeLists.txt        # Build configuration
└── README.md             # This file

🛠️ Building the Project
Make sure you have CMake and a C++ compiler (like g++) installed.

# Inside the project root
mkdir build
cd build
cmake ..
make
You’ll get the HcodeCompiler binary inside the build/ directory.

## Running Hcode Programs
./HcodeCompiler ../examples/hello.hcode
