# Hexdump Utility

## Overview

This hexdump utility reads a binary file and prints its contents in both hexadecimal and ASCII formats. It is a simple tool designed to help users inspect the contents of binary files. The utility requires one mandatory argument, the file path, and an optional second argument to specify the number of bytes per row (default is 16, maximum is 32).

## Features

- Prints binary file contents in hexadecimal format.
- Displays corresponding ASCII characters next to hex values.
- Allows customization of bytes displayed per row (1-32).
- Provides clear error messages for common issues.

## Usage   
   
```sh
./hexdump <file_path> [bytes_per_row]
```
- <file_path>: The path to the binary file to be read.
- [bytes_per_row] (optional): The number of bytes to display per row (default is 16, maximum is 32).   

## Compilation

To compile the program, use the following command:

```sh
g++ -o hexdump hexdump.cpp
```
