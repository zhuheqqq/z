class Solution {
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        vector<int> ans;
        
        // 检查矩阵是否为空
        if (matrix.empty() || matrix[0].empty()) {
            return ans;
        }
        
        int m = matrix.size();  // 获取矩阵的行数
        int n = matrix[0].size();  // 获取矩阵的列数
        int left = 0, right = n - 1, top = 0, bottom = m - 1;

        // 开始遍历，直到遍历完整个矩阵
        while (left <= right && top <= bottom) {
            // 遍历上边界，从左到右
            for (int j = left; j <= right; j++) {
                ans.push_back(matrix[top][j]);
            }
            
            // 遍历右边界，从上到下
            for (int i = top + 1; i <= bottom; i++) {
                ans.push_back(matrix[i][right]);
            }
            
            // 防止只有一行的情况，遍历底边界，从右到左
            if (top < bottom) {
                for (int j = right - 1; j > left; j--) {
                    ans.push_back(matrix[bottom][j]);
                }
            }
            
            // 防止只有一列的情况，遍历左边界，从下到上
            if (left < right) {
                for (int i = bottom; i > top; i--) {
                    ans.push_back(matrix[i][left]);
                }
            }
            
            // 缩小边界，准备遍历内圈
            left++;
            right--;
            top++;
            bottom--;
        }
        
        return ans;
    }
};
