// ===== 拆成兩條直線 =====
int robLine(vector<int>& nums, int l, int r) {
    int a = 0, b = 0;              // 上一集的滾動變數
    for (int i = l; i <= r; i++) {
        int c = max(b, a + nums[i]);
        a = b;
        b = c;
    }
    return b;
}
int rob(vector<int>& nums) {
    int n = nums.size();
    if (n == 1) return nums[0];
    return max(robLine(nums, 0, n - 2),     // 不偷最後一間
               robLine(nums, 1, n - 1));    // 不偷第 0 間
}
