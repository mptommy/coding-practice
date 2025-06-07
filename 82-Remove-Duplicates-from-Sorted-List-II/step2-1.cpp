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
        if (!head || !head->next) {
            return head;
        }
        ListNode* pre_result = deleteDuplicates(head->next);
        if (head->val == head->next->val) {
            if (pre_result == head->next) {
                return pre_result->next;
            } else {
                return pre_result;
            }
        } else {
            head->next = pre_result;
            return head;
        }
    }
};
