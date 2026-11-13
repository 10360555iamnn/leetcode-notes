// ===== 滑動視窗 + 單調雙端佇列 =====
class Solution {
public:
    long long countNonDecreasingSubarrays(vector<int>& nums, int k) {
        int n = nums.size();
        deque<pair<int, int>> dq;          // (補到的高度, 個數)，front = 視窗左端
        long long cost = 0, ans = 0;
        int r = n - 1;
        for (int l = n - 1; l >= 0; l--) {
            int cnt = 1;
            while (!dq.empty() && dq.front().first <= nums[l]) {
                cost += (long long)(nums[l] - dq.front().first) * dq.front().second;
                cnt += dq.front().second;
                dq.pop_front();
            }
            dq.push_front({nums[l], cnt});
            while (cost > k) {
                cost -= dq.back().first - nums[r];
                r--;
                if (--dq.back().second == 0) dq.pop_back();
            }
            ans += r - l + 1;
        }
        return ans;
    }
};
