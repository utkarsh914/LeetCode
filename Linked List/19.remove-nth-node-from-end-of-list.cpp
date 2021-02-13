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