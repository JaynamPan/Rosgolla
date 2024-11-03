## Introduction
Rosgolla (yes, it's named after a cat) is a toy programming language.

#### Features
- **Meow Mode**: You can write a basic program with cat's language(the "meow"s).
- **Dynamic Typed**: Easy to use.
## Quick Start
Note: The source code uses c99 features.
1. Compile source code in src (with params to support c99 for your C compiler).
2. Use the generated binary interpreter in a Terminal.  You can use REPL interface or pass in a text script file.   
(You can use compiled ```rosgolla.exe``` in ```build/output``` direcotry if you're using Windows)
## Examples
1. Run meow_bird_go.ros 
   ```
   rosgolla meow_bird_go.ros
   ```
  
## References

This project is inspired by the following sources:
- **[CraftingInterpreters WebSite](https://craftinginterpreters.com/)**: The initial structure of Rosgolla referred the website's Clox implementation.
- **Brainfuck Language**: Rosgolla's "Meow Mode" is based on brainfuck.
