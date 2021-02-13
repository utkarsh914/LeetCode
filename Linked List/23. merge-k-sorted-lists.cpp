/*
https://leetcode.com/problems/merge-k-sorted-lists/
*/

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *	 int val;
 *	 ListNode *next;
 *	 ListNode() : val(0), next(nullptr) {}
 *	 ListNode(int x) : val(x), next(nullptr) {}
 *	 ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */

class Solution {
public:
	ListNode* mergeKLists(vector<ListNode*>& lists);
};

// To compare two points
class myComparator {
public:
	int operator() (const ListNode* n1, const ListNode* n2) {
		return n1->val > n2->val;
	}
};

ListNode* Solution::mergeKLists(vector<ListNode*>& lists) {
	// min-heap
	priority_queue <ListNode*, vector<ListNode*>, myComparator > pq;

	for (int i=0; i<lists.size(); i++)
		if (lists[i]) pq.push(lists[i]);

	ListNode* head = new ListNode(0);
	ListNode* i = head;

	while (!pq.empty()) {
		ListNode* curr = pq.top(); pq.pop();
		if (curr->next) pq.push(curr->next);
		i->next = curr;
		i = i->next;
	}

	return head->next;
}