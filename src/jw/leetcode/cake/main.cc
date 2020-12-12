#include <algorithm>
#include <vector>
#include <iostream>

using namespace std;

class Solution {
public:
    unsigned long long int maxArea(int h, int w, vector<int>& horizontalCuts, vector<int>& verticalCuts) {
        horizontalCuts.push_back(0);
        horizontalCuts.push_back(h);
        verticalCuts.push_back(0);
        verticalCuts.push_back(w);
        
        sort(horizontalCuts.begin(), horizontalCuts.end());
        sort(verticalCuts.begin(), verticalCuts.end());
        
        unsigned long long int h_max = 0, h_prv;
        bool flag = false;
        
        for(int i = 0 ; i < horizontalCuts.size() ; i++) {
            if (flag) {
                unsigned long long int diff = horizontalCuts[i] - horizontalCuts[h_prv];
                if (diff > h_max) h_max = diff;
            }
            else {
                flag = true;
            }
            h_prv = i;
        }
        
        unsigned long long int v_max = 0, v_prv = -1;
        flag = false;
        
        for(int i = 0 ; i < verticalCuts.size() ; i++) {
            if (flag) {
                unsigned long long int diff = verticalCuts[i] - verticalCuts[v_prv];
                if (diff > v_max) v_max = diff;
            }
            else 
                flag = true;
            v_prv = i;
        }
        return h_max * v_max%1000000007;
    }
};

int main() { 
	Solution sl;
	vector<int> h = {3, 1};
	vector<int> v = {1};

	cout << sl.maxArea(5, 4, h, v) << endl;
	return 0;
}	
