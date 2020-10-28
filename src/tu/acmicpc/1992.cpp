#include<iostream>
#include<vector>
#include<string>

using namespace std;

char image[66][66];

string solve(int,int,int,int*);

int main () {
    int n, total;
    cin >> n;

    for (int i=0; i<n; i++) {
        for (int j=0; j<n; j++)
            cin >> image[i][j];
    }

    cout << solve(n, 0, 0, &total) << endl;

}

string solve (int size, int row_l, int col_l, int *sum) {
    int sum_rl, sum_rr, sum_cl, sum_cr;
    string one="1", zero="0";

    if (size == 1) {
        *sum = (int)(image[row_l][col_l]-'0');
        return string(1, image[row_l][col_l]);
    }

    string ret_rl = solve(size/2, row_l, col_l, &sum_rl);
    string ret_rr = solve(size/2, row_l, col_l + size/2, &sum_rr);
    string ret_cl = solve(size/2, row_l + size/2, col_l, &sum_cl);
    string ret_cr = solve(size/2, row_l + size/2, col_l + size/2, &sum_cr);

    *sum = sum_rl + sum_rr + sum_cl + sum_cr; 

    if (size == 2) {
        if (*sum > 0 && *sum < 4)
            return "(" + ret_rl + ret_rr + ret_cl + ret_cr + ")";
    } 

    if (*sum == size*size) {
        return one;
    } else if (*sum == 0) {
        return zero;
    } else {
        return "(" + ret_rl + ret_rr + ret_cl + ret_cr + ")";
    }
}
