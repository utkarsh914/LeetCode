/*
https://leetcode.com/problems/swap-nodes-in-pairs/
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
	ListNode* swapinKgroups(ListNode* head, int k);
	ListNode* swapPairs(ListNode* head);
};

ListNode* Solution::swapinKgroups(ListNode* head, int k) {
	ListNode* i = head;
	int count = 0;
	for (; i and count!=k; count++, i=i->next);
	if (count < k)
		return head;

	ListNode* nextSubList = swapinKgroups(i, k);
	// reverse
	ListNode* curr = head;
	ListNode* prev = NULL;
	while (count-- > 0) {
		ListNode* next = curr->next;
		curr->next = prev;
		prev = curr;
		curr = next;
	}
	head->next = nextSubList;
	return prev;
}

ListNode* Solution::swapPairs(ListNode* head) {
	return swapinKgroups(head, 2);
}