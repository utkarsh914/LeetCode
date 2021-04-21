// https://leetcode.com/problems/partition-list/

/*
Given the head of a linked list and a value x,
partition it such that all nodes less than x come before nodes greater than or equal to x.
You should preserve the original relative order of the nodes in each of the two partitions.

Example 1:

Input: head = [1,4,3,2,5,2], x = 3
Output: [1,2,2,4,3,5]
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

// ***** NOT ACCepted (doesn't maintain the relative order)
// similar to quick select
class Solution {
public:
	ListNode* partition(ListNode* head, int x) {
		ListNode *i = head, *j = head;
		for (; i != NULL; i=i->next) {
			if (i->val < x) {
				swap(i->val, j->val);
				j = j->next;
			}
		}
		return head;
	}
};


/*
move all smaller values to a new list
then combine both lists at the end
*/
class Solution {
public:
	ListNode* partition(ListNode* h1, int x) {
		ListNode* h2 = new ListNode(-1);
		ListNode* i = h2;
		ListNode* dummy = new ListNode(-1, h1);
		h1 = dummy;

		while (h1 && h1->next) {
			if (h1->next->val < x) {
				i->next = h1->next;
				h1->next = h1->next->next;
				i = i->next;
				i->next = NULL;
			}
			else {
				h1 = h1->next;
			}
		}
		// join h2 - h1
		i->next = dummy->next;
		return h2->next;
	}
};