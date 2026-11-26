// ===== 做法：照規則模擬 =====
class Solution {
public:
    bool canAliceWin(int n) {
        int take = 10;            // 這一回合要拿幾顆
        bool alice = true;        // 現在輪到 Alice 嗎？
        while (n >= take) {       // 拿得動就拿
            n -= take;
            take--;               // 下一個人少拿 1 顆
            alice = !alice;       // 換人
        }
        return !alice;            // 輪到的人拿不動，他就輸了
    }
};

// ===== 看出規律：數回合 =====
class Solution {
public:
    bool canAliceWin(int n) {
        // 拿完第 1、2、3… 回合，總共用掉的石頭數（10、10+9、10+9+8…）
        int used[7] = {10, 19, 27, 34, 40, 45, 49};
        int rounds = 0;
        for (int u : used)
            if (n >= u) rounds++;  // n 撐得過這一回合
        return rounds % 2 == 1;    // 奇數回合：最後拿的是 Alice，Alice 贏
    }
};
