# Minishell Project Scope

The **Minishell** project involves creating a simplified version of a Unix shell. The goal is to replicate a subset of Bash's functionality, focusing on parsing commands, executing them, and implementing basic shell features. Here's a detailed breakdown of the project's scope based on the requirements:

---

## **Key Objectives of the Minishell Project**

### **1. Basics**
- Create a program that behaves like a simple Unix shell.
- Must not use any external libraries except for the standard C library (`<stdlib.h>`, `<unistd.h>`, etc.).

### **2. Required Features**
The shell should support:

#### **Interactive Mode:**
- Continuously display a prompt (`minishell$`) waiting for user input.

#### **Command Parsing:**
- Handle user input, parse commands, and execute them.

#### **Builtin Commands:**
Implement these Bash-like builtins:
- `echo` with `-n` flag.
- `cd` to navigate directories.
- `pwd` to display the current working directory.
- `export` to set environment variables.
- `unset` to unset environment variables.
- `env` to display all environment variables.
- `exit` to exit the shell.

#### **Execution of Programs:**
- Support executing binaries located in the `$PATH`.
- Handle invalid commands gracefully by displaying appropriate error messages.

#### **Redirections:**
- Handle **input redirection** (`<`).
- Handle **output redirection** (`>` and `>>` for append mode).

#### **Pipes (`|`):**
- Enable piping between commands, where the output of one command serves as the input for the next.

#### **Environment Variables:**
- Expand environment variables in commands (e.g., `$HOME` or `$USER`).
- Support special variables like `$?`, which stores the exit status of the last executed command.

#### **Signals:**
- Properly handle signals like:
  - `CTRL+C` to interrupt the current command.
  - `CTRL+D` to signal end-of-file (EOF) and exit the shell.
  - `CTRL+\` to quit the current process without killing the shell.

#### **Error Management:**
- Provide meaningful error messages for invalid commands, invalid syntax, or failures (e.g., permission denied).

---

## **Forbidden Elements**
- Using `system()` or any function that behaves like it.
- Using functions like `getline()` or higher-level parsing utilities.
- Memory leaks or invalid memory management.

---

## **Additional Expectations**

### **1. Norm Compliance:**
- The code must follow the **42 Norm** coding standard.

### **2. Robustness:**
- Handle invalid inputs and edge cases gracefully (e.g., empty commands, invalid paths, malformed pipes).

---

## **Bonus Features**
If you complete the mandatory part, you can add advanced features:
- `&&` and `||` (logical AND/OR operators for chaining commands).
- Subshells using `()` (e.g., `(ls && echo success)`).
- Wildcards (`*`) for file globbing.
- Advanced redirections (e.g., `<<` for heredocs).

---

## **Scope Summary**
The **Minishell project** lies at the intersection of **low-level programming** and **operating system fundamentals**. You'll need to:
- Write a command-line interface that interacts with the system via system calls.
- Understand process management (`fork`, `execve`, `wait`).
- Work with file descriptors and redirection (`dup2`, `pipe`).
- Manage dynamic memory effectively.
- Parse complex strings and handle edge cases.

---

Would you like me to expand on how to approach specific parts of this project or create a plan for breaking it into manageable steps?

