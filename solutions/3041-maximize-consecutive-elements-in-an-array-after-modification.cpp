// ===== 排序 + 雜湊表 DP =====
class Solution {
public:
    int maxSelectedElements(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        unordered_map<int, int> f;   // f[v]：以 v 結尾的最長連續長度
        int ans = 0;
        for (int x : nums) {
            f[x + 1] = f[x] + 1;      // 把 x 加 1，接在 x 後面（先算！）
            f[x] = f[x - 1] + 1;      // x 不變，接在 x - 1 後面
            ans = max({ans, f[x], f[x + 1]});
        }
        return ans;
    }
};

// ===== 計數排序 O(n + M) =====
class Solution {
public:
    int maxSelectedElements(vector<int>& nums) {
        int M = *max_element(nums.begin(), nums.end());
        vector<int> cnt(M + 1, 0), f(M + 3, 0);
        for (int x : nums) cnt[x]++;          // 計數：每個值出現幾次
        int ans = 0;
        for (int v = 1; v <= M; v++)          // 從小到大，等於排好序
            for (int k = 0; k < cnt[v]; k++) {
                f[v + 1] = f[v] + 1;
                f[v] = f[v - 1] + 1;
                ans = max({ans, f[v], f[v + 1]});
            }
        return ans;
    }
};
