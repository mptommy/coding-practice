/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
#include <set>
class Solution {
public:
    bool hasCycle(ListNode *head) {
		std::set<ListNode*> seen;
		ListNode *cur_node = head;
		while(cur_node && !seen.contains(cur_node)){
			seen.insert(cur_node);
			cur_node = cur_node->next;
		}
		if(cur_node){
			return true;
		}else{
			return false;
		}
    }
};
