// ===== 貪心公式 O(1) =====
class Solution {
public:
    long long minimumCost(int cost1, int cost2, int costBoth, int need1, int need2) {
        long long m = min(need1, need2);             // 可以配成一對的數量
        long long r1 = need1 - m, r2 = need2 - m;    // 配完剩下的
        long long pairCost = min((long long)costBoth, (long long)cost1 + cost2);
        return m * pairCost
             + r1 * min(cost1, costBoth)
             + r2 * min(cost2, costBoth);
    }
};

// ===== 只看三個轉折點 =====
auto f = [&](long long x) {          // 買 x 個套餐的總花費
    return x * costBoth
         + max<long long>(0, need1 - x) * cost1
         + max<long long>(0, need2 - x) * cost2;
};
long long lo = min(need1, need2), hi = max(need1, need2);
return min({f(0), f(lo), f(hi)});    // 只看三個轉折點
