EV Charging Station Scheduling – Assignment 4
👨‍💻 Student Assignment – Advanced AI Lab

This project solves a scheduling problem for an electric vehicle (EV) charging station using the Z3 SMT Solver in Python.

The goal is to assign vehicles to charging ports in such a way that:

All vehicles finish charging before departure

No two vehicles use the same port at the same time

Charging is continuous (no interruption)

Total charging cost is minimized

📌 Problem Description

A charging station has:

K charging ports

Each port has a different charging speed

Faster ports cost more per unit time

Each vehicle provides:

Arrival time (ai)

Departure time (di)

Required charging time on slowest port (ci)

If a vehicle uses port k, then its charging time becomes:

ceil(ci / k)

Our task is to find the most cost-effective schedule.

📁 Files in This Project
1️⃣ genTestcases.py

This file generates random test cases.

It:

Asks how many test cases you want

Generates random values for ports, prices, and vehicles

Saves everything into input.txt

To run:

python genTestcases.py

Enter the number of test cases when asked.

It will generate:

input.txt
2️⃣ assg04.py

This file:

Reads data from input.txt

Uses Z3 to model constraints

Finds optimal schedule

Prints results for each test case

To run:

python assg04.py
📄 Input File Format (input.txt)
t
K
price list
number_of_vehicles
vehicle_id arrival departure charge_time
...

Example:

2
4
8 20 29 30
4
1 17 24 15
2 0 20 15
3 11 31 5
4 5 16 8
⚙ Constraints Used in Model

For each vehicle:

Port must be between 1 and K

Start time ≥ arrival

Finish time ≤ departure

Duration = ceil(ci / port)

For vehicles on same port:

They must not overlap

Cost is calculated as:

duration × price_of_port

We use Z3 Optimize() to minimize total cost.

🧠 How the Solver Works

Create symbolic variables for:

port

start time

duration

Add constraints:

Arrival constraint

Departure constraint

Charging time formula

No overlap condition

Minimize total cost

Print solution

▶ Example Output
--- Test Case 1 ---
Total Cost: 340
Vehicle 1 Port: 4 Start: 17 Duration: 4
Vehicle 2 Port: 4 Start: 10 Duration: 4
Vehicle 3 Port: 1 Start: 21 Duration: 5
Vehicle 4 Port: 4 Start: 14 Duration: 2

✅ Why Output Is Correct

The solution guarantees:

All vehicles are fully charged

No time overlaps

All constraints satisfied

Cost is minimum possible

Z3 ensures mathematical correctness.

🛠 Requirements

Python 3

Z3 Solver

Install Z3 using:

pip install z3-solver
🎯 What This Assignment Demonstrates

Constraint Modeling

Scheduling Problems

Optimization using SMT

Real-world problem solving with Z3

📌 How To Run Complete Flow

Step 1:

python genTestcases.py

Step 2:

python assg04.py 
