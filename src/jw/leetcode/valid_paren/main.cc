#include <string>
#include <string.h>
#include <iostream>
#include <unordered_map>
#include <map>

using namespace std;
class Solution {
	public:
		class Key {
			public:
			string str;
			int stack;
			bool operator<(const Key &r) const {
					if (stack == r.stack) {
						return (str < r.str);
					}
					else {
						return (stack < r.stack);
					}
			}
		};
		struct multikey_less : public std::binary_function<Key, Key, bool>
{
    bool 
    operator()(const Key &mkey1, const Key &mkey2 ) const 
    {
        return mkey1.operator<(mkey2); // mkey1 < mkey2;
    }
};
		map<Key, bool, multikey_less> cache{};
		//unordered_map<Key, bool, multikey_less> cache{};
		int cnt{};
		bool dfs(string s, int n){
			Key key;
			key.str = s; key.stack = n;
			if (cache.find(key) != cache.end()) return cache[key];
			bool ret;
			if (s == "") {
				if (n == 0) { ret = true; goto end; };
				ret = false;
				goto end;
			}

			if (s[0] == '*') {
				cnt++;
				string sub;

				sub = s.substr(1, s.size() - 1);
				ret = dfs(sub, n);
				if (ret) goto end;

				sub = s.substr(1, s.size() - 1);
				sub.insert(0, "(");
				ret = dfs(sub, n);
				if (ret) goto end;

				sub = s.substr(1, s.size() - 1);
				sub.insert(0, ")");
				ret = dfs(sub, n);
				if (ret) goto end;

				goto end;
			}

			if (s[0] == '(') n++;

			else if (s[0] == ')') {
				if (n <= 0) { ret = false; goto end; }
				n--;
			}
			ret = dfs(s.substr(1, s.size() - 1), n);
end:
			cache[key] = ret;
			return ret;
		}
		bool checkValidString(string s) {
			return dfs(s, 0);
		}
};
int main() {
	Solution sl;
	cout << sl.checkValidString("(((((*(()((((*((**(((()()*)()()()*((((**)())*)*)))))))(())(()))())((*()()(((()((()*(())*(()**)()(())") << endl;
	cout << sl.cnt << endl;
	return 0;
}
