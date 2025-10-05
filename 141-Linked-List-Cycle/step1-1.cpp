/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    bool hasCycle(ListNode *head) {
		int num_visit_nodes = 0;
		ListNode *cur_node = head;
		while(!cur_node->val){
			num_visit_nodes++;
			cur_node = cur_node->next;
			if(num_visit_nodes >= 105){
				return true;
			}
		}
		return false;
    }
};
