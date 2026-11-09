// ===== 509 遞迴 =====
int fib(int n) {
    if (n < 2) return n;
    return fib(n - 1) + fib(n - 2);
}

// ===== 509 記憶化 =====
int memo[31];            // -1 代表還沒算過
int f(int n) {
    if (n < 2) return n;
    if (memo[n] != -1) return memo[n];   // 算過 → 查表
    return memo[n] = f(n - 1) + f(n - 2);
}
int fib(int n) {
    memset(memo, -1, sizeof memo);
    return f(n);
}

// ===== 509 由下而上 =====
int fib(int n) {
    if (n < 2) return n;
    vector<int> dp(n + 1);
    dp[0] = 0, dp[1] = 1;
    for (int i = 2; i <= n; i++)
        dp[i] = dp[i - 1] + dp[i - 2];
    return dp[n];
}

// ===== 509 滾動變數 =====
int fib(int n) {
    if (n < 2) return n;
    int a = 0, b = 1;        // a = F(i-2), b = F(i-1)
    for (int i = 2; i <= n; i++) {
        int c = a + b;
        a = b;
        b = c;
    }
    return b;
}

// ===== 1137 泰波那契 =====
int tribonacci(int n) {
    if (n == 0) return 0;
    if (n <= 2) return 1;
    int a = 0, b = 1, c = 1;
    for (int i = 3; i <= n; i++) {
        int d = a + b + c;
        a = b; b = c; c = d;
    }
    return c;
}

// ===== 70 爬樓梯 =====
int climbStairs(int n) {
    if (n <= 2) return n;
    int a = 1, b = 2;        // a = dp[i-2], b = dp[i-1]
    for (int i = 3; i <= n; i++) {
        int c = a + b;
        a = b;
        b = c;
    }
    return b;
}

// ===== 746 最小花費爬樓梯 =====
int minCostClimbingStairs(vector<int>& cost) {
    int n = cost.size();
    int a = 0, b = 0;        // a = dp[i-2], b = dp[i-1]
    for (int i = 2; i <= n; i++) {
        int c = min(b + cost[i - 1], a + cost[i - 2]);
        a = b;
        b = c;
    }
    return b;
}
