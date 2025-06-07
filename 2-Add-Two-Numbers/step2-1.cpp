/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    ListNode* helper(ListNode* l1, ListNode* l2, int carry) {
        if (!l1 && !l2 && !carry) {
            return nullptr;
        }
        int v1 = l1 ? l1->val : 0;
        int v2 = l2 ? l2->val : 0;
        int total = v1 + v2 + carry;
        carry = total / 10;
        total = total % 10;
        ListNode* node = new ListNode(total);
        ListNode* next_l1 = l1 ? l1->next : nullptr;
        ListNode* next_l2 = l2 ? l2->next : nullptr;
        node->next = helper(next_l1, next_l2, carry);
        return node;
    }
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        return helper(l1, l2, 0);
    }
};
