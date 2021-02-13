/*

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
	ListNode* reverseKGroup(ListNode* head, int k);
};

// ============ ITERATIVE ==========
ListNode* Solution::reverseKGroup(ListNode* head, int k) {
	if (!head) return NULL;

	int len = 0;
	ListNode* i = head;
	while (i) len++, i=i->next;

	int rounds = len/k;
	if (rounds == 0) return head;

	ListNode* dummy = new ListNode(0);
	dummy->next = head;
	ListNode* prev = dummy;

	for (int i=0; i<rounds; i++) {
		//for each list with size k, reverse it
		ListNode* curr = prev->next;
		ListNode* tail = curr;
		while (k--) {
			ListNode* next = curr->next;
			curr->next = prev;
			prev = curr;
			curr = next;
		}
		tail->next = curr;
		prev = tail;
	}

	return prev;
}

// ============= RECURSIVE ==============
ListNode* Solution::reverseKGroup(ListNode* head, int k) {
	ListNode* i = head;
	int count = 0;
	for (; i and count!=k; count++, i=i->next);
	// return if less than k nodes are present
	if (count < k)
		return head;

	ListNode* nextSubList = reverseKGroup(i, k);
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