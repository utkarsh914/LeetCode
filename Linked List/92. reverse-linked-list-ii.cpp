// https://leetcode.com/problems/reverse-linked-list-ii/

/*
Reverse a linked list from position m to n. Do it in one-pass.

Note: 1 ≤ m ≤ n ≤ length of list.

Example:

Input:  1->2->3->4->5->NULL, m = 2, n = 4
Output: 1->4->3->2->5->NULL
*/

class Solution {
public:
	ListNode* reverseBetween(ListNode* head, int m, int n) {
		if (!head) return NULL;

		ListNode* dummy = new ListNode(0, head);
		ListNode* start = dummy;
		
		for (int i=0; i<m-1 ; i++, start=start->next){}

		ListNode* tail = start->next;
		head = start->next;
		ListNode* prev = NULL;
		
		for (int i=1; i<=n-m+1 && head; i++) {
			ListNode* next = head->next;
			head->next = prev;
			prev = head;
			head = next;
		}

		tail->next = head;
		start->next = prev;

		ListNode* result = dummy->next;
		delete dummy;
		return result;
	}
};