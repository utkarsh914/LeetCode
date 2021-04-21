/*
https://leetcode.com/problems/remove-nth-node-from-end-of-list/
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
	ListNode* removeNthFromEnd(ListNode* head, int n) {
		ListNode* dummy = new ListNode(0, head);
		ListNode* prev = dummy, *slow = head, *fast = head;
		// move fast n-1 steps ahead
		for (int i = 0; i < n-1; i++, fast = fast->next);
		// move prev, slow, fast until fast is the last node
		while (fast && fast->next) {
			prev = prev->next;
			slow = slow->next;
			fast = fast->next;
		}
		// delete slow as it is now the nth node from end
		prev->next = prev->next->next;
		delete slow;
		return dummy->next;
	}
};






class Solution {
public:
	ListNode* removeNthFromEnd(ListNode* head, int n) {
		ListNode* newHead = new ListNode(0, head);
		ListNode* slow = newHead;
		ListNode* fast = newHead;
		while (n-- and fast and fast->next) {
			fast = fast->next;
		}
		while (fast and fast->next) {
			slow = slow->next;
			fast = fast->next;
		}
		slow->next = slow->next->next;
		return newHead->next;
	}
};
