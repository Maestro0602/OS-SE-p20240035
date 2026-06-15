# OS Lab 9 — Vault Deadlock, Resource Ordering & Recovery

**Student Name:** Theng Van Heng  
**Student ID:** p20240035  
**Date:** Mon, Jun 15, 2026

## Overview
This lab covers deadlock conditions, simulating deadlocks via file locks (`flock`) on shared vault resources, detecting deadlocks using `ps`, resolving deadlocks using global resource ordering (Alpha-before-Beta), and implementing timeout-based recovery.

## Questions & Answers
1. **What does each `vault.lock` file represent in this lab?**  
   It represents exclusive access to a specific vault resource. A process must acquire a write lock on this file descriptor using `flock` to modify files inside that vault, preventing race conditions.
2. **Why does `flock` require every script to lock the same shared file to coordinate correctly?**  
   Because `flock` locks are advisory and associated with the underlying file description. Processes can only coordinate mutual exclusion if they check the lock status of the exact same target inode.
3. **In the local deadlock, which resource did `sync_up` hold, and which resource did it wait for?**  
   `sync_up` held `Vault Alpha`'s lock and was waiting to acquire `Vault Beta`'s lock.
4. **In the local deadlock, which resource did `sync_down` hold, and which resource did it wait for?**  
   `sync_down` held `Vault Beta`'s lock and was waiting to acquire `Vault Alpha`'s lock.
5. **Which four deadlock conditions were present in Level 3?**  
   - **Mutual Exclusion**: Vault lock files were locked exclusively.
   - **Hold and Wait**: Each process held one lock and blocked waiting for the other.
   - **No Preemption**: Locks could not be forcibly taken away by the OS or other processes.
   - **Circular Wait**: `sync_up` waited for `sync_down`'s lock, and `sync_down` waited for `sync_up`'s lock.
6. **How does the global Alpha-before-Beta ordering rule break circular wait?**  
   By forcing all processes to lock `Alpha` first, a process cannot hold `Beta` while waiting for `Alpha`. This ensures that whoever locks `Alpha` first will eventually acquire `Beta` without cyclic dependencies.
7. **Why is `flock -w` useful for recovery even though it does not prevent every deadlock?**  
   `flock -w <seconds>` sets a timeout. If a lock cannot be acquired within the timeout window, the script exits and automatically releases all other locks it holds. This breaks the hold-and-wait condition, preventing indefinite freezes.
8. **Why should you check for stuck processes before finishing a deadlock lab?**  
   Because stuck processes keep holding locks, consuming CPU/memory, and blocking subsequent drills or recovery scripts from executing correctly.
