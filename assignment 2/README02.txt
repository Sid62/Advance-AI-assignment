CS5205: Advanced Artificial Intelligence Lab
Assignment – 2
--------------------------------------------

Student Name  : Siddhartha Srivastava
Course        : M.Tech (AI)
Institute     : IIT Patna

------------------------------------------------
PROBLEM DESCRIPTION
------------------------------------------------
This assignment is an extension of Assignment–1.

We are given a set of assignments with:
- fixed prompt requirements
- dependency constraints between assignments

The group size (number of students) and the number of prompts per student per day
are NOT provided in the input file. These values are provided through the command
line.

The objectives are:
1. Given number of students (N) and prompts per student per day (K),
   determine the minimum number of days required to complete all assignments.

2. Given number of students (N) and a deadline in days (M),
   determine the minimum number of prompts per student per day required.

3. Solve the above two problems under an additional constraint:
   - Students start work at 6 AM.
   - Solutions of completed assignments are shared only the next day at 6 AM.
   (This is referred to as the “6 AM rule”.)

------------------------------------------------
INPUT FILE FORMAT
------------------------------------------------
The input file contains ONLY assignment details.

Comment lines start with '%' and are ignored.

Assignment format:
A <assignment-id> <prompt-cost> <dependency1> <dependency2> ... 0

Example:
A 4 3 7 2 0

This means:
Assignment 4 requires 3 prompts and depends on assignments 7 and 2.

NOTE:
- The input file does NOT contain number of students or prompts per day.
- All assignments must be completed in a single day by a single student.

------------------------------------------------
IMPLEMENTATION DETAILS
------------------------------------------------
Language Used : C++
File Name    : assg02.cpp

Approach:
- A backtracking-based state space search is used.
- This is necessary because greedy scheduling does not guarantee correctness
  under dependency and prompt constraints.
- The solution checks feasibility for a given number of days or prompts.
- Minimum days and minimum prompts are computed by repeated feasibility checks.

------------------------------------------------
COMPILATION INSTRUCTIONS
------------------------------------------------
Open terminal in the directory containing assg02.cpp and run:

g++ assg02.cpp -o assg02

This will generate:
assg02.exe   (on Windows)
assg02       (on Linux)

------------------------------------------------
EXECUTION INSTRUCTIONS
------------------------------------------------

General format:
./assg02 <inputfile> <N> <K> <mode> [days]

On Windows PowerShell:
.\assg02.exe <inputfile> <N> <K> <mode> [days]

------------------------------------------------
MODES
------------------------------------------------

Mode 1:
Find minimum number of days.

Command:
.\assg02.exe input.txt 3 5 1

Meaning:
- 3 students
- 5 prompts per student per day
- Find minimum days required

------------------------------------------------

Mode 2:
Find minimum prompts per student per day.

Command:
.\assg02.exe input.txt 3 0 2 4

Meaning:
- 3 students
- Complete all assignments within 4 days
- Find minimum prompts per student per day

------------------------------------------------

Mode 3:
Apply 6 AM dependency sharing rule.

Command:
.\assg02.exe input.txt 3 5 3 4

Meaning:
- 3 students
- 5 prompts per student per day
- Dependencies become available only the next day at 6 AM
- Deadline = 4 days

------------------------------------------------
OUTPUT
------------------------------------------------
The program prints:
- Minimum number of days required, OR
- Minimum prompts per student per day required

If completion is impossible under given constraints, output is:
-1

------------------------------------------------
IMPORTANT NOTES
------------------------------------------------
- A greedy approach is insufficient due to combinatorial scheduling constraints.
- Backtracking ensures correctness by exploring all valid schedules.
- This implementation correctly handles dependency chains, prompt limits,
  and parallel execution by multiple students.


