class Solution {
public:
    int longestSubstring(string s, int k) {
        if(s.size()==0||s.size()<k)
        return 0;
    
        unordered_map<char,int>mp;
        for(int i=0;i<s.size();i++)
            mp[s[i]]++;

        int mid=0;

        while(mid<s.size() and mp[s[mid]]>=k)
            mid++;

        if(mid==s.size())
            return mid;

        int left=longestSubstring(s.substr(0,mid),k);
        int right=longestSubstring(s.substr(mid+1),k);

        return max(left,right);
        }
};
