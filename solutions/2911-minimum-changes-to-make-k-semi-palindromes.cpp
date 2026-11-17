// ===== 因數表 + cost 預處理 + 切段 DP =====
class Solution {
public:
    int minimumChanges(string s, int k) {
        int n = s.size(), INF = INT_MAX / 2;
        vector<vector<int>> divs(n + 1);          // 因數表
        for (int d = 1; d < n; d++)
            for (int len = 2 * d; len <= n; len += d)
                divs[len].push_back(d);
        vector<vector<int>> cost(n, vector<int>(n, INF));
        for (int l = 0; l < n; l++)
            for (int r = l + 1; r < n; r++) {
                for (int d : divs[r - l + 1]) {
                    int c = 0;
                    for (int g = 0; g < d; g++)
                        for (int i = l + g, j = r - d + 1 + g; i < j; i += d, j -= d)
                            if (s[i] != s[j]) c++;
                    cost[l][r] = min(cost[l][r], c);
                }
            }
        vector<vector<int>> dp(n + 1, vector<int>(k + 1, INF));
        dp[0][0] = 0;
        for (int i = 2; i <= n; i++)
            for (int j = 1; j <= k; j++)
                for (int p = 0; p + 2 <= i; p++)
                    dp[i][j] = min(dp[i][j], dp[p][j - 1] + cost[p][i - 1]);
        return dp[n][k];
    }
};
