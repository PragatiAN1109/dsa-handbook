// LeetCode 2 - Add Two Numbers
//  Link: https://leetcode.com/problems/add-two-numbers/

// Approaches:

// 1. Space-Efficient In-Place (Reuse longer input list for storing result)
// - Reuse nodes from the longer list to store the result digits in-place.
// - Only allocate a new node if a final carry remains.
// Time:  O(n)
// Space: O(1) (in-place; may allocate 1 node)

// 2. Build new list with 3 loops (brute force)
// - Build a new result list by allocating nodes.
// - Uses separate loops for common part + remaining list.
// - Time:  O(n)
// - Space: O(n)

// 3. Dummy Node 
// Use a dummy node: one loop while(l1 || l2 || carry).
// Time:  O(n)
// Space: O(n)

#include <iostream>
#include <vector>
#include <string>
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

// 1. 
class Solution_InPlace {
    int getLength(ListNode* node) {
        int len = 0;
        while (node) {
            len++;
            node = node->next;
        }
        return len;
    }

public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        if (!l1) return l2;
        if (!l2) return l1;

        // Reuse the longer list as the result list
        if (getLength(l2) > getLength(l1)) swap(l1, l2);

        ListNode* head = l1;
        ListNode* prev = nullptr;
        int carry = 0;

        while (l1 || l2) {
            int sum = carry;

            if (l1) sum += l1->val;
            if (l2) sum += l2->val;

            // l1 is guaranteed to exist here as it's the longer list,
            if (l1) {
                l1->val = sum % 10;
                carry = sum / 10;

                prev = l1;
                l1 = l1->next;
            }

            if (l2) l2 = l2->next;
        }

        if (carry) {
            prev->next = new ListNode(carry);
        }

        return head;
    }
};

// 2. 
class Solution_3Loops {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode dummy(0);
        ListNode* curr = &dummy;
        int carry = 0;

        while (l1 && l2) {
            int sum = l1->val + l2->val + carry;
            int digit = sum % 10;
            carry = sum / 10;

            curr->next = new ListNode(digit);
            curr = curr->next;

            l1 = l1->next;
            l2 = l2->next;
        }

        while (l1) {
            int sum = l1->val + carry;
            int digit = sum % 10;
            carry = sum / 10;

            curr->next = new ListNode(digit);
            curr = curr->next;

            l1 = l1->next;
        }

        while (l2) {
            int sum = l2->val + carry;
            int digit = sum % 10;
            carry = sum / 10;

            curr->next = new ListNode(digit);
            curr = curr->next;

            l2 = l2->next;
        }

        if (carry) {
            curr->next = new ListNode(carry);
        }

        return dummy.next;
    }
};

// 3. Dummy node + single loop
class Solution_Dummy {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode dummy(0);
        ListNode* curr = &dummy;

        int carry = 0;

        while (l1 || l2 || carry) {
            int sum = carry;

            if (l1) {
                sum += l1->val;
                l1 = l1->next;
            }

            if (l2) {
                sum += l2->val;
                l2 = l2->next;
            }

            curr->next = new ListNode(sum % 10);
            curr = curr->next;

            carry = sum / 10;
        }

        return dummy.next;
    }
};

/* =========================
             Helpers
   ========================= */
static ListNode* buildList(const vector<int>& v) {
    ListNode dummy(0);
    ListNode* curr = &dummy;

    for (int x : v) {
        curr->next = new ListNode(x);
        curr = curr->next;
    }
    return dummy.next;
}

static void printList(ListNode* head) {
    while (head) {
        cout << head->val;
        if (head->next) cout << " -> ";
        head = head->next;
    }
    cout << "\n";
}

static void freeList(ListNode* head) {
    while (head) {
        ListNode* nxt = head->next;
        delete head;
        head = nxt;
    }
}

int main() {
    // Example: 342 + 465 = 807
    vector<int> a = {2, 4, 3};
    vector<int> b = {5, 6, 4};

    // 1) In-place
    {
        ListNode* l1 = buildList(a);
        ListNode* l2 = buildList(b);

        Solution_InPlace sol;
        ListNode* res = sol.addTwoNumbers(l1, l2);

        cout << "InPlace:   ";
        printList(res);

        // res is l1 reused; free both
        freeList(res);
        freeList(l2);
    }

    // 2) User 3-loops (brute force)
    {
        ListNode* l1 = buildList(a);
        ListNode* l2 = buildList(b);

        Solution_3Loops sol;
        ListNode* res = sol.addTwoNumbers(l1, l2);

        cout << "3Loops:    ";
        printList(res);

        freeList(l1);
        freeList(l2);
        freeList(res);
    }

    // 3) Dummy node
    {
        ListNode* l1 = buildList(a);
        ListNode* l2 = buildList(b);

        Solution_Dummy sol;
        ListNode* res = sol.addTwoNumbers(l1, l2);

        cout << "Dummy:     ";
        printList(res);

        freeList(l1);
        freeList(l2);
        freeList(res);
    }

    return 0;
}
