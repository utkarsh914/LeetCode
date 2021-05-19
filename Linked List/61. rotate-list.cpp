// https://leetcode.com/problems/rotate-list/

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
	ListNode* rotateRight(ListNode* head, int k) {
		int len = length(head);
		if (len == 0 or (k = k % len) == 0)
			return head;
		
		ListNode* itr = head;
		for (int i = 0; i < len-k-1; itr = itr->next, i++);
		ListNode* newHead = itr->next;
		itr->next = NULL;
		// find the tail node now
		for (itr = newHead; itr->next; itr = itr->next);
		itr->next = head;

		return newHead;
	}

	int length(ListNode* head) {
		int l = 0;
		for (; head != NULL; head=head->next, l++);
		return l;
	}
};








class Solution {
public:
	ListNode* rotateRight(ListNode* head, int k) {
		if (!head) return head;
		
		int len=1; // number of nodes
		ListNode *newH, *tail;
		newH = tail = head;

		// get the number of nodes in the list
		while (tail->next) {
			tail = tail->next;
			len++;
		}

		// circle the link
		tail->next = head;

		if (k %= len) {
			// the tail node is the (len-k)-th node (1st node is head)
			for (auto i = 0; i < len-k; i++)
				tail = tail->next;
		}

		newH = tail->next; 
		tail->next = NULL;
		return newH;
	}
};