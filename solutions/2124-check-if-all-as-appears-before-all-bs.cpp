// ===== 找相鄰的 ba O(n) =====
class Solution {
public:
    bool checkString(string s) {
        for (int i = 0; i + 1 < s.size(); i++)
            if (s[i] == 'b' && s[i + 1] == 'a')   // 相鄰出現 ba
                return false;
        return true;
    }
};
