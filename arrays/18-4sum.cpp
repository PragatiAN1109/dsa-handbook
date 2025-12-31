// LeetCode 18 - 4Sum
// Link: https://leetcode.com/problems/4sum/

// Approaches:

// 1. Brute Force (4 nested loops) 
// - For all i<j<k<l quadruplets and check sum == target
// - Use set to get distinct quadruplets
// - Time:  O(n^4)
// - Space: O(answers)

// 2. Hashing-based (Fix 3 numbers + hash set) [average O(n^3)]
// - Sort nums for consistent quadruplet ordering
// - For each (i, j, k), check if needed value was seen before
// - Use set to get the final element of the quadruplets
// - Time:  O(n^3) 
// - Space: O(n) + O(answers)

// 3. Optimal (Sort + fix (i,j) + TwoSum helper with two pointers)
// - Sort nums
// - Fix i and j (skip duplicates)
// - Run two-pointer two-sum on suffix starting at j+1 (skip duplicates)
// - Time:  O(n^3)
// - Space: O(1) + O(answers)

#include <iostream>
#include <vector>
#include <set>
#include <unordered_set>
#include <algorithm>
using namespace std;

class Solution {
public:
    // 1. 
    vector<vector<int>> fourSum_bruteforce(vector<int> nums, int target) {
        int n = nums.size();
        set<vector<int>> st;

        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                for (int k = j + 1; k < n; k++) {
                    for (int l = k + 1; l < n; l++) {
                        long long sum = 0;
                        sum += (long long)nums[i];
                        sum += (long long)nums[j];
                        sum += (long long)nums[k];
                        sum += (long long)nums[l];

                        if (sum == (long long)target) {
                            vector<int> quad = {nums[i], nums[j], nums[k], nums[l]};
                            sort(quad.begin(), quad.end());
                            st.insert(quad);
                        }
                    }
                }
            }
        }

        return vector<vector<int>>(st.begin(), st.end());
    }

    // 2. 
    vector<vector<int>> fourSum_hash(vector<int> nums, int target) {
        sort(nums.begin(), nums.end());
        int n = nums.size();

        set<vector<int>> st;

        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                unordered_set<long long> seen;

                for (int k = j + 1; k < n; k++) {
                    long long need = (long long)target
                                   - (long long)nums[i]
                                   - (long long)nums[j]
                                   - (long long)nums[k];

                    if (seen.find(need) != seen.end()) {
                        vector<int> quad = {nums[i], nums[j], nums[k], (int)need};
                        sort(quad.begin(), quad.end());
                        st.insert(quad);
                    }

                    seen.insert(nums[k]);
                }
            }
        }

        return vector<vector<int>>(st.begin(), st.end());
    }

    // 3.
    vector<vector<int>> findTwoSum(vector<int>& nums, long long target, int start) {
        int l = start;
        int r = (int)nums.size() - 1;
        vector<vector<int>> ans;

        while (l < r) {
            long long sum = (long long)nums[l] + (long long)nums[r];

            if (sum == target) {
                ans.push_back({nums[l], nums[r]});

                // skip duplicates
                int leftVal = nums[l], rightVal = nums[r];
                while (l < r && nums[l] == leftVal) l++;
                while (l < r && nums[r] == rightVal) r--;
            }
            else if (sum > target) {
                r--;
            }
            else {
                l++;
            }
        }

        return ans;
    }

    vector<vector<int>> fourSum(vector<int>& nums, int target) {
        vector<vector<int>> ans;
        sort(nums.begin(), nums.end());

        for (int i = 0; i < (int)nums.size(); i++) {
            // skip duplicates for i
            if (i > 0 && nums[i] == nums[i - 1]) continue;

            for (int j = i + 1; j < (int)nums.size(); j++) {
                // skip duplicates for j
                if (j > i + 1 && nums[j] == nums[j - 1]) continue;

                long long tmp_target = (long long)target - (long long)nums[i] - (long long)nums[j];

                vector<vector<int>> pairs = findTwoSum(nums, tmp_target, j + 1);

                for (const vector<int>& p : pairs) {
                    ans.push_back({nums[i], nums[j], p[0], p[1]});
                }
            }
        }

        return ans;
    }
};

/*************** Basic local test ***************/
static void print2D(const vector<vector<int>>& v) {
    cout << "[\n";
    for (auto &row : v) {
        cout << "  [";
        for (int i = 0; i < (int)row.size(); i++) {
            cout << row[i] << (i + 1 < (int)row.size() ? ", " : "");
        }
        cout << "]\n";
    }
    cout << "]\n";
}

int main() {
    Solution sol;

    vector<int> nums1 = {1, 0, -1, 0, -2, 2};
    int target1 = 0;

    cout << "Optimal:\n";
    auto ans1 = sol.fourSum(nums1, target1);
    print2D(ans1);

    cout << "\nBrute Force:\n";
    auto bf1 = sol.fourSum_bruteforce(nums1, target1);
    print2D(bf1);

    cout << "\nHashing:\n";
    auto hs1 = sol.fourSum_hash(nums1, target1);
    print2D(hs1);

    vector<int> nums2 = {2, 2, 2, 2, 2};
    int target2 = 8;

    cout << "\nOptimal (duplicates case):\n";
    auto ans2 = sol.fourSum(nums2, target2);
    print2D(ans2);

    return 0;
}
