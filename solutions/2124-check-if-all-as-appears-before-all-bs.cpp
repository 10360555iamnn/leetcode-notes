// ===== 做法一：檢查每一對 O(n²) =====
class Solution {
public:
    bool checkString(string s) {
        int n = s.size();
        for (int i = 0; i < n; i++)              // 檢查每一對 (i, j)
            for (int j = i + 1; j < n; j++)
                if (s[i] == 'b' && s[j] == 'a') return false;   // b 在 a 前面
        return true;
    }
};

// ===== 做法二：找相鄰的 ba O(n) =====
class Solution {
public:
    bool checkString(string s) {
        for (int i = 0; i + 1 < s.size(); i++)
            if (s[i] == 'b' && s[i + 1] == 'a')   // 相鄰出現 ba
                return false;
        return true;
    }
};
