# 42 MiniShell

A simple Unix shell implementation developed as part of the 42 curriculum.  
This project replicates fundamental behaviors of a real shell such as command parsing, redirections, piping, and environment handling.

## 📚 Project Overview

The goal of this project is to create a basic shell that mimics the behavior of Bash. The shell interprets and executes user input with features like:

- Built-in commands (e.g., `cd`, `echo`, `pwd`, `exit`, etc.)
- Handling of environment variables
- Pipes (`|`)
- Redirections (`>`, `>>`, `<`, `<<`)
- Quoting with `'` and `"`
- Signal handling (e.g., `Ctrl+C`, `Ctrl+D`)
- Proper exit codes

> This project follows the strict [42 Norm](https://github.com/42School/norminette) coding style and restrictions (e.g., no `fork()` in parsing, limited allowed functions).

---

## ⚙️ Features

- ✅ Lexical analysis (tokenization with respect to quotes)
- ✅ Parsing (AST-like structure for commands and redirections)
- ✅ Execution engine with fork/execve and pipelines
- ✅ Support for **heredoc (`<<`)** with signal handling
- ✅ Environment variable expansion (`$VAR`)
- ✅ Built-in commands:
  - `cd`
  - `echo`
  - `env`
  - `exit`
  - `export`
  - `pwd`
  - `unset`
- ✅ Signal handling (`SIGINT`, `SIGQUIT`)
- ✅ Exit status management

---

## 🧪 Getting Started

### ✅ Prerequisites

- Unix-like system (Linux or macOS)
- `cc` and `make` installed

### 🔧 Build the Shell

```bash
git clone https://github.com/Moe-Salim91156/42_Mini-Shell.git
cd 42_Mini-Shell
make
```

### 🚀 Run the Shell

```bash
./minishell
```

Type commands like in a real shell:

```bash
minishell$ echo "Hello World"
Hello World
```


---

## 🔒 Allowed Functions

- `malloc`, `free`, `write`, `read`, `access`, `open`, `close`, `dup`, `dup2`
- `pipe`, `fork`, `execve`, `exit`, `wait`, `waitpid`, `wait3`, `wait4`
- `getcwd`, `chdir`, `stat`, `lstat`, `fstat`
- `opendir`, `readdir`, `closedir`
- `strerror`, `perror`, `isatty`, `ttyname`, `ttyslot`
- `ioctl`, `getenv`, `tcsetattr`, `tcgetattr`
- `signal`, `kill`
- `printf`, `atoi`, `itoa`
-  `ft_strdup`, `ft_strjoin`, etc. from **libft**

---

## 🚦 Signals

- `Ctrl+C` (`SIGINT`) — interrupts current command but not the shell
- `Ctrl+\` (`SIGQUIT`) — ignored by shell, passed to child processes
- `Ctrl+D` — triggers shell exit if input is empty

---

## ✅ Status

- [x] Mandatory part
- [ ] Bonus part (Job control, wildcards `*`, and more...)

---

## 👨‍💻 Contributors

- **Mohammad Salim** - [@Moe-Salim91156](https://github.com/Moe-Salim91156)
- **Yousef Kitaneh** - [@dotacow](https://github.com/dotacow)

---

Happy Shell-ing! 🐚

## Feedback are welcomed!!
