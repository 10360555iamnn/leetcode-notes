// ===== 雙堆積模擬 =====
class Solution {
public:
    vector<int> assignTasks(vector<int>& servers, vector<int>& tasks) {
        using T = tuple<long long, int, int>;   // (空閒時間, 權重, 編號)
        priority_queue<pair<int,int>, vector<pair<int,int>>, greater<>> freeQ;
        priority_queue<T, vector<T>, greater<>> busyQ;
        for (int i = 0; i < servers.size(); i++) freeQ.push({servers[i], i});
        vector<int> ans;
        long long t = 0;
        for (int j = 0; j < tasks.size(); j++) {
            t = max(t, (long long)j);
            if (freeQ.empty()) t = get<0>(busyQ.top());
            while (!busyQ.empty() && get<0>(busyQ.top()) <= t) {
                auto [end, w, i] = busyQ.top(); busyQ.pop();
                freeQ.push({w, i});
            }
            auto [w, i] = freeQ.top(); freeQ.pop();
            ans.push_back(i);
            busyQ.push({t + tasks[j], w, i});
        }
        return ans;
    }
};
