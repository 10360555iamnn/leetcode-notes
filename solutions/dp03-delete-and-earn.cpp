// ===== 桶子 + 打家劫舍 =====
int deleteAndEarn(vector<int>& nums) {
    int m = *max_element(nums.begin(), nums.end());
    vector<int> sum(m + 1, 0);
    for (int x : nums) sum[x] += x;      // 裝進桶子
    int a = 0, b = 0;                    // 打家劫舍
    for (int v = 1; v <= m; v++) {
        int c = max(b, a + sum[v]);
        a = b;
        b = c;
    }
    return b;
}
