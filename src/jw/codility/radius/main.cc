// you can use includes, for example:
// #include <algorithm>
#include <stdio.h>
// you can write to stdout for debugging purposes, e.g.
// cout << "this is a debug message" << endl;

int N;

bool isOverlap(int x1, int x2, int y1, int y2) {
    //printf("%d %d %d %d\n", x1, y1, x2, y2);
    if (x1 <= y2 && y1 <= x2) return true;
    return false;
}
class IntervalTree {
    public:
    bool insert(int s, int e);
    int search(int s, int e);
    int start, end, max;
    IntervalTree *l, *r;
};

bool IntervalTree::insert(int s, int e) {
    bool max_updated = false;

    if (s <= start) {
        if (l) {
            if(l->insert(s, e)) max_updated = true;
        }
        else {
            //cout << "left insert" << endl;
            l = new IntervalTree();
            l->start = s;
            l->end = e;
            l->max = s;
        }
    }
    else {
        if (r) {
            if(r->insert(s, e)) {
                max = s;
                max_updated = true;
            }
        }
        else{
            //cout << "right insert" << endl;
            r = new IntervalTree();
            r->start = s;
            r->end = e;
            r->max = s;
            if (s > start) {
                max = s;
                max_updated = true;
            }
        }
    }
    return max_updated;
}

int IntervalTree::search(int s, int e) {
    int ret{};
    if (isOverlap(s, e, start, end)) ret++;
    if (r) ret += r->search(s, e);
    if (l) ret += l->search(s, e);
    return ret;
}

IntervalTree *head;

void insert(int s, int e) {
    if (head == nullptr) {
        head = new IntervalTree();
        head->start = s;
        head->end = e;
        head->max = s;
        return ;
    }
    head->insert(s, e);
}
int search(int s, int e) {
    if (head == nullptr) return 0;
    return head->search(s, e);
}

int solution(vector<int> &A) {
    // write your code in C++14 (g++ 6.2.0)
    vector<int> s{}, e{};
    N = A.size();
    unsigned long long int sum{};
    for (int i = 0 ; i < N ; i++) {
        s.push_back(i - A[i]);
        e.push_back(i + A[i]);
    }
    for (int i = 0 ; i < N ; i++) {
        sum += search(s[i], e[i]);
        insert(s[i], e[i]);
    }

    if (sum > 10000000) return -1;
    return (int)sum;
}
