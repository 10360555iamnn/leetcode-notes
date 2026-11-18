// ===== 兩兩一組 O(n) =====
class Solution {
public:
    int minChanges(string s) {
        int ans = 0;
        for (int i = 0; i < s.size(); i += 2)   // 兩兩一組
            if (s[i] != s[i + 1]) ans++;        // 不同就要改一次
        return ans;
    }
};
