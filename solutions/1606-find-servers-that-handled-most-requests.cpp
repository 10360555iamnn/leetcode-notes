// ===== 解答 =====
class Solution {
public:
    vector<int> busiestServers(int k, vector<int>& arrival, vector<int>& load) {
        set<int> avail;                                   // 空閒伺服器的編號
        for (int i = 0; i < k; i++) avail.insert(i);
        priority_queue<pair<long long,int>, vector<pair<long long,int>>, greater<>> busy;
        vector<int> cnt(k, 0);
        for (int i = 0; i < arrival.size(); i++) {
            while (!busy.empty() && busy.top().first <= arrival[i]) {
                avail.insert(busy.top().second); busy.pop();
            }
            if (avail.empty()) continue;                  // 全部在忙：丟掉
            auto it = avail.lower_bound(i % k);
            if (it == avail.end()) it = avail.begin();    // 繞回開頭
            int s = *it; avail.erase(it);
            cnt[s]++;
            busy.push({(long long)arrival[i] + load[i], s});
        }
        int mx = *max_element(cnt.begin(), cnt.end());
        vector<int> ans;
        for (int i = 0; i < k; i++) if (cnt[i] == mx) ans.push_back(i);
        return ans;
    }
};
