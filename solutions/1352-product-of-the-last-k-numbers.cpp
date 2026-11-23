// ===== 前綴乘積 O(1) =====
class ProductOfNumbers {
    vector<int> pre{1};   // pre[i]：最後一個 0 之後，前 i 個數的乘積
public:
    ProductOfNumbers() {}
    void add(int num) {
        if (num == 0) pre = {1};             // 遇到 0：重新開始
        else pre.push_back(pre.back() * num);
    }
    int getProduct(int k) {
        int n = pre.size();
        if (k >= n) return 0;                // 最後 k 個數裡有 0
        return pre[n - 1] / pre[n - 1 - k];
    }
};
