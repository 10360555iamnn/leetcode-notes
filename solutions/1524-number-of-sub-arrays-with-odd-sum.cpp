// ===== 前綴和 + 奇偶配對 O(n) =====
class Solution {
public:
    int numOfSubarrays(vector<int>& arr) {
        const int MOD = 1000000007;
        long long ans = 0;
        int even = 1, odd = 0;      // P[0] = 0 是偶數
        int sum = 0;                // 前綴和的奇偶
        for (int x : arr) {
            sum = (sum + x) % 2;
            if (sum == 1) {         // 奇數：配前面的偶數
                ans += even;
                odd++;
            } else {                // 偶數：配前面的奇數
                ans += odd;
                even++;
            }
        }
        return ans % MOD;
    }
};
