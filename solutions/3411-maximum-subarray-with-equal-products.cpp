// ===== 滑動視窗 + 質數最後位置 O(n) =====
class Solution {
public:
    int maxLength(vector<int>& nums) {
        int primes[4] = {2, 3, 5, 7};
        int last[4] = {-1, -1, -1, -1};   // 每個質數最後出現的位置
        int ans = 2, left = 0;            // 任兩個數一定成立，答案至少 2
        for (int right = 0; right < nums.size(); right++) {
            for (int j = 0; j < 4; j++) {
                if (nums[right] % primes[j] == 0) {   // 有這個質數
                    left = max(left, last[j] + 1);   // 踢掉上一個有它的數
                    last[j] = right;
                }
            }
            ans = max(ans, right - left + 1);
        }
        return ans;
    }
};
