#include <bits/stdc++.h>
using namespace std;

/* ===================== DATA STRUCTURES ===================== */

struct Assignment {
    int id;
    int cost;
    vector<int> prereq;
};

vector<Assignment> A;
int totalAssignments;

/* ===================== GLOBAL PARAMETERS ===================== */

int GPT_limit, GEM_limit;
int c1, c2;
int maxDays;
bool caseB;   // true → Case-B (multi per day + delayed sharing)

long long nodesDFS = 0;
long long nodesDFBB = 0;
long long nodesAStar = 0;

/* ===================== STATE ===================== */

struct State {
    vector<bool> done;
    unordered_map<int,int> completedDay;
    int day;
    int gptLeft;
    int gemLeft;
    int costSoFar;
};

/* ===================== UTILS ===================== */

bool allDone(const State &s) {
    for (bool b : s.done)
        if (!b) return false;
    return true;
}

bool prereqSatisfied(int idx, const State &s) {
    for (int p : A[idx].prereq) {
        bool found = false;
        for (int i = 0; i < totalAssignments; i++) {
            if (A[i].id == p && s.done[i]) {
                if (caseB) {
                    if (s.completedDay.at(p) >= s.day)
                        return false;
                }
                found = true;
            }
        }
        if (!found) return false;
    }
    return true;
}

/* ===================== HEURISTIC ===================== */
/* Admissible Lower Bound on remaining cost */

int heuristic(const State &s) {
    int remGPT = 0, remGEM = 0;

    for (int i = 0; i < totalAssignments; i++) {
        if (!s.done[i]) {
            if (A[i].id % 2 == 0)
                remGPT += A[i].cost;
            else
                remGEM += A[i].cost;
        }
    }

    int minDaysGPT = (GPT_limit == 0) ? 1e9 :
                     (remGPT + GPT_limit - 1) / GPT_limit;

    int minDaysGEM = (GEM_limit == 0) ? 1e9 :
                     (remGEM + GEM_limit - 1) / GEM_limit;

    int lbDays = max(minDaysGPT, minDaysGEM);

    return lbDays * (GPT_limit*c1 + GEM_limit*c2);
}

/* ===================== DFS ===================== */

bool dfs(State s) {
    nodesDFS++;

    if (allDone(s))
        return true;

    if (s.day > maxDays)
        return false;

    for (int i = 0; i < totalAssignments; i++) {
        if (!s.done[i] && prereqSatisfied(i, s)) {

            bool isGPT = (A[i].id % 2 == 0);
            int &limit = isGPT ? s.gptLeft : s.gemLeft;

            if (A[i].cost <= limit) {

                State next = s;
                next.done[i] = true;
                limit -= A[i].cost;
                next.completedDay[A[i].id] = s.day;

                if (dfs(next))
                    return true;
            }
        }
    }

    // Move to next day
    State next = s;
    next.day++;
    next.gptLeft = GPT_limit;
    next.gemLeft = GEM_limit;

    return dfs(next);
}

/* ===================== DFBB ===================== */

int bestCost;

void dfbb(State s) {
    nodesDFBB++;

    if (allDone(s)) {
        bestCost = min(bestCost, s.costSoFar);
        return;
    }

    if (s.costSoFar + heuristic(s) >= bestCost)
        return;

    if (s.day > maxDays)
        return;

    for (int i = 0; i < totalAssignments; i++) {

        if (!s.done[i] && prereqSatisfied(i, s)) {

            bool isGPT = (A[i].id % 2 == 0);
            int &limit = isGPT ? s.gptLeft : s.gemLeft;

            if (A[i].cost <= limit) {

                State next = s;
                next.done[i] = true;
                limit -= A[i].cost;
                next.completedDay[A[i].id] = s.day;

                dfbb(next);
            }
        }
    }

    // next day
    State next = s;
    next.day++;
    next.gptLeft = GPT_limit;
    next.gemLeft = GEM_limit;

    dfbb(next);
}

/* ===================== A* ===================== */

struct Compare {
    bool operator()(const State &a, const State &b) {
        return (a.costSoFar + heuristic(a)) >
               (b.costSoFar + heuristic(b));
    }
};

bool aStar() {

    priority_queue<State, vector<State>, Compare> pq;

    State start;
    start.done = vector<bool>(totalAssignments, false);
    start.day = 1;
    start.gptLeft = GPT_limit;
    start.gemLeft = GEM_limit;
    start.costSoFar = 0;

    pq.push(start);

    while (!pq.empty()) {

        State s = pq.top();
        pq.pop();

        nodesAStar++;

        if (allDone(s))
            return true;

        if (s.day > maxDays)
            continue;

        for (int i = 0; i < totalAssignments; i++) {

            if (!s.done[i] && prereqSatisfied(i, s)) {

                bool isGPT = (A[i].id % 2 == 0);
                int &limit = isGPT ? s.gptLeft : s.gemLeft;

                if (A[i].cost <= limit) {

                    State next = s;
                    next.done[i] = true;
                    limit -= A[i].cost;
                    next.completedDay[A[i].id] = s.day;

                    pq.push(next);
                }
            }
        }

        // next day
        State next = s;
        next.day++;
        next.gptLeft = GPT_limit;
        next.gemLeft = GEM_limit;
        pq.push(next);
    }

    return false;
}

/* ===================== MAIN ===================== */

int main(int argc, char* argv[]) {

    if (argc < 9) {
        cout << "Usage:\n";
        cout << "./assg03 input.txt case objective GPT GEM c1 c2 days\n";
        return 0;
    }

    ifstream fin(argv[1]);

    caseB = (atoi(argv[2]) == 2);
    int objective = atoi(argv[3]);

    GPT_limit = atoi(argv[4]);
    GEM_limit = atoi(argv[5]);

    c1 = atoi(argv[6]);
    c2 = atoi(argv[7]);

    maxDays = atoi(argv[8]);

    string line;
    while (getline(fin, line)) {
        if (line.empty() || line[0] == '%') continue;

        stringstream ss(line);
        char ch;
        ss >> ch;

        if (ch == 'A') {
            Assignment a;
            ss >> a.id >> a.cost;
            int x;
            while (ss >> x && x != 0)
                a.prereq.push_back(x);
            A.push_back(a);
        }
    }

    totalAssignments = A.size();

    State start;
    start.done = vector<bool>(totalAssignments, false);
    start.day = 1;
    start.gptLeft = GPT_limit;
    start.gemLeft = GEM_limit;
    start.costSoFar = 0;

    cout << "Running DFS...\n";
    dfs(start);

    cout << "Running DFBB...\n";
    bestCost = INT_MAX;
    dfbb(start);

    cout << "Running A*...\n";
    aStar();

    cout << "\nNode Comparison:\n";
    cout << "DFS Nodes: " << nodesDFS << endl;
    cout << "DFBB Nodes: " << nodesDFBB << endl;
    cout << "A* Nodes: " << nodesAStar << endl;

    return 0;
}
