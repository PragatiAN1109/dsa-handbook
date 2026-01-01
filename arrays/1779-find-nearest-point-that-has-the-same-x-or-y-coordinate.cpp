// 1779. Find Nearest Point That Has the Same X or Y Coordinate
// Problem Link: https://leetcode.com/problems/find-nearest-point-that-has-the-same-x-or-y-coordinate/description/


// Approach:

// 1. Single Pass (Optimal)
// - A point is valid if it shares x or y with (x, y)
// - For each valid point, compute Manhattan distance: |x1 - x| + |y1 - y|
// - Track the smallest distance seen so far and its index
// Time Complexity: O(n)
// Space Complexity: O(1)

#include <iostream>
#include <vector>
#include <climits>
#include <cstdlib>
using namespace std;

class Solution {
public:
    int nearestValidPoint(int x, int y, vector<vector<int>>& points) {
        int smallest_distance = INT_MAX;
        int idx = -1;

        for (int i = 0; i < (int)points.size(); i++) {
            int x1 = points[i][0];
            int y1 = points[i][1];

            if (x1 == x || y1 == y) {
                int manhattan_dist = abs(x1 - x) + abs(y1 - y);

                if (manhattan_dist < smallest_distance) {
                    smallest_distance = manhattan_dist;
                    idx = i;
                }
            }
        }

        return idx;
    }
};

int main() {
    Solution sol;

    int x = 3, y = 4;
    vector<vector<int>> points = {{1,2}, {3,1}, {2,4}, {2,3}, {4,4}};

    cout << sol.nearestValidPoint(x, y, points) << endl; // Expected: 2

    return 0;
}
