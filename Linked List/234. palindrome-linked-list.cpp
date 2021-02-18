// https://leetcode.com/problems/palindrome-linked-list/

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
	bool isPalindrome(ListNode* head) {
		ListNode *slow = head, *fast = head;
		// find mid
		while (fast && fast->next) {
			slow = slow->next;
			fast = fast->next->next;
		}
		// reverse first half
		ListNode *cur = head, *prev = NULL;
		while (cur != slow) {
			ListNode* next = cur->next;
			cur->next = prev;
			prev = cur;
			cur = next;
		}
		// if odd length list, skip middle node
		if (fast) slow = slow->next;
		// compare 2 lists now
		ListNode *h1 = prev, *h2 = slow;
		while (h1 && h2) {
			if (h1->val != h2->val) return false;
			h1 = h1->next, h2 = h2->next;
		}
		
		return true;
	}
};





// same as above, but also restore the link
class Solution {
public:
	bool isPalindrome(ListNode* head) {

		ListNode *slow = head, *fast = head;
		// find mid
		while (fast && fast->next) {
			slow = slow->next;
			fast = fast->next->next;
		}
		// reverse first half
		ListNode *cur = head, *prev = NULL;
		while (cur != slow) {
			ListNode* next = cur->next;
			cur->next = prev;
			prev = cur;
			cur = next;
		}
		
		// compare 2 lists now
		ListNode *h1 = prev, *h2 = (fast) ? slow->next : slow;
		ListNode *h1_backup = h1, prev = NULL; // keep start of first half reversed list (to join both lists at the end)
		bool ans = true;

		while (h1 && h2) {
			if (h1->val != h2->val) ans = false;
			h2 = h2->next;
			// keep reverse first half while comparing
			ListNode* next = h1->next;
			h1->next = prev;
			prev = h1;
			h1 = next;
		}
		
		if (h1_backup) h1_backup->next = slow; // join both lists to restore original list
		return ans;
	}
};