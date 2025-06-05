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
        ListNode* current_node = head;
        ListNode* leader_node = head;
        while (current_node) {
            if (current_node->val != leader_node->val) {
                leader_node->next = current_node;
                leader_node = current_node;
            }
            current_node = current_node->next;
        }
        if (leader_node) {
            leader_node->next = nullptr;
        }
        return head;
    }
};
