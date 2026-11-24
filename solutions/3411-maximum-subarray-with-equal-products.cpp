// ===== 做法一：每一段都算算看 =====
class Solution {
public:
    int maxLength(vector<int>& nums) {
        int n = nums.size(), ans = 0;
        for (int i = 0; i < n; i++) {            // 每一段都算算看
            long long prod = 1;
            int g = 0, l = 1;                    // g：gcd，l：lcm
            for (int j = i; j < n; j++) {
                prod *= nums[j];
                g = gcd(g, nums[j]);
                l = lcm(l, nums[j]);
                if (prod > 25200) break;         // 2520 × 10，乘積再大也不可能相等
                if (prod == (long long)l * g)
                    ans = max(ans, j - i + 1);
            }
        }
        return ans;
    }
};

// ===== 做法二：滑動視窗 O(n) =====
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
