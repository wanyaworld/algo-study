class Solution {
public:
    unordered_map<long long int, int> cache{};
    int combination(int n, int r) {
	    if(n==r || r==0){
		    return 1;
	    }
        long long int key = n;
        key = key << 32;
        key += r;
        if (cache.find(key) != cache.end()) return cache[key];
        long long int ret = (combination(n-1,r-1) + combination(n-1, r)) % 1000000007;
        cache[key] = (int)ret;
        return (int)ret;
    }
    int dupCombination(int a, int b) {
        return combination(a + b - 1, b);
    }
    int numWays(string s) {
        int n = s.size();
        int n_ones{};
        for (int i = 0 ; i < n ; i++) {
            if (s[i] == '1') n_ones++;
        }
        if (n_ones % 3 != 0) return 0;
        if (n == 3) return 1;
        if (n < 3) return 0;
        if (n_ones == 0) {
            return dupCombination(3, n - 3);
        }
        int idx_1 = n_ones / 3 - 1;
        int idx_2 = n_ones / 3 * 2 - 1;
        int i{}, j{};
        for ( ; idx_1 >= 0 ; i++ ) { if (s[i] == '1') idx_1--;}
        for ( ; idx_2 >= 0 ; j++) { if (s[j] == '1') idx_2--;}
        i--;
        j--;
        int cnt1{}, cnt2{};
        for ( ; ; i++) {
            if (s[i + 1] == '1') break;
            cnt1++;
        }
        for ( ; ; j++) {
            if (s[j + 1] == '1') break;
            cnt2++;
        }
        int ret = (cnt1 + 1) % 1000000007;
        return (unsigned long long int)ret * (cnt2 + 1) % 1000000007;
    }
};
