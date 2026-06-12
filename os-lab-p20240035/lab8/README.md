# OS Lab 8 — Secure Bash Scripting, Race Conditions & File Locking

**Student Name:** Theng Van Heng  
**Student ID:** p20240035  
**Date:** Fri, Jun 12, 2026

## Overview
This lab covers input validation, transaction logging, Time-of-Check to Time-of-Use (TOC-TOU) race conditions, process scheduling issues, OS-level mutual exclusion using `flock`, cross-user permissions, secure drop zones, and automated cleanup scripts.

## Questions & Answers
1. **What does TOC-TOU mean, and where did it appear in the vulnerable `buy_widget` script?**  
   TOC-TOU stands for *Time-of-Check to Time-of-Use*. It occurred in `buy_widget` where the script checked if the inventory was sufficient (`cat inventory.txt`), and then later updated it (`echo $new_inv > inventory.txt`). Since these two operations were not atomic, multiple processes checked the inventory concurrently before any of them updated it, causing race conditions.
2. **Why did `bot_swarm` sometimes leave inventory values other than `0` before the patch?**  
   Because processes ran concurrently and read stale inventory data before write operations completed. Many processes read the same inventory level (e.g. 100), calculated the same new value (98), and wrote 98 back, resulting in "lost updates" and leaving inventory higher than 0.
3. **What part of the script is the critical section, and why must it be protected?**  
   The critical section spans from reading the inventory, validating availability, writing the updated inventory, and appending to the sales log. It must be protected so that only one process can execute these steps at a time, ensuring data consistency.
4. **How does `flock -x` enforce mutual exclusion between concurrent processes?**  
   `flock -x` requests an advisory exclusive lock on a specific file descriptor. If another process holds the lock, subsequent processes block until the lock is released, allowing only one process inside the critical section.
5. **Which permissions did you use to let a classmate run your API without giving full access to your home directory?**  
   We used `chmod o+x "$HOME"` to allow traversal of the home directory, and `chmod 755 ~/public_api` with `chmod o+rx` on the script to allow execution, while granting `chmod o+rw` on `inventory.txt`, `sales.log`, and `inventory.lock`.
6. **Why does the sticky bit protect files in a shared drop zone?**  
   The sticky bit (`+t`) modifies directory deletion rights so that only the owner of a file (or the directory owner) can delete or rename it, even if other users have write access to the directory itself.
7. **What defensive scripting practice from this lab would you use in a real production script?**  
   Strict regular expression input validation (e.g. `[[ "$quantity" =~ ^[1-9][0-9]*$ ]]`) and anchoring file paths using absolute paths (`$(dirname "${BASH_SOURCE[0]}")`).
