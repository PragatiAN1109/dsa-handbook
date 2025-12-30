// 859. Buddy Strings
// Problem Link: https://leetcode.com/problems/buddy-strings/

// Approaches:

// 1. Mismatch Tracking + Duplicate Check
// - If lengths differ, impossible.
// - If s == goal: return true only if s contains any duplicate character
// - Else: collect indices where s[i] != goal[i]. Must be exactly 2 and match after swap.
// - Time Complexity: O(n)
// - Space Complexity: O(1)

#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Solution {
public:
    bool buddyStrings(string s, string goal) {
        // Length mismatch
        if (s.length() != goal.length()) return false;

        // Case 1: Strings already equal - need duplicate character
        if (s == goal) {
            vector<int> freq(26, 0);
            for (int i = 0; i < s.length(); i++) {
                freq[s[i] - 'a']++;
                if (freq[s[i] - 'a'] == 2) return true;
            }
            return false;
        }

        // Case 2: Track mismatched indices
        int idx1 = -1, idx2 = -1;

        for (int i = 0; i < s.length(); i++) {
            if (s[i] != goal[i]) {
                // More than 2 mismatches
                if (idx1 != -1 && idx2 != -1) return false;

                if (idx1 == -1) idx1 = i;
                else idx2 = i;
            }
        }

        // Must have exactly 2 mismatches
        if (idx1 == -1 || idx2 == -1) return false;

        // Check swap validity
        return (s[idx1] == goal[idx2] && s[idx2] == goal[idx1]);
    }
};

int main() {
    Solution sol;

    cout << boolalpha;
    cout << sol.buddyStrings("ab", "ba") << "\n";   // true
    cout << sol.buddyStrings("ab", "ab") << "\n";   // false
    cout << sol.buddyStrings("aa", "aa") << "\n";   // true
    cout << sol.buddyStrings("abcd", "cbad") << "\n"; // true

    return 0;
}