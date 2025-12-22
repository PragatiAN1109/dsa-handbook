// 53. Maximum Subarray
// Problem Link: https://leetcode.com/problems/maximum-subarray/description/


// Approaches:

// 1. Brute Force
// - Consider all possible subarrays
// - For each starting index i, keep adding elements nums[j] (j >= i) and track the maximum subarray sum found.
// - This checks every possible subarray explicitly.
// - Time Complexity: O(n²)
// - Space Complexity: O(1)


// 2. Optimized Approach
// - Maintain a curr_sum representing the maximum subarray ending at the current index.
// - At each step:
//     - Add nums[i] to curr_sum
//     - Update max_sum 
//     - If curr_sum becomes negative, reset it to 0 (start a new subarray).
// - Time Complexity: O(n)
// - Space Complexity: O(1)


#include <iostream>
#include <vector>
#include <climits>  
#include <algorithm> 
using namespace std;

class Solution {
    // Brute Force approach
    int bruteForce(vector<int>& nums) {
        int max_sum = INT_MIN;

        for(int i = 0; i < nums.size(); i++){
            int curr_sum = 0;
            for(int j = i; j < nums.size(); j++){
                curr_sum += nums[j];
                max_sum = max(max_sum, curr_sum);
            }
        }

        return max_sum;
    }

public:
    // Kadane's Algorithm
    int maxSubArray(vector<int>& nums) {
        int curr_sum = 0;
        int max_sum = INT_MIN;

        for(int i = 0; i < nums.size(); i++){
            curr_sum += nums[i];
            max_sum = max(curr_sum, max_sum);
            if(curr_sum < 0) curr_sum = 0;
        }

        return max_sum;
        // return bruteForce(nums);
    }
};


int main() {
    Solution sol;

    vector<int> nums = {-2, 1, -3, 4, -1, 2, 1, -5, 4};

    int result = sol.maxSubArray(nums);

    cout << "Maximum subarray sum: " << result << endl;
    // Expected output: 6  (subarray [4, -1, 2, 1])

    return 0;
}
