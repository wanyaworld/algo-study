#include <iostream>
#include <vector>
#include <stdlib.h>
#include <unistd.h>

using namespace std;

class Solution {
	public:
		int min(int a, int b) {
			if (a < b) return a;
			return b;
		}
		int dnc(vector<int>& vec, int s, int e) {
			if (s >= e) return 0;
			int mid = (s + e) / 2;
			int l_max = dnc(vec, s, mid);
			int r_max = dnc(vec, mid + 1, e);
			int max;
			if (r_max > l_max) max = r_max;
			else max = l_max;

			int i = mid, j = mid, min_h = vec[mid];

			while (1) {
				int h;
				if (i <= s && j >= e) break;
				if (j >= e) {
				  i--;
					h = min(min_h, vec[i]);
				}
				else if (i <= s) {
					j++;
					h = min(min_h, vec[j]);
				}
				else if (i <= s || (vec[i - 1] <= vec[j + 1] && j < e)) {
					j++;
					h = min(min_h, vec[j]);
				}
				else if (j >= e || (vec[i - 1] >= vec[j + 1] && i > s)) {
					i--;
					h = min(min_h, vec[i]);
				}
				else {
					break;
				}
				min_h = h;
				int w = (j - i);
				int tmp = w * h;
				if (tmp > max) max = tmp;
			}
			return max;
		}
		int maxArea(vector<int>& height) {
			return dnc(height, 0, height.size() - 1);
		}
};

int main() {
	vector<int> v {1,8,100,2,100};
	Solution sl;
	cout << sl.maxArea(v) << endl;
	return 0;
}
