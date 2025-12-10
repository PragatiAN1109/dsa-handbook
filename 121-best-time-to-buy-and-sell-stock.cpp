// 121. Best Time to Buy and Sell Stock
// Problem Link: https://leetcode.com/problems/best-time-to-buy-and-sell-stock/description/

// Approaches:
//
// 1️. Brute Force 
// - Try all possible pairs (i, j) where i < j.
// - Treat i as the buy day and j as the sell day.
// - Compute profit = prices[j] - prices[i] for each pair and track the maximum.
// - This guarantees we check all possibilities but is very slow for large arrays.
// - Time Complexity: O(n²)
// - Space Complexity: O(1)

// 2. Optimized Two-Pointer
// - Track the best (minimum) price to buy so far, and at each step compute the profit if we sell on the current day.
// - Use two pointers:
//   - left  = buy day index
//   - right = sell day index
// - Move right forward one step at a time:
//     - If prices[right] > prices[left], we can make a profit:
//         profit = prices[right] - prices[left], update max_profit if this profit is larger.
//     - Else (prices[right] <= prices[left]), it's better to "buy" at right, so we move left = right (cheaper price to buy).
// - This way, we scan the array once and always maintain the best buy so far.
// - Time Complexity: O(n)
// - Space Complexity: O(1)

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
    int bruteForce(vector<int>& prices){
        int max_profit = 0;

        for(int i=0; i<prices.size(); i++){
            for(int j=i+1; j<prices.size(); j++){
                max_profit = max(max_profit, prices[j]-prices[i]);
            }
        }

        return max_profit;
    }
public:
    int maxProfit(vector<int>& prices) {
        int left = 0; 
        int right = 1;
        int max_profit = 0;

        while(right < prices.size()){
            if(prices[right] > prices[left]){
                int profit = prices[right] - prices[left];
                max_profit = max(max_profit, profit);
            }
            else left = right;
            right++;
        }

        return max_profit;
    }
};


int main() {
    Solution sol;

    vector<int> prices = {7, 1, 5, 3, 6, 4};

    int result = sol.maxProfit(prices);

    cout << "Maximum Profit: " << result << endl; // Expected: 5

    return 0;
}