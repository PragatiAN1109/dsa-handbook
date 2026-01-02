// 961. N-Repeated Element in Size 2N Array
// Problem Link: https://leetcode.com/problems/n-repeated-element-in-size-2n-array/description/


// Approaches:

// 1. Using HashSet
// - Traverse array while storing each element
// - The first element seen twice is the answer
// - Time Complexity: O(n)
// - Space Complexity: O(n)


// 2. Proximity Checks
// - Since one element appears N times in a 2N array, it must appear within distance <= 3 from itself at some point
// - Check nums[i] against nums[i+1], nums[i+2], nums[i+3]
// - Time Complexity: O(n)
// - Space Complexity: O(1)


// 3. Random Sampling (Probabilistic)
// - Randomly pick two indices i and j
// - If nums[i] == nums[j] (and i != j), that value must be the repeated element.
// - Expected Time Complexity: O(1)
// - Space Complexity: O(1)


#include <iostream>
#include <vector>
#include <unordered_set>
#include <cstdlib>
#include <ctime>
using namespace std;

class Solution {

    // 1.
    int repeatedNTimes_usingHashSet(vector<int>& nums) {
        unordered_set<int> seen;

        for (int n : nums) {
            if (seen.find(n) != seen.end()) return n;
            seen.insert(n);
        }
        return -1;
    }

    // 2. 
    int repeatedNTimes_usingProximityCheck(vector<int>& nums) {
        int n = nums.size();

        for (int i = 0; i < n; i++) {
            if ((i + 1 < n && nums[i] == nums[i + 1]) ||
                (i + 2 < n && nums[i] == nums[i + 2]) ||
                (i + 3 < n && nums[i] == nums[i + 3])) {
                return nums[i];
            }
        }
        return -1;
    }

public:
    // 3.
    int repeatedNTimes(vector<int>& nums) {
        int n = nums.size();
        srand(time(0)); // seed RNG

        while (true) {
            int i = rand() % n;
            int j = rand() % n;

            if (i != j && nums[i] == nums[j]) {
                return nums[i];
            }
        }
    }
};

int main() {
    Solution sol;

    vector<int> nums1 = {5,1,5,2,5,3,5,4};
    vector<int> nums2 = {1,2,3,1};

    cout << sol.repeatedNTimes(nums1) << endl; // 5
    cout << sol.repeatedNTimes(nums2) << endl; // 1

    return 0;
}
