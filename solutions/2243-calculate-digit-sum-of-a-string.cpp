// ===== 模擬 分組加總 =====
class Solution {
public:
    string digitSum(string s, int k) {
        while (s.size() > k) {                    // 長度大於 k 才做一輪
            string t = "";
            for (int i = 0; i < s.size(); i += k) {   // 每一組的起點
                int sum = 0;
                for (int j = i; j < i + k && j < s.size(); j++)
                    sum += s[j] - '0';            // 字元轉數字
                t += to_string(sum);              // 數字轉字串，接到後面
            }
            s = t;
        }
        return s;
    }
};
