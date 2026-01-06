// 1161. Maximum Level Sum of a Binary Tree
// Problem Link: https://leetcode.com/problems/maximum-level-sum-of-a-binary-tree/description/

// Approaches:

// 1. DFS + Map 
// - Perform DFS and store the sum of each level in a map<int, int>
// - Iterate through the map to find the level with maximum sum
// - Time Complexity: O(n)
// - Space Complexity: O(height + levels)

// 2. BFS (Level Order Traversal)
// - Traverse the tree level by level using a queue
// - Compute sum for each level immediately and update max sum and level 
// - Time Complexity: O(n)
// - Space Complexity: O(width of tree)

#include <iostream>
#include <map>
#include <queue>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *l, TreeNode *r) : val(x), left(l), right(r) {}
};

class Solution {

    // DFS + Map 
    map<int, int> level_sum;

    void dfs(TreeNode* root, int level) {
        if (root == nullptr) return;

        level_sum[level] += root->val;

        dfs(root->left, level + 1);
        dfs(root->right, level + 1);
    }

public:
    // DFS solution
    int maxLevelSum_DFS(TreeNode* root) {
        level_sum.clear();
        dfs(root, 1);

        int max_val = level_sum[1];
        int ans = 1;

        for (auto ele : level_sum) {
            if (ele.second > max_val) {
                max_val = ele.second;
                ans = ele.first;
            }
        }

        return ans;
    }

    // BFS (Level Order Traversal)
    int maxLevelSum(TreeNode* root) {
        if (!root) return 0;

        queue<TreeNode*> q;
        q.push(root);

        long long max_sum = LLONG_MIN;
        int ans = 1;
        int level = 1;

        while (!q.empty()) {
            int sz = q.size();
            long long level_sum = 0;

            for (int i = 0; i < sz; i++) {
                TreeNode* node = q.front();
                q.pop();

                level_sum += node->val;

                if (node->left) q.push(node->left);
                if (node->right) q.push(node->right);
            }

            if (level_sum > max_sum) {
                max_sum = level_sum;
                ans = level;
            }

            level++;
        }

        return ans;
    }
};

int main() {
    TreeNode* root = new TreeNode(1,
        new TreeNode(7, new TreeNode(7), new TreeNode(-8)),
        new TreeNode(0)
    );

    Solution sol;

    cout << "BFS result: " << sol.maxLevelSum(root) << endl;        // 2
    cout << "DFS result: " << sol.maxLevelSum_DFS(root) << endl;    // 2

    return 0;
}
