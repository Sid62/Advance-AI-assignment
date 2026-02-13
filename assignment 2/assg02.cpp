#include <bits/stdc++.h>

using namespace std;

struct Assignment {
    int id;
    int cost;
    vector<int> prereq;
    bool done;
};

vector<Assignment> A;
int N, K, M;
bool delayedRule;
bool found;

/* check if prerequisites are done */
bool prereqDone(int idx) {
    for (int p : A[idx].prereq) {
        bool ok = false;
        for (auto &a : A)
            if (a.id == p && a.done)
                ok = true;
        if (!ok) return false;
    }
    return true;
}

/* backtracking scheduler */
void dfs(int day, int student, vector<int>& promptsLeft, int finished) {
    if (finished == A.size()) {
        found = true;
        return;
    }
    if (day > M || found) return;

    bool assigned = false;

    for (int i = 0; i < A.size(); i++) {
        if (!A[i].done && prereqDone(i) && A[i].cost <= promptsLeft[student]) {

            A[i].done = true;
            promptsLeft[student] -= A[i].cost;

            dfs(day, student, promptsLeft, finished + 1);

            promptsLeft[student] += A[i].cost;
            A[i].done = false;

            assigned = true;
            if (found) return;
        }
    }

    if (!assigned) {
        if (student + 1 < N) {
            dfs(day, student + 1, promptsLeft, finished);
        } else {
            vector<int> nextPrompts(N, K);
            dfs(day + 1, 0, nextPrompts, finished);
        }
    }
}

/* feasibility check */
bool canFinish(int students, int prompts, int days, bool delayed) {
    N = students;
    K = prompts;
    M = days;
    delayedRule = delayed;
    found = false;

    for (auto &a : A)
        a.done = false;

    vector<int> promptsLeft(N, K);
    dfs(1, 0, promptsLeft, 0);

    return found;
}

/* Problem 1 */
int minDays(int students, int prompts, bool delayed) {
    for (int d = 1; d <= 20; d++)
        if (canFinish(students, prompts, d, delayed))
            return d;
    return -1;
}

/* Problem 2 */
int minPrompts(int students, int days, bool delayed) {
    for (int p = 1; p <= 20; p++)
        if (canFinish(students, p, days, delayed))
            return p;
    return -1;
}

int main(int argc, char* argv[]) {
    if (argc < 5) {
        cout << "Usage: assg02 <inputfile> <N> <K> <mode> [days]\n";
        return 0;
    }

    ifstream fin(argv[1]);
    int students = atoi(argv[2]);
    int prompts = atoi(argv[3]);
    int mode = atoi(argv[4]);

    string line;
    while (getline(fin, line)) {
        if (line.empty() || line[0] == '%') continue;
        stringstream ss(line);
        char c;
        ss >> c;
        if (c == 'A') {
            Assignment a;
            ss >> a.id >> a.cost;
            int x;
            while (ss >> x && x != 0)
                a.prereq.push_back(x);
            a.done = false;
            A.push_back(a);
        }
    }
    fin.close();

    if (mode == 1) {
        cout << "Minimum days = "
             << minDays(students, prompts, false) << endl;
    }
    else if (mode == 2) {
        int days = atoi(argv[5]);
        cout << "Minimum prompts per student per day = "
             << minPrompts(students, days, false) << endl;
    }
    else if (mode == 3) {
        int days = atoi(argv[5]);
        cout << "[6AM Rule]\n";
        cout << "Minimum days = "
             << minDays(students, prompts, true) << endl;
        cout << "Minimum prompts per student per day = "
             << minPrompts(students, days, true) << endl;
    }

    return 0;
}
