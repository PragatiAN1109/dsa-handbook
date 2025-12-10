// 217. Contains Duplicate
// Problem Link: https://leetcode.com/problems/contains-duplicate/


// Approaches:

// 1. Brute Force 
// - Compare every pair of elements using two nested loops: for each nums[i], check all nums[j] where j > i.
// - If any pair is equal (nums[i] == nums[j]), return true. If we finish all comparisons without finding a match, return false.
// - Time Complexity: O(n²)
// - Space Complexity: O(1)

// 2. Sorting-Based
// - If we sort the array, any duplicates will become adjacent. 
// - Then linearly scan the array and compare nums[i] with nums[i-1].
// - If any adjacent pair is equal, we have a duplicate -> return true.
// - If we finish scanning without finding equal neighbors, return false.
// - Time Complexity: O(nlogn) 
// - Space Complexity: O(1) or O(n) depending on the sort implementation

// 3. Hash Set 
// - Use an unordered_set to track elements we've already seen.
// - Iterate through nums:
//     - For each num, check if it already exists in the set:
//           - If yes -> duplicate found → return true.
//           - If no -> insert num into the set and continue.
// - If we finish the loop without returning true, then all elements are distinct → return false.
// - Time Complexity: O(n) on average (O(1) average insert + lookup per element)
// - Space Complexity: O(n) in the worst case 


#include <iostream>
#include <vector>
#include <unordered_set>
using namespace std;

class Solution {
    bool bruteForce(vector<int>& nums){
        for(int i=0; i<nums.size(); i++){
            for(int j=i+1; j<nums.size(); j++){
                if(nums[i]==nums[j]) return true;
            }
        }
        return false;
    }
    bool sortAlgo(vector<int>& nums){
        sort(nums.begin(), nums.end());
        for(int i=1; i<nums.size(); i++){
            if(nums[i-1]==nums[i]) return true;
        }
        return false;
    }
public:
    bool containsDuplicate(vector<int>& nums) {
        unordered_set<int> elements;

        for(int num: nums){
            if(elements.find(num) != elements.end()) return true;
            elements.insert(num);
        }

        return false;
    }
};


int main() {
    Solution sol;
    vector<int> nums = {1, 2, 3, 1};
    bool result = sol.containsDuplicate(nums);
    if(result) {
        cout << "Contains duplicate values." << endl;   // Expected: true
    } else {
        cout << "All elements are unique." << endl;
    }
    return 0;
}