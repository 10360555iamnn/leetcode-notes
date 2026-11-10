// ===== 2466 構造好字串 =====
int countGoodStrings(int low, int high, int zero, int one) {
    const int MOD = 1000000007;
    vector<int> dp(high + 1, 0);
    dp[0] = 1;                                  // 空字串
    int ans = 0;
    for (int i = 1; i <= high; i++) {
        if (i >= zero) dp[i] = (dp[i] + dp[i - zero]) % MOD;
        if (i >= one)  dp[i] = (dp[i] + dp[i - one]) % MOD;
        if (i >= low)  ans = (ans + dp[i]) % MOD;
    }
    return ans;
}

// ===== 91 解碼方法 =====
int numDecodings(string s) {
    int n = s.size();
    vector<int> dp(n + 1, 0);
    dp[0] = 1;                                  // 空字串
    for (int i = 1; i <= n; i++) {
        if (s[i - 1] != '0')                    // 單獨一個數字
            dp[i] += dp[i - 1];
        if (i >= 2) {
            int two = (s[i - 2] - '0') * 10 + (s[i - 1] - '0');
            if (two >= 10 && two <= 26)         // 兩個數字
                dp[i] += dp[i - 2];
        }
    }
    return dp[n];
}
