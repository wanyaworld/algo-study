#include <vector>
#include <string>
#include <iostream>

using namespace std;

class Solution {
public:
    class Elem {
        public:
        enum class Type {dot, star, num};
        Type t;
        char c;
    };
    bool dfs(string& s, int i, vector<Elem> &p, int j) {
        if (i > (int)s.size() - 1) {
            if (j > (int)p.size() - 1)
                return true;
            else { 
                for ( ; j <= p.size() - 1 ; j++) {
                  if (p[j].t != Elem::Type::star) return false;
                }
                return true;
            }
        }
        if (j > (int)p.size() - 1)
            return false;
        
        if (p[j].t == Elem::Type::dot)
            return dfs(s, i + 1, p, j + 1);
        
        else if (p[j].t == Elem::Type::num) {
            if (s[i] == p[j].c)
                return dfs(s, i + 1, p, j + 1);
            else
                return false;
        }
        
        else {
            if (dfs(s, i, p, j + 1)) return true;
            int cnt = {};
            while(1) {
                if (i + cnt > s.size()) break;
                if (i + cnt <= s.size() - 1) {
                  if (p[j].c != s[i + cnt] && p[j].c != '.') break;
                }
                if (dfs(s, i + cnt, p, j + 1)) return true;
                cnt++;
            }
            return dfs(s, i + cnt, p, j + 1);
        }
        return false;
    }
    bool isMatch(string s, string p) {
        vector<Elem> v;
        char prv;
        for (int i = 0 ; i < p.size() ; i++) {
            Elem e;
            if (p[i] == '*') {
                if (prv == '.') {
                    e.t = Elem::Type::star;
                    e.c = prv;
                    v.push_back(e);
                }
                else {
                    e.t = Elem::Type::star;
                    e.c = prv;
                    v.push_back(e);
                }
            }
            else if (p[i] == '.') {
                if (i + 1 < p.size()) {
                    if (p[i + 1] == '*') {
                        
                    }
                    else {
                        e.t = Elem::Type::dot;
                        v.push_back(e);
                        
                    }
                }
                else {
                    e.t = Elem::Type::dot;
                    v.push_back(e);
                }
            }
            else {
                if (i + 1 < p.size()) {
                    if (p[i + 1] != '*') {
                        e.t = Elem::Type::num;
                        e.c = p[i];
                        v.push_back(e);
                    }
                }
                else {
                    e.t = Elem::Type::num;
                    e.c = p[i];
                    v.push_back(e);
                }
            }
            prv = p[i];
        }
        return dfs(s, 0, v, 0);
    }
};



int main() {
  string s = "aab";
	string p = "c*a*b";
	Solution sl;
	bool ret = sl.isMatch(s, p);
  cout << ret << endl;
	return 0;
}	
