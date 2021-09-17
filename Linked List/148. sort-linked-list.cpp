// https://leetcode.com/problems/sort-list/submissions/


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
	ListNode* mergeList(ListNode* h1, ListNode* h2);
	ListNode* sortList(ListNode* head);
};

ListNode* Solution::sortList(ListNode* head) {
	// return head if it has no node or just one node
	if (!head or !head->next) return head;
	ListNode *h1 = head, *h2 = head;
	// separate 2 lists from head, one starting from head, and another from mid of the list
	// use slow fast pointer algo to find middle, and thus we get the starting head of second list
	while (h2 and h2->next and h2->next->next)
		h1=h1->next, h2=h2->next->next;
	h2 = h1->next;
	h1->next = NULL;
	h1 = head;
	// recursively sort both the lists
	h1 = sortList(h1);
	h2 = sortList(h2);
	// return the merged list after merging both lists
	return mergeList(h1, h2);
}

// function to merge the two lists and return head of merged list
ListNode* Solution::mergeList(ListNode* h1, ListNode* h2) {
	// if one list is empty, simply return the other one
	if (!h1) return h2;
	if (!h2) return h1;
	// initialize an empty head
	ListNode* head = NULL;
	// if h1 val is lesser, then it should be proceeded by the merged of remaining part of h1, and full h2
	// similarly if h2 val is lesser, then it should be proceeded by the merged of remaining part of h2, and full h1
	if (h1->val < h2->val) {
		head = h1;
		head->next = mergeList(h2, h1->next);
	}
	else {
		head = h2;
		head->next = mergeList(h2->next, h1);
	}
	// return merged list
	return head;
}







class Solution {
	inline ListNode* getMid(ListNode* head) {
		if (!head) return NULL;
		auto slow = head, fast = head->next;
		while (fast and fast->next) {
			slow = slow->next;
			fast = fast->next->next;
		}
		return slow;
	}
	
public:
	ListNode* sortList(ListNode* head) {
		if (!head or !head->next) return head;
		auto mid = getMid(head);
		auto A = head, B = mid->next;
		mid->next = NULL;
		A = sortList(A);
		B = sortList(B);
		return merge(A, B);
	}
	
	ListNode* merge(ListNode* A, ListNode* B) {
		if (!A) return B;
		if (!B) return A;

		if (A->val < B->val) {
			A->next = merge(A->next, B);
			return A;
		} else {
			B->next = merge(B->next, A);
			return B;
		}
	}
};





class Solution {
	inline ListNode* getMid(ListNode* head) {
		if (!head) return NULL;
		auto slow = head, fast = head->next;
		while (fast and fast->next) {
			slow = slow->next;
			fast = fast->next->next;
		}
		return slow;
	}
	
public:
	ListNode* sortList(ListNode* head) {
		if (!head or !head->next) return head;
		auto mid = getMid(head);
		auto A = head, B = mid->next;
		mid->next = NULL;
		A = sortList(A);
		B = sortList(B);
		return merge(A, B);
	}
	
	ListNode* merge(ListNode* A, ListNode* B) {
		auto dummy = new ListNode(0);
		auto it = dummy;

		while (A and B) {
			if (A->val < B->val) {
				it->next = A;
				A = A->next;
			} else {
				it->next = B;
				B = B->next;
			}
			it = it->next;
		}

		if (A) it->next = A;
		if (B) it->next = B;

		return dummy->next;
	}
};