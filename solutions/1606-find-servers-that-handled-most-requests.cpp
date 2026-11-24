// ===== set + 最小堆積 =====
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

// ===== 另解：只用兩個堆積 =====
class Solution {
public:
    vector<int> busiestServers(int k, vector<int>& arrival, vector<int>& load) {
        priority_queue<int, vector<int>, greater<>> avail;   // 空閒伺服器的「排隊號碼」
        for (int i = 0; i < k; i++) avail.push(i);           // 一開始號碼就是編號
        priority_queue<pair<long long,int>, vector<pair<long long,int>>, greater<>> busy;  // (結束時間, 編號)
        vector<int> cnt(k, 0);
        for (int i = 0; i < arrival.size(); i++) {
            while (!busy.empty() && busy.top().first <= arrival[i]) {
                int id = busy.top().second; busy.pop();
                avail.push(i + ((id - i) % k + k) % k);    // 號碼 = 從 i 往後數第一個 ≡ id (mod k) 的數
            }
            if (avail.empty()) continue;                      // 全部在忙：丟掉
            int s = avail.top() % k; avail.pop();             // 號碼最小 = 順時針最早遇到
            cnt[s]++;
            busy.push({(long long)arrival[i] + load[i], s});
        }
        int mx = *max_element(cnt.begin(), cnt.end());
        vector<int> ans;
        for (int i = 0; i < k; i++) if (cnt[i] == mx) ans.push_back(i);
        return ans;
    }
};
