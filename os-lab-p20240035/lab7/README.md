# OS Lab 7 — Bash Scripting, Permissions & Server Automation

**Student Name:** Theng Van Heng  
**Student ID:** p20240035  
**Date:** Sun, Jun 7, 2026

## Overview
This lab covers Bash scripting basics, login environment configuration via `.bashrc`, write-only drop-boxes, broadcaster patterns, compiled SUID helpers, cross-user scripting, and automation.

## Questions & Answers
1. **Why did `warmup` fail before you added execute permission?**  
   Linux requires the execute (`x`) permission bit on a text file to run it directly as a script. Without this bit, the kernel's loader blocks execution, throwing a `Permission denied` error.
2. **What does adding `~/bin` to `PATH` allow you to do?**  
   It informs the shell's command-lookup process to search `~/bin` for executables. This allows running personal scripts by typing their name from any working directory, rather than prefixing them with `./` or using the full absolute path.
3. **Why does `chmod 733 public_inbox` allow classmates to drop files but not list the inbox?**  
   Permissions `733` give write (`w`) and execute (`x`) access to others, but not read (`r`). Without read access, users cannot list directory contents (e.g. via `ls`). However, execute access allows them to traverse (enter) the directory, and write access lets them create new files inside it.
4. **Why does Linux ignore SUID on shell scripts, and why did we use a compiled C program instead?**  
   Modern Linux ignore the SUID bit on interpreted scripts because of security vulnerabilities. An attacker can exploit race conditions between the interpreter starting up and reading the file to gain root access. Compiled C binaries are evaluated directly by the kernel and do not require external interpreters, which makes SUID execution safe.
5. **What is the difference between `>` and `>>` in Bash redirection?**  
   The `>` operator overwrites the target file's existing content (truncating it to 0 bytes first), whereas the `>>` operator appends the output to the end of the target file without destroying existing content.
6. **How did your `harvester` avoid reading files that were missing or not readable?**  
   It utilized conditionals `[ -f "$target_file" ]` to verify the path is a regular file, and `[ -r "$target_file" ]` to verify the file is readable by our user before executing `cat`.
7. **What permission problems did you or your classmates need to fix during the lab?**  
   Home directory permissions had to be updated to `711` to allow classmates' processes to traverse into our bin or public directories, and the target files/directories in our public workspaces needed appropriate group/others write and read permissions.
