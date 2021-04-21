// https://leetcode.com/problems/reorder-list/

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
	void reorderList(ListNode* head) {
		auto splitted = splitList(head);
		ListNode *h1 = splitted.first;
		ListNode *h2 = splitted.second;
		h2 = reverseList(h2);
		return merge(h1, h2);
	}

	pair<ListNode*, ListNode*> splitList(ListNode* head) {
		ListNode *h1 = head, *h2 = head;
		// find the mid
		while (h2 && h2->next && h2->next->next) {
			h1 = h1->next;
			h2 = h2->next->next;
		}
		// split to two lists
		h2 = h1->next;
		h1->next = NULL;
		h1 = head;
		return { h1, h2 };
	}

	ListNode* reverseList(ListNode* h) {
		ListNode * prev = NULL, cur = h;
		while (cur) {
			ListNode* next = cur->next;
			cur->next = prev;
			prev = cur;
			cur = next;
		}
		return prev;
	}

	ListNode* merge(ListNode* h1, ListNode* h2) {
		ListNode *i = h1, *j = h2;
		while (i and j) {
			ListNode* temp = j;
			j = j->next;
			temp->next = i->next;
			i->next = temp;
			i = i->next->next;
		}
		return h1;
	}
};