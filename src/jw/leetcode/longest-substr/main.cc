#include <string>
#include <string.h>
#include <unordered_map>

using namespace std;

class Solution {
	public:
		int lengthOfLongestSubstring(string s) {
			int i{}, j{}, ret{};
			unordered_map<char, bool> dict;

			while (i < s.size() && j < s.size()) {
				if (dict.find(s[j]) == dict.end()) {
					dict[s[j++]] = true;	
					if (dict.size() > ret) ret = dict.size();
				}
				else {
					dict.erase(s[i++]);
				}
			}
			return ret;
		}
};

int main (){
	Solution sl;
	printf("%d\n", sl.lengthOfLongestSubstring((std::string)"anviaj"));
	return 0;
} 
