CS5205: Advanced Artificial Intelligence Lab - Assignment 1
==========================================================

PROGRAM: assg01.cpp
------------------

DESCRIPTION:
This program solves the multi-student assignment scheduling problem with 
dependencies and prompt limits. It uses backtracking to enumerate ALL valid 
schedules that complete all assignments within M days.

COMPILATION:
------------
Linux/Mac:
  g++ -o assg01 assg01.cpp -std=c++11
  OR
  g++ -O2 -o assg01 assg01.cpp -std=c++11  (optimized)

Windows (MinGW):
  g++ -o assg01.exe assg01.cpp -std=c++11

RUNNING:
--------
./assg01 input01.txt 3
./assg01 input02.txt 2  
./assg01 input03.txt 4

USAGE FORMAT:
<executable> <input-filename> <number-of-days>

SAMPLE COMMANDS:
./assg01 input01.txt 3
./assg01 input02.txt 2
./assg01 input03.txt 4

INPUT FORMAT:
-------------
N <number>           # Number of students
K <number>           # Prompts per student per day
A <id> <prompts> <dep1> <dep2> ... 0
                     # Assignment ID, prompt cost, dependencies (0 terminates)

TEST CASES PROVIDED:
-------------------
input01.txt  - Chain dependencies (12 assignments)
input02.txt  - Parallel dependencies (10 assignments)  
input03.txt  - Complex tree structure (15 assignments)

OUTPUT:
-------
- Prints each valid schedule with Day/Student/Assignment mapping
- Counts total number of valid schedules
- Handles all constraints: dependencies, prompt limits, max days


