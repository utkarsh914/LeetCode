// https://leetcode.com/problems/swapping-nodes-in-a-linked-list/

/*
You are given the head of a linked list, and an integer k.

Return the head of the linked list after swapping the values of the kth node
from the beginning and the kth node from the end (the list is 1-indexed).
*/

class Solution {
public:
	ListNode* swapNodes(ListNode* head, int k) {
		ListNode *h1, *h2, *h3;
		int i = 0;
		for (h1=head, i=0; i<k-1; i++, h1=h1->next);
		for (h2=head, i=0; i<k; i++, h2=h2->next);
		for (h3=head; h2!=NULL; h3=h3->next, h2=h2->next);
		swap(h1->val, h3->val);
		return head;
	}
};



/*
When we reach k-th node, we set n1 to the current node, and n2 - to the head.

We continue traversing the list, but now we also move n2.
When we reach the end, n2 will points to k-th node from end.
*/
ListNode* swapNodes(ListNode* head, int k) {
	ListNode *n1 = nullptr, *n2 = nullptr;
	for (auto p = head; p != nullptr; p = p->next) {
		n2 = n2 == nullptr ? nullptr : n2->next;
		if (--k == 0) {
			n1 = p;
			n2 = head;
		}
	}
	swap(n1->val, n2->val);
	return head;
}