#include<cstdio>
#include<iostream>
#include<vector>
#include<set>
#include<string>

using namespace std;

char board[33][6][6];
set<string> dict;

set<string> found_word;
int match_count[33];
int score[33];
string longest_word[33];

vector<pair<int,int>> tracking;

int turn;

void solve(int, pair<int,int>);

string make_str(vector<pair<int,int>>);
int score_word(string);

vector<int> iter1{0, 1, -1};
vector<int> iter2{0, 1, -1};

int main() {
    int w, b;
    char empty;
    string input_str;

    // init
    tracking.clear();
    found_word.clear();
    for (int n=0; n<33; n++) {
        for (int i=0; i<6; i++)
            for (int j=0; j<6; j++)
                board[n][i][j] = 0;

        match_count[n] = 0;
        score[n] = 0;
        longest_word[n] = "";
    }

    cin >> w;

    for (int i=0; i<w; i++) {
        cin >> input_str;
        dict.insert(input_str);
    }
    empty = cin.get();

    cin >> b;

    for (int n=0; n<b; n++) {
        for (int i=1; i <= 4; i++) {
            cin >> input_str;
            for (int j=1; j <= 4; j++) {
                board[n][i][j] = input_str.c_str()[j-1];
            }
        }
        if (n != b-1)
           empty = cin.get();
    }

    /*
    turn = 1;
    for (int i=1; i<5; i++) {
        for (int j=1; j<5; j++)
            solve(1, pair<int,int>(i,j), vector<pair<int,int>>(), vector<string> ());
    }*/
    for (int n=0; n<b; n++) {
        turn = n;
        for (int i=1; i<5; i++) {
            for (int j=1; j<5; j++)
                solve(1, pair<int,int>(i,j));
        }
        tracking.clear();
        found_word.clear();
    }

    for (int n=0; n<b; n++) {
        cout << score[n] << " " << longest_word[n] << " " << match_count[n];
        if (n != b-1)
            cout << endl;
    }

    return 0;

}


void solve(int count, pair<int,int> cur_pos) {

    tracking.push_back(cur_pos);

    string target = make_str(tracking);

    // if current word exists in dict
    if (dict.find(target) != dict.end()) {
        if (found_word.find(target) == found_word.end()) {
            match_count[turn]++;
            score[turn] += score_word(target);
            if (longest_word[turn].length() < target.length())
                longest_word[turn] = target;
            else if (longest_word[turn].length() == target.length())
                if (target.compare(longest_word[turn]) < 0)
                    longest_word[turn] = target;

            found_word.insert(target);
        }
    }

    if (count == 8) {
        tracking.pop_back();
        return;
    }

    for (auto i=iter1.begin(); i < iter1.end(); i++) {
        for (auto j=iter2.begin(); j < iter2.end(); j++) {
            if (*i == 0 && *j == 0)
                continue;

            if (board[turn][cur_pos.first+(*i)][cur_pos.second+(*j)] == 0)
                continue;

            bool containing = false;
            for(auto iter=tracking.begin(); iter < tracking.end(); iter++)
                if (iter->first == cur_pos.first+(*i) && iter->second == cur_pos.second+(*j))
                    containing = true;

            if (containing)
                continue;

            solve(count+1, pair<int,int> (cur_pos.first+(*i), cur_pos.second+(*j)));
        }
    }

    tracking.pop_back();

}

string make_str(vector<pair<int,int>> pos_vec) {
    string ret = "";

    for (auto i = pos_vec.begin(); i < pos_vec.end(); i++)
        ret.push_back(board[turn][i->first][i->second]);

    return ret;
}

int score_word(string input) {
    if (input.length() == 1 || input.length() == 2)
        return 0;
    else if (input.length() == 3 || input.length() == 4)
        return 1;
    else if (input.length() == 5)
        return 2;
    else if (input.length() == 6)
        return 3;
    else if (input.length() == 7)
        return 5;
    else if (input.length() == 8)
        return 11;
}
