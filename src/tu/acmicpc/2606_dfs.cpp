#include<iostream>
#include<vector>

using namespace std;

int n, e, count=0;
bool visited[100] = {0,};
bool v[100][100] = {0,};
vector<int> s;

void solve(int cur);

int main () {
    cin >> n;
    cin >> e;

    for (int i=0; i<e; i++) {
        int idx, adj;
        cin >> idx;
        cin >> adj;

        v[idx-1][adj-1] = true;
        v[adj-1][idx-1] = true;
    }
    
    s.push_back(0);
    visited[0] = true;

    solve(0);

    cout << count << endl;
}

void solve(int cur) {
    for (int i=0; i<n; i++) {
        if (v[cur][i] && !visited[i]) {
            visited[i] = true;
            count++;
            solve(i);
        }
    }
    return ;
}
