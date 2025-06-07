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
    ListNode* deleteDuplicates(ListNode* head) {
        ListNode dummy = ListNode();
        ListNode *result = &dummy;
        ListNode *node = head;
        while (node) {
            if (node->next && node->val == node->next->val) {
                while (node->next && node->val == node->next->val) {
                    node = node->next;
                }
                node = node->next;
            } else {
                result->next = node;
                node = node->next;
                result = result->next;
                result->next = nullptr;
            }
        }
        return dummy.next;
    }
};
