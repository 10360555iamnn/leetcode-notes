// ===== 暴力法 O(n²) =====
int trap(vector<int>& height) {
    int n = height.size(), ans = 0;
    for (int i = 0; i < n; i++) {
        int lMax = 0, rMax = 0;
        for (int j = i; j >= 0; j--)  // 往左找最高
            lMax = max(lMax, height[j]);
        for (int j = i; j < n; j++)   // 往右找最高
            rMax = max(rMax, height[j]);
        ans += min(lMax, rMax) - height[i];
    }
    return ans;
}

// ===== 前綴最大值 O(n) =====
int trap(vector<int>& height) {
    int n = height.size();
    vector<int> leftMax(n), rightMax(n);
    leftMax[0] = height[0];
    for (int i = 1; i < n; i++)
        leftMax[i] = max(leftMax[i - 1], height[i]);
    rightMax[n - 1] = height[n - 1];
    for (int i = n - 2; i >= 0; i--)
        rightMax[i] = max(rightMax[i + 1], height[i]);
    int ans = 0;
    for (int i = 0; i < n; i++)
        ans += min(leftMax[i], rightMax[i]) - height[i];
    return ans;
}

// ===== 雙指針 O(1) 空間 =====
int trap(vector<int>& height) {
    int l = 0, r = height.size() - 1;
    int lMax = 0, rMax = 0, ans = 0;
    while (l < r) {
        lMax = max(lMax, height[l]);
        rMax = max(rMax, height[r]);
        if (lMax < rMax) {     // 左邊比較矮
            ans += lMax - height[l];
            l++;
        } else {               // 右邊比較矮
            ans += rMax - height[r];
            r--;
        }
    }
    return ans;
}

// ===== 單調棧 =====
int trap(vector<int>& height) {
    stack<int> st;    // 存 index，高度遞減
    int ans = 0;
    for (int i = 0; i < height.size(); i++) {
        while (!st.empty() && height[i] > height[st.top()]) {
            int bottom = st.top(); st.pop();
            if (st.empty()) break;   // 沒有左牆
            int left = st.top();
            int w = i - left - 1;
            int h = min(height[left], height[i]) - height[bottom];
            ans += w * h;
        }
        st.push(i);
    }
    return ans;
}
