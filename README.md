# Operating System Assignments

## 1. **Inline Assembly and `rdtsc`**
   - Use inline assembly in C to add values to CPU registers and memory, and read the time-stamp counter (`rdtsc`) value into memory.

## 2. **Assembly String Input with `sys_read`**
   - Implement the `sys_read` system call in assembly to read a string of less than 100 characters.

## 3. **Calculating Pi with `pthread`**
   - Use `pthread` to create multiple threads that collaboratively compute the value of Pi using a numerical method (e.g., Monte Carlo or Leibniz series).

## 4. **Real-Time CPU Temperature Monitoring with `strace`**
   - Use `strace` to monitor system calls and retrieve CPU core temperature values from sensor files. Calculate and display the real-time average temperature of all CPU cores.

## 5. **Peterson's Solution with Atomic and Non-Atomic Operations**
   - Implement Peterson's solution for mutual exclusion and compare two versions:
     1. Using atomic operations.
     2. Without atomic operations.
   - Evaluate the correctness of both versions, describe the execution flow, and discuss potential race conditions.

## 6. **Spinlock and Critical Section Measurement**
   - Implement spinlock mechanisms and measure how many times each CPU enters the critical section.
   - Compare the differences between your spinlock implementation and the implementations found in GNU's and C11's spinlock standards.
