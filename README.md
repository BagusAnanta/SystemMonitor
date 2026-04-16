# Simple System Monitor 

![Sysmon Screen Shoot Program](Sysmon/Sysmon.png "Sysmon Image")

A lightweight system monitoring tools write at C, inspired by htop (without progress list). 
This project displays real-time system information such as CPU usage, Disk usage, Memory usage and Swap usage directory in the terminal.
I create this because learn Low Level Programming, but yeah I said this semi Low Level Programming and if you get something fishy or wrong I'm say sorry maybe you can inform to me haha :D.

---

## Feature

- Real-time CPU usage (based on '/proc/stat')
- Memory monitoring (MemAvailable, MemTotal, MemFree, Memused)
- Disk usage (using 'statvfs' libc)
- Swap usage monitoring
- Dynamic progress bars
- Fullscreen terminal mode 
- Graceful exit handling (SIGINT support)


---

## Tech Stack

- Language : C
- OS : Linux
- Library : 
  - stdio.h
  - stdlib.h
  - string.h
  - unistd.h
  - sys/statvfs.h
  - signal.h

---

## Installation & Run

this system run only linux operating system, and gcc with requirement :
  - All linux with readable permission at /proc
  - ANSI Terminal support
  - gcc package (for C compiler), at least gcc 14.2.0 version

if all requirement already at your system, you can go into next step


- Step 1 : recompile all

  ```bash
  gcc *.c -o sysmon
  ./sysmon
  ```

- Step 2 : run sysmon

  if sysmon is already, just run a file :

  ```bash
  ./sysmon
  ```
