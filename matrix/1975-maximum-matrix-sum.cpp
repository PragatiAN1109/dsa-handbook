// 1975. Maximum Matrix Sum
// Problem Link: https://leetcode.com/problems/maximum-matrix-sum/description/


// Approach:
// In one operation, we can flip the sign of two adjacent cells. This operation always flips TWO signs, so the parity (odd/even) of the number of negative elements in the matrix never changes
// To maximize the sum:
// - We want as many values to be positive as possible -> take absolute values
// - If the count of negative numbers is even, we can make all numbers positive, so answer = sum(abs)
// - If the count of negative numbers is odd, we must end with exactly one negative. To get maximum sum, keep the smallest absolute value as negative, thus answer = sum(abs) - 2 * minAbs
// Time Complexity: O(m * n)
// Space Complexity: O(1)

#include <iostream>
#include <vector>
#include <cstdlib>
using namespace std;

class Solution {
public:
    long long maxMatrixSum(vector<vector<int>>& matrix) {
        long long total_sum = 0;
        int neg_cnt = 0;
        int min_element = abs(matrix[0][0]);

        int rows = (int)matrix.size();
        int cols = (int)matrix[0].size();

        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                total_sum += (long long)abs(matrix[i][j]);
                if (matrix[i][j] < 0) neg_cnt++;
                min_element = min(min_element, abs(matrix[i][j]));
            }
        }

        if (neg_cnt % 2) return total_sum - 2LL * min_element;
        return total_sum;
    }
};

int main() {
    Solution sol;

    vector<vector<int>> m1 = {{1, -1}, {-1, 1}};
    cout << sol.maxMatrixSum(m1) << endl; // Expected: 4

    vector<vector<int>> m2 = {{1, 2, 3}, {-1, -2, -3}, {1, 2, 3}};
    cout << sol.maxMatrixSum(m2) << endl; // Example output depends on parity; should be sum(abs) if even negatives

    vector<vector<int>> m3 = {{-1, 2}, {3, 4}};
    cout << sol.maxMatrixSum(m3) << endl; // Expected: 8

    return 0;
}
