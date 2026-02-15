# Advance AI Lab – Assignment 3  
## DFS vs DFBB vs A* Search Algorithms Comparison

---

# 📌 1. Problem Overview

This program implements and compares three search algorithms:

- Depth First Search (DFS)
- Depth First Branch and Bound (DFBB)
- A* Search Algorithm

The goal is to:

1. Develop a good heuristic function.
2. Use that heuristic in DFBB and A*.
3. Compare number of nodes expanded in:
   - DFS
   - DFBB
   - A*

---

# 🧠 2. Approach

## 🔹 DFS (Depth First Search)

- Blind search algorithm.
- Explores one branch completely before backtracking.
- Does NOT use heuristic.
- May explore many unnecessary nodes.

---

## 🔹 DFBB (Depth First Branch and Bound)

- DFS + pruning.
- Maintains a global best cost (bound).
- If current path cost > best known cost → prune branch.
- Uses heuristic to improve pruning.

---

## 🔹 A* Algorithm

Uses evaluation function:

    f(n) = g(n) + h(n)

Where:
- g(n) = cost from start to current node
- h(n) = heuristic estimate to goal

- Uses priority queue.
- Expands node with smallest f(n).
- Most efficient when heuristic is strong.

---

# 🎯 3. Heuristic Function

The heuristic estimates the remaining cost to reach the goal.

A good heuristic should be:

- Admissible (never overestimate)
- Consistent
- Fast to compute

This heuristic is used in:
- DFBB
- A*

DFS does not use heuristic.

---

# ⚙️ 4. Running Process (Step-by-Step Guide)

## ✅ Step 1: Open Terminal

Open PowerShell or Command Prompt.

Navigate to project directory:

cd "C:\Users\siddh\Downloads\advance ai lab\assignment 3"


---

## ✅ Step 2: Compile the Program

Make sure g++ is installed.

Compile using:



g++ -std=c++17 assg03.cpp -o assg03


After compilation, you will get:



assg03.exe


---

## ✅ Step 3: Run the Program (IMPORTANT for PowerShell)

PowerShell does NOT run executables from current folder directly.

❌ This will NOT work:



assg03.exe input.txt ...


✅ Correct way:



.\assg03.exe input.txt 1 1 5 3 2 3 4
