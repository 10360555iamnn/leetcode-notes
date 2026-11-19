// ===== 排序 O(n log n) =====
class Solution {
public:
    int minimizeSum(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        int n = nums.size();
        int a = nums[n - 1] - nums[2];   // 改最小的兩個
        int b = nums[n - 3] - nums[0];   // 改最大的兩個
        int c = nums[n - 2] - nums[1];   // 左右各改一個
        return min({a, b, c});
    }
};

// ===== 前三小、前三大 O(n) =====
class Solution {
public:
    int minimizeSum(vector<int>& nums) {
        int s1 = INT_MAX, s2 = INT_MAX, s3 = INT_MAX;  // 最小、第二小、第三小
        int l1 = INT_MIN, l2 = INT_MIN, l3 = INT_MIN;  // 最大、第二大、第三大
        for (int x : nums) {
            if (x < s1) { s3 = s2; s2 = s1; s1 = x; }
            else if (x < s2) { s3 = s2; s2 = x; }
            else if (x < s3) s3 = x;
            if (x > l1) { l3 = l2; l2 = l1; l1 = x; }
            else if (x > l2) { l3 = l2; l2 = x; }
            else if (x > l3) l3 = x;
        }
        return min({l1 - s3, l3 - s1, l2 - s2});
    }
};
