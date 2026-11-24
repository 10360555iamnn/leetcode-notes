// ===== 計數（本集解法） =====
class Solution {
public:
    int countServers(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        vector<int> rowCnt(m, 0), colCnt(n, 0);
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                if (grid[i][j] == 1) {
                    rowCnt[i]++;
                    colCnt[j]++;
                }
        int ans = 0;
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                if (grid[i][j] == 1 && (rowCnt[i] > 1 || colCnt[j] > 1))
                    ans++;
        return ans;
    }
};

// ===== 另解一：深度優先搜尋 =====
class Solution {
    int m, n;
    vector<vector<int>> g;
    int dfs(int r, int c) {                         // 回傳這個連通塊有幾台伺服器
        g[r][c] = 0;                                // 走過就標記掉
        int size = 1;
        for (int j = 0; j < n; j++) if (g[r][j]) size += dfs(r, j);   // 同一列
        for (int i = 0; i < m; i++) if (g[i][c]) size += dfs(i, c);   // 同一行
        return size;
    }
public:
    int countServers(vector<vector<int>>& grid) {
        g = grid; m = g.size(); n = g[0].size();
        int ans = 0;
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                if (g[i][j]) {
                    int size = dfs(i, j);
                    if (size > 1) ans += size;      // 連通塊大小 > 1 才能通訊
                }
        return ans;
    }
};

// ===== 另解二：並查集 =====
class Solution {
    vector<int> parent;
    int find(int x) { return parent[x] == x ? x : parent[x] = find(parent[x]); }
    void unite(int a, int b) { parent[find(a)] = find(b); }
public:
    int countServers(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        parent.resize(m * n);
        iota(parent.begin(), parent.end(), 0);
        vector<int> rowFirst(m, -1), colFirst(n, -1);   // 每列、每行第一台伺服器
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                if (grid[i][j]) {
                    int id = i * n + j;
                    if (rowFirst[i] == -1) rowFirst[i] = id; else unite(id, rowFirst[i]);
                    if (colFirst[j] == -1) colFirst[j] = id; else unite(id, colFirst[j]);
                }
        unordered_map<int, int> size;                    // 每個連通塊的大小
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                if (grid[i][j]) size[find(i * n + j)]++;
        int ans = 0;
        for (auto& [root, s] : size) if (s > 1) ans += s;
        return ans;
    }
};
