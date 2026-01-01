// 1790. Check if One String Swap Can Make Strings Equal
// Problem Link: https://leetcode.com/problems/check-if-one-string-swap-can-make-strings-equal/

// Approach:
// 1. Brute Force 
// - If lengths differ, then return false.
// - Try swapping every pair (i, j) in s1 (including i==j) and check if it equals s2.
// - Time Complexity: O(n^3)
// - Space Complexity: O(1) 

// 2. Optimized (Mismatch Tracking)
// - If lengths differ, then return false.
// - If s1 == s2, then return true (0 swaps needed; swapping same index keeps it same).
// - Otherwise, collect indices where s1[i] != s2[i].
//   - If mismatches > 2 -> false
//   - If mismatches != 2 -> false
//   - If exactly 2 mismatches at idx1 and idx2, check cross-match:
//       s1[idx1] == s2[idx2] && s1[idx2] == s2[idx1]
// - Time Complexity: O(n)
// - Space Complexity: O(1)

#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Solution {
    bool areAlmostEqual_bruteforce(string s1, string s2) {
        if (s1.size() != s2.size()) return false;

        int n = (int)s1.size();

        // Try all swaps in s1
        for (int i = 0; i < n; i++) {
            for (int j = i; j < n; j++) {
                swap(s1[i], s1[j]);
                if (s1 == s2) return true;
                swap(s1[i], s1[j]); 
            }
        }

        return false;
    }

public:
    bool areAlmostEqual(string s1, string s2) {
        if (s1.size() != s2.size()) return false;
        if (s1 == s2) return true;

        int idx1 = -1, idx2 = -1;

        for (int i = 0; i < (int)s1.size(); i++) {
            if (s1[i] != s2[i]) {
                if (idx1 == -1) idx1 = i;
                else if (idx2 == -1) idx2 = i;
                else return false; // more than 2 mismatches
            }
        }

        // must have exactly 2 mismatches
        if (idx1==-1 || idx2 == -1) return false;

        return (s1[idx1] == s2[idx2] && s1[idx2] == s2[idx1]);
    }
};

int main() {
    Solution sol;

    string s1 = "bank";
    string s2 = "kanb";
    cout << boolalpha;

    cout << "Optimized: " << sol.areAlmostEqual(s1, s2) << endl;

    // Quick extra tests
    cout << "Already equal: " << sol.areAlmostEqual("attack", "attack") << endl; // true
    cout << "One mismatch:  " << sol.areAlmostEqual("abcd", "abce") << endl;     // false
    cout << "More mismatches:" << sol.areAlmostEqual("abcd", "dcba") << endl;    // false

    return 0;
}
