// 1. Two Sum
// Problem Link: https://leetcode.com/problems/two-sum/description/


// Approach:
// 1. Brute Force
// - Try all possible pairs (i, j) and check if nums[i] + nums[j] == target.
// - Fix one element nums[i] and then scan all elements after it (j = i + 1 to n-1) to see if any pair forms the required sum.
// - As soon as we find such a pair, we return their indices.
// - This uses no extra data structure, so it is space efficient but slow for large inputs.
// - Time Complexity: O(n²)  
// - Space Complexity: O(1)  

// 2️. Optimized Using Hash Map
// - Use an unordered_map to store elements we have seen so far and their indices.
// - For every element nums[i], we compute diff = target - nums[i].
//   - If diff is already present in the map, it means we have previously seen a number that can pair with nums[i] to form the target -> return both indices.
//   - Otherwise, we store nums[i] in the map with its index (ele_index[nums[i]] = i) and move on.
// - This way, each element is processed once, and lookup in the map is O(1) on average.
// - Time Complexity: O(n)   
// - Space Complexity: O(n) 

#include <iostream>
#include <vector>
using namespace std;

class Solution {
    vector<int> twoSum_spaceEff(vector<int>& nums, int target){
        for(int i=0; i<nums.size(); i++){
            for(int j=i+1; j<nums.size(); j++){
                if(nums[i]+nums[j]==target){
                    return {i, j};
                }
            }
        }
        return {};
    }
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int, int> ele_index;

        for(int i=0; i<nums.size(); i++){
            int diff = target - nums[i];
            if(ele_index.find(diff) != ele_index.end()){
                return {ele_index[diff], i};
            }
            ele_index[nums[i]] = i;
        }

        return {};
    }
};

int main() {
    Solution sol;

    vector<int> nums = {2, 7, 11, 15};
    int target = 9;

    vector<int> result = sol.twoSum(nums, target);

    if(!result.empty()) {
        cout << "Indices: " << result[0] << ", " << result[1] << endl;
        cout << "Values: " << nums[result[0]] << ", " << nums[result[1]] << endl;
    } else {
        cout << "No valid pair found!" << endl;
    }

    return 0;
}
