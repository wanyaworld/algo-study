#include<iostream>
#include<queue>

using namespace std;

int main () {
    bool v[100][100] = {0,};
    queue<int> q;
    bool visited[100] = {0,};
    int n, e;
    int count = 0;

    cin >> n;
    cin >> e;

    for (int i=0; i < e; i++) {
        int idx, adj;
        cin >> idx;
        cin >> adj;
        v[idx][adj] = true;
        v[adj][idx] = true;
    }

    q.push(1);
    visited[1] = true;

    while (!q.empty()) {
        for (int i=0; i<n; i++) {
            if (v[q.front()][i] && !visited[i]) {
                q.push(i);
                count++;
                visited[i] = true;
                //cout << "visiting " << i << endl;
            }
        }
        q.pop();
    }

    cout << count << endl;

    return 0;

}
