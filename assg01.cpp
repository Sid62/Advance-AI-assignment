#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>

using namespace std;

struct Assignment {
    int aid;
    int cost;
    vector<int> prereq;
    bool done;
};

struct Plan {
    int day, student, aid;
};

int students, dailyPrompts, maxDays;
vector<Assignment> assnList;
vector<Plan> planPath;
int totalAssn;
long long totalPlans = 0;

// Check if all prerequisites for assignment at index i are done
bool prereqDone(int i) {
    for (int need : assnList[i].prereq) {
        bool found = false;
        for (const auto& a : assnList) {
            if (a.aid == need && a.done) {
                found = true;
                break;
            }
        }
        if (!found) return false;
    }
    return true;
}

// Count completed assignments
int countDone() {
    int cnt = 0;
    for (const auto& a : assnList) {
        if (a.done) cnt++;
    }
    return cnt;
}

// Reset all assignments to undone state
void resetState() {
    for (auto& a : assnList) {
        a.done = false;
    }
    planPath.clear();
}

// Main recursion: day, student, prompts_left_for_student, current_student_index
void makeSchedule(int day, int stuIdx, int promptsLeft, int finished) {
    if (finished == totalAssn) {
        totalPlans++;
        cout << "Schedule #" << totalPlans << ":\n";
        for (const auto& p : planPath) {
            cout << "Day " << p.day << ", Student " << p.student 
                 << ": Assignment " << p.aid << endl;
        }
        cout << "--------------------------------------------\n";
        return;
    }
    
    if (day > maxDays) return;
    
    // Try assigning work to current student
    bool didWork = false;
    for (int i = 0; i < assnList.size(); i++) {
        if (!assnList[i].done && assnList[i].cost <= promptsLeft && prereqDone(i)) {
            // Do this assignment
            assnList[i].done = true;
            planPath.push_back({day, stuIdx + 1, assnList[i].aid});
            
            makeSchedule(day, stuIdx, promptsLeft - assnList[i].cost, finished + 1);
            
            // Backtrack
            planPath.pop_back();
            assnList[i].done = false;
            didWork = true;
        }
    }
    
    // If student did some work, don't move to next student (one assignment per student per day? 
    // Wait, problem allows multiple per student if prompts allow)
    
    // Move to next student if we have more students
    if (stuIdx + 1 < students) {
        makeSchedule(day, stuIdx + 1, dailyPrompts, finished);
    } 
    // All students done for this day, move to next day
    else {
        makeSchedule(day + 1, 0, dailyPrompts, finished);
    }
}

int main(int argc, char* argv[]) {
    if (argc < 3) {
        cout << "Usage: " << argv[0] << " <input_file> <days>\n";
        return 1;
    }
    
    string file = argv[1];
    maxDays = atoi(argv[2]);
    
    ifstream fin(file);
    if (!fin) {
        cout << "File not found: " << file << endl;
        return 1;
    }
    
    string line;
    while (getline(fin, line)) {
        if (line.empty() || line[0] == '%') continue;
        
        stringstream ss(line);
        string tag;
        ss >> tag;
        
        if (tag == "N") {
            ss >> students;
        } else if (tag == "K") {
            ss >> dailyPrompts;
        } else if (tag == "A") {
            Assignment a;
            ss >> a.aid >> a.cost;
            int x;
            while (ss >> x && x != 0) {
                a.prereq.push_back(x);
            }
            a.done = false;
            assnList.push_back(a);
        }
    }
    fin.close();
    
    totalAssn = assnList.size();
    cout << "Loaded " << totalAssn << " assignments\n";
    cout << "N=" << students << ", K=" << dailyPrompts << ", M=" << maxDays << endl << endl;
    
    // Start recursion: day 1, student 1 (index 0), full prompts, 0 finished
    makeSchedule(1, 0, dailyPrompts, 0);
    
    cout << "\n========================================\n";
    cout << "Total valid schedules: " << totalPlans << endl;
    cout << "========================================\n";
    
    return 0;
}
