// ===== 枚舉子陣列 O(n²) =====
class Solution {
public:
    int minimumSumSubarray(vector<int>& nums, int l, int r) {
        int n = nums.size();
        int ans = INT_MAX;                     // 還沒找到任何答案
        for (int i = 0; i < n; i++) {          // 子陣列從 i 開始
            int sum = 0;
            for (int j = i; j < n; j++) {      // 往右延伸到 j
                sum += nums[j];                // 只加新的一個數
                int len = j - i + 1;
                if (len >= l && len <= r && sum > 0)
                    ans = min(ans, sum);
            }
        }
        return ans == INT_MAX ? -1 : ans;      // 找不到就回傳 -1
    }
};
