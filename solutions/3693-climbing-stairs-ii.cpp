// ===== 記憶化搜尋 =====
vector<int> memo;   // 初始化成 -1
int dfs(int j, vector<int>& costs) {
    if (j == 0) return 0;
    if (memo[j] != -1) return memo[j];
    int best = INT_MAX;
    for (int k = 1; k <= 3 && j - k >= 0; k++)
        best = min(best, dfs(j - k, costs) + costs[j - 1] + k * k);
    return memo[j] = best;
}

// ===== 由下而上 DP =====
class Solution {
public:
    int climbStairs(int n, vector<int>& costs) {
        vector<int> dp(n + 1, INT_MAX);
        dp[0] = 0;
        for (int j = 1; j <= n; j++) {
            for (int k = 1; k <= 3 && j - k >= 0; k++) {
                dp[j] = min(dp[j], dp[j - k] + costs[j - 1] + k * k);
            }
        }
        return dp[n];
    }
};

// ===== 滾動變數 O(1) 空間 =====
int climbStairs(int n, vector<int>& costs) {
    const int INF = 1000000000;
    int a = INF, b = INF, c = 0;   // dp[j-3], dp[j-2], dp[j-1]
    for (int j = 1; j <= n; j++) {
        int x = costs[j - 1];
        int cur = min({c + x + 1, b + x + 4, a + x + 9});
        a = b; b = c; c = cur;
    }
    return c;
}
