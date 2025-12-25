# Custom Linux Shell

A lightweight **Unix Shell** implementation in C that provides a robust command-line interface for interacting with the operating system. This project implements the core lifecycle of a shell: reading user input, parsing commands, and managing process execution.

---

## 🚀 Current Features

### 1. REPL Architecture
The shell operates on a continuous **Read-Eval-Print Loop**, ensuring a seamless user experience similar to Bash or Zsh.

### 2. Command Execution
Executes standard system binaries by leveraging the power of system calls:
* **`fork()`**: To create new child processes.
* **`execvp()`**: To replace the child process with the desired command.
* **`wait()`**: To synchronize the shell with the command completion.



### 3. Built-in Commands
Native support for commands that operate directly on the shell's process:
* `cd`: Change the current working directory.
* `help`: Display manual and usage instructions.
* `exit`: Gracefully terminate the shell.
* `hello`: A custom greeting built-in.

### 4. Piping
Supports single-level piping (e.g., `ls | grep .c`) by setting up a communication channel between two child processes using `pipe()` and `dup2()`.



### 5. Command History
Integrated with the **GNU Readline** library, providing:
* Up/Down arrow key navigation through previous commands.
* Persistent session history.
* Advanced line editing features.

---

## 🛠️ Future Enhancements

To move this from a basic shell to a production-grade tool, the following features are planned:

* **I/O Redirection**: Support for `<` (input), `>` (output), and `>>` (append) to bridge commands with the filesystem.
* **Multiple Pipes**: Upgrading the execution engine to handle complex chains like `cat file | grep x | sort | uniq`.
* **Background Execution**: Support for the `&` operator to launch non-blocking tasks.
* **Signal Handling**: Capturing `Ctrl+C` (SIGINT) to prevent the shell from exiting when a child process is interrupted.
* **Environment Variables**: Parsing and expanding variables such as `$PATH`, `$HOME`, and custom user-defined strings.
* **Job Control**: Implementation of `jobs`, `fg`, and `bg` for managing multiple active processes.

---

## 🏗️ Requirements & Compilation

To compile and run this shell, you need the `readline` library installed on your Linux system.

```bash
# Install readline library (Ubuntu/Debian)
sudo apt-get install libreadline-dev

# Compile the shell
gcc shell.c -lreadline -o myshell

# Run the shell
./myshell
