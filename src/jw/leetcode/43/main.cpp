class Solution {
public:
    int max(int a, int b) {
        if (a > b) return a;
        return b;
    }
    string add(string num1, string num2) {
        int borrow{};
        std::reverse(num1.begin(), num1.end());
        std::reverse(num2.begin(), num2.end());
        string ret{};
        for (int i = 0 ; i < max(num1.size(), num2.size()) ; i++) {
            int val1{}, val2{};
            if (i <= num1.size() - 1) val1 = num1[i] - '0';
            if (i <= num2.size() - 1) val2 = num2[i] - '0';
            auto output = val1 + val2 + borrow;
            borrow = 0;
            if (output >= 10) {
                borrow = output / 10;
                output -= 10;
            }
            ret.push_back(output + '0');
        }
        if (borrow) ret.push_back(borrow + '0');
        std::reverse(ret.begin(), ret.end());
        return ret;
    }
    string multiply(string num1, string num2) {
        string ret{"0"};
        std::reverse(num2.begin(), num2.end());
        for (int i = 0 ; i < num2.size() ; i++) {
            string cur{"0"};
            for (int j = 0 ; j < num2[i] - '0' ; j++) {
                cur = add(cur, num1);
            }
            for (int j = 0 ; j < i ; j++)
                cur.push_back('0');
            ret = add(ret, cur);
        }
      
        /* Remove successive zeros */
        while (1) {
            bool prv_was_zero = false;
            for (int i = 0 ; i < ret.size() ; i++) {
                if (ret[i] != '0') return ret;
                if (prv_was_zero && ret[i] == '0') {
                    ret.erase(i);
                    return ret;
                }
                if (ret[i] == '0')
                    prv_was_zero = true;
            }
            break;
        }
        return ret;
    }
};
