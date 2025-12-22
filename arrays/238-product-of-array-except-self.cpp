// 238. Product of Array Except Self
// Problem Link: https://leetcode.com/problems/product-of-array-except-self/description/?source=submission-ac


// Approaches:

// 1. Prefix + Postfix in Output Array (Space Optimized)
// - First, store prefix products in the answer array.
// - Then traverse from the end while maintaining a postfix product and multiply it with the existing prefix value.
// - Time Complexity: O(n)
// - Space Complexity: O(1) extra space (excluding output array)


// 2. Separate Prefix and Postfix Arrays
// - Create a prefix array where prefix[i] stores the product of elements.
// - Create a postfix array where postfix[i] stores the product of elements.
// - For each index, multiply appropriate prefix and postfix values.
// - Time Complexity: O(n)
// - Space Complexity: O(n)


#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    // Approach 1: Space Optimized
    vector<int> productExceptSelf(vector<int>& nums) {
        vector<int> answer;

        // put prefix product in the answer
        answer.push_back(1);
        int prefix_prod = 1;
        for(int i = 0; i < nums.size() - 1; i++){
            prefix_prod *= nums[i];
            answer.push_back(prefix_prod);
        }

        // add postfix to the answer
        int postfix_prod = 1;
        for(int i = nums.size() - 1; i > 0; i--){
            answer[i] *= postfix_prod;
            postfix_prod *= nums[i];
        }
        answer[0] = postfix_prod;

        return answer;
    }

    // Approach 2: Prefix + Postfix Arrays
    vector<int> productExceptSelf_prefixPostfix(vector<int>& nums) {
        vector<int> prefix = nums;
        vector<int> postfix = nums;

        for(int i = 1; i < nums.size(); i++){
            prefix[i] = prefix[i - 1] * nums[i];
        }

        for(int i = nums.size() - 2; i >= 0; i--){
            postfix[i] = postfix[i + 1] * nums[i];
        }

        for(int i = 0; i < nums.size(); i++){
            if(i == 0) 
                nums[i] = postfix[i + 1];
            else if(i == nums.size() - 1) 
                nums[i] = prefix[i - 1];
            else 
                nums[i] = prefix[i - 1] * postfix[i + 1];
        }

        return nums;
    }
};


int main() {
    Solution sol;

    vector<int> nums = {1, 2, 3, 4};

    vector<int> result = sol.productExceptSelf(nums);

    cout << "Product of array except self: ";
    for(int val : result){
        cout << val << " ";
    }
    cout << endl;   // Expected: 24 12 8 6

    return 0;
}
