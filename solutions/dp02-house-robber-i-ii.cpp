// ===== 198 記憶化 =====
int memo[100];               // -1 代表還沒算過
int f(vector<int>& nums, int i) {
    if (i == 0) return nums[0];
    if (i == 1) return max(nums[0], nums[1]);
    if (memo[i] != -1) return memo[i];
    int skip = f(nums, i - 1);              // 不偷第 i 間
    int take = f(nums, i - 2) + nums[i];    // 偷第 i 間
    return memo[i] = max(skip, take);
}
int rob(vector<int>& nums) {
    memset(memo, -1, sizeof memo);
    return f(nums, nums.size() - 1);
}

// ===== 198 由下而上 =====
int rob(vector<int>& nums) {
    int n = nums.size();
    if (n == 1) return nums[0];
    vector<int> dp(n);
    dp[0] = nums[0];
    dp[1] = max(nums[0], nums[1]);
    for (int i = 2; i < n; i++)
        dp[i] = max(dp[i - 1], dp[i - 2] + nums[i]);
    return dp[n - 1];
}

// ===== 198 滾動變數 =====
int rob(vector<int>& nums) {
    int a = 0, b = 0;        // a = dp[i-2], b = dp[i-1]
    for (int x : nums) {
        int c = max(b, a + x);   // 不偷 / 偷
        a = b;
        b = c;
    }
    return b;
}

// ===== 213 拆成兩條直線 =====
int robLine(vector<int>& nums, int l, int r) {
    int a = 0, b = 0;              // 前一題的滾動變數
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
