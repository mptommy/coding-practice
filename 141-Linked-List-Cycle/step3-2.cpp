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
		while(cur_node){
			if(seen.contains(cur_node)){
				return true;
			}
			seen.insert(cur_node);
			cur_node = cur_node->next;
		}
		return false;
    }
};
