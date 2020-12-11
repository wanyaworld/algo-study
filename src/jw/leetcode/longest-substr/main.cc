#include <string>
#include <string.h>

using namespace std;

class Solution {
public:
    char str[5001];
    int n;
    int dnc(int s, int e) {
        if (s == e) return 1;
        if (e - s == 1) {
            if (str[s] == str[e])
                return 1;
            return 2;
        }
        int mid = (s + e) / 2;
        int l_max = dnc(s, mid);
        int r_max = dnc(mid + 1, e);
        int max;
        if (l_max > r_max) max = l_max;
        else max = r_max;
        string med{};
        int i = mid -1, j = mid + 2;
        med += str[mid];
        med += str[mid + 1];
				if (str[mid] == str[mid + 1]) med.pop_back();
        while (1) {
            if (i < s && j > e) break;
            if (i >= s && strchr(med.c_str(), (char)str[i]) == nullptr)
                med += str[i--];
            else if (j <= e && strchr(med.c_str(), (char)str[j]) == nullptr)
                med += str[j++];
            else {
                break;
            }
        }
        if (med.size() > max) max = med.size();
        return max;
    }
    int lengthOfLongestSubstring(string s) {
        
        n = s.size();
				if (n == 0) return 0;
        strcpy(str, s.c_str());
        return dnc(0, n - 1);
    }
};

int main (){
	Solution sl;
	printf("%d\n", sl.lengthOfLongestSubstring((std::string)"anviaj"));
	return 0;
} 
