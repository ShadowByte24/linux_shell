Custom Linux Shell
A lightweight Unix Shell implementation in C that provides a command-line interface for interacting with the operating system. It handles the core lifecycle of a shell: reading user input, parsing commands, and managing process execution.

🚀 Current Features
REPL Architecture: A continuous Read-Eval-Print Loop for user interaction.

Command Execution: Executes standard binaries (e.g., ls, grep, mkdir) using fork and execvp.

Built-in Commands: Native support for cd, help, exit, and hello.

Piping: Supports single-level piping (e.g., command1 | command2) using system pipes and I/O redirection between child processes.

Command History: Integrated with the readline library for command history and easy navigation.

🛠️ Future Enhancements
I/O Redirection: Support for < (input), > (output), and >> (append) to interact with files.

Multiple Pipes: Upgrade logic to handle complex chains (e.g., cmd1 | cmd2 | cmd3).

Background Execution: Implement the & operator to run processes without blocking the prompt.

Signal Handling: Manage Ctrl+C (SIGINT) so the shell stays active even if a child process is killed.

Environment Variables: Support for expanding and setting variables like $PATH.

Job Control: Add jobs, fg, and bg commands to manage running tasks.
