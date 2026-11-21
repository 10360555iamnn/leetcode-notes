// ===== 一次 DFS + 字母書籤 =====
class Solution {
public:
    vector<int> findSubtreeSizes(vector<int>& parent, string s) {
        int n = parent.size();
        vector<vector<int>> g(n);                  // g[x]：x 原本的孩子
        for (int i = 1; i < n; i++) g[parent[i]].push_back(i);
        vector<int> last(26, -1), ans(n, 1);       // last[c]：書籤
        function<void(int)> dfs = [&](int x) {
            int c = s[x] - 'a';
            int old = last[c];                     // 最近的同字母祖先
            int np = old != -1 ? old : parent[x];  // 新父節點
            last[c] = x;                           // 進入 x
            for (int y : g[x]) dfs(y);
            last[c] = old;                         // 離開 x：還原
            if (x != 0) ans[np] += ans[x];         // 大小交給新父節點
        };
        dfs(0);
        return ans;
    }
};
