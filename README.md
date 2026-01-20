# Pipex – 42 School Project

This repository contains my **Pipex** project from 42 School. Pipex is designed to mimic the behavior of shell pipelines, allowing the execution of multiple commands connected with pipes, along with input and output redirection.

---

## Overview

`Pipex` simulates the command-line behavior of `cmd1 | cmd2 | ... | cmdN` with input/output redirection, providing practice with **processes, pipes, file descriptors, and command execution** in C.

### Features

* Execute multiple commands in sequence using pipes
* Redirect input from a file and output to a file
* Handles command execution using `fork()` and `execve()`
* Proper error handling for invalid commands or file issues
* Supports unlimited commands chained via pipes

### Usage

```bash
./pipex file1 "cmd1" "cmd2" ... "cmdN" file2
```

* `file1` – input file
* `cmd1 ... cmdN` – commands to execute
* `file2` – output file

### Example

```bash
./pipex infile "ls -l" "grep txt" outfile
```

This is equivalent to:

```bash
< infile ls -l | grep txt > outfile
```

### Installation & Build

```bash
git clone <repo-url>
cd pipex  # change to the project directory
make
./pipex <arguments>
```

### Notes

* Focuses on **system programming** concepts: processes, pipes, file descriptors, and command execution.
* Teaches error handling and proper resource management in C.
* Prepares for more complex projects like MiniShell and other shell implementations.

---

## Languages

* C — 96.7%
* Makefile — 3.3%
