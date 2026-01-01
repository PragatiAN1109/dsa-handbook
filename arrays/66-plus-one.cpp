// 66. Plus One
// Problem Link: https://leetcode.com/problems/plus-one/description/

// Approaches:

// 1. Carry Propagation (Brute force)
// - Add 1 to the last digit
// - If there is no carry, return immediately
// - Otherwise propagate the carry backward
// - If carry remains after the most significant digit, insert it at the front
// - Time Complexity: O(n)
// - Space Complexity: O(1)

// 2. Optimized One-Pass 
// - Traverse digits from right to left.
// - If digit < 9, increment and return
// - If digit == 9, set it to 0 and continue
// - If all digits were 9, insert 1 at the front
// - Time Complexity: O(n)
// - Space Complexity: O(1)


#include <iostream>
#include <vector>
using namespace std;

class Solution {

    // 1.
    vector<int> plusOne_carry(vector<int>& digits) {
        int n = digits.size() - 1;

        int sum = digits[n] + 1;

        // No carry case
        if (sum <= 9) {
            digits[n] = sum;
            return digits;
        }

        // Handle carry
        digits[n] = sum % 10;
        int carry = sum / 10;

        for (int i = n - 1; i >= 0; i--) {
            int currSum = digits[i] + carry;
            digits[i] = currSum % 10;
            carry = currSum / 10;

            if (!carry) return digits;
        }

        // Carry remains after most significant digit
        digits.insert(digits.begin(), carry);
        return digits;
    }

public:
    // 2. 
    vector<int> plusOne(vector<int>& digits) {
        for (int i = digits.size() - 1; i >= 0; i--) {
            if (digits[i] < 9) {
                digits[i]++;
                return digits;
            }
            digits[i] = 0; // digit was 9, carry continues
        }

        // All digits were 9
        digits.insert(digits.begin(), 1);
        return digits;
    }
};

// ---------- Helper for local testing ----------
static void printVector(const vector<int>& v) {
    cout << "[";
    for (int i = 0; i < (int)v.size(); i++) {
        cout << v[i] << (i + 1 < (int)v.size() ? ", " : "");
    }
    cout << "]\n";
}

int main() {
    Solution sol;

    vector<int> a = {1, 2, 3};
    vector<int> b = {9};
    vector<int> c = {9, 9, 9};
    vector<int> d = {4, 3, 2, 1};

    cout << "Optimized one-pass:\n";
    printVector(sol.plusOne(a)); // [1,2,4]
    printVector(sol.plusOne(b)); // [1,0]
    printVector(sol.plusOne(c)); // [1,0,0,0]
    printVector(sol.plusOne(d)); // [4,3,2,2]

    return 0;
}
