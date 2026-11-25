// ===== 做法一：暴力 O(n³) =====
class Solution {
public:
    int smallestUniqueSubarray(vector<int>& nums) {   // 暴力做法：O(n³)，會超時，僅供理解
        int n = nums.size();
        for (int L = 1; L <= n; L++) {          // 長度從 1 開始試
            map<vector<int>, int> cnt;          // 每一種出現幾次
            for (int i = 0; i + L <= n; i++) {
                vector<int> sub(nums.begin() + i, nums.begin() + i + L);
                cnt[sub]++;
            }
            for (auto& [sub, c] : cnt)
                if (c == 1) return L;           // 只出現一次
        }
        return n;
    }
};

// ===== 做法二：二分搜尋 + 滾動雜湊 O(n log n) =====
class Solution {
public:
    int smallestUniqueSubarray(vector<int>& nums) {
        typedef long long ll;
        const ll M1 = 1000000007, M2 = 998244353, B = 100003;
        int n = nums.size();
        vector<ll> h1(n + 1, 0), h2(n + 1, 0), p1(n + 1, 1), p2(n + 1, 1);
        for (int i = 0; i < n; i++) {
            h1[i + 1] = (h1[i] * B + nums[i]) % M1;   // 前綴雜湊
            h2[i + 1] = (h2[i] * B + nums[i]) % M2;
            p1[i + 1] = p1[i] * B % M1;               // B 的次方
            p2[i + 1] = p2[i] * B % M2;
        }
        auto hasUnique = [&](int L) {     // 長度 L 有沒有只出現一次的？
            unordered_map<ll, int> cnt;
            for (int i = 0; i + L <= n; i++) {
                ll a = ((h1[i + L] - h1[i] * p1[L]) % M1 + M1) % M1;
                ll b = ((h2[i + L] - h2[i] * p2[L]) % M2 + M2) % M2;
                cnt[a * M2 + b]++;        // 兩個雜湊值合成一個
            }
            for (auto& [key, c] : cnt)
                if (c == 1) return true;
            return false;
        };
        int lo = 1, hi = n;               // 長度 n 一定只出現一次
        while (lo < hi) {
            int mid = (lo + hi) / 2;
            if (hasUnique(mid)) hi = mid; // 可以 → 答案 ≤ mid
            else lo = mid + 1;            // 不行 → 答案 > mid
        }
        return lo;
    }
};
