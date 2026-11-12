// ===== 一次掃描 O(n) =====
class Solution {
public:
    int longestMonotonicSubarray(vector<int>& nums) {
        int inc = 1, dec = 1, ans = 1;   // 以 i 結尾的遞增 / 遞減長度
        for (int i = 1; i < nums.size(); i++) {
            if (nums[i] > nums[i - 1]) {
                inc++; dec = 1;
            } else if (nums[i] < nums[i - 1]) {
                dec++; inc = 1;
            } else {
                inc = 1; dec = 1;
            }
            ans = max({ans, inc, dec});
        }
        return ans;
    }
};
