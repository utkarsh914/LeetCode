// https://leetcode.com/problems/merge-k-sorted-lists/

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
struct CompareNodes {
	bool operator()(ListNode* const& p1, ListNode* const& p2) {
		return p1->val > p2->val;
	}
};
public:
	ListNode* mergeKLists(vector<ListNode*>& lists) {
		priority_queue<ListNode*, vector<ListNode*>, CompareNodes> pq;
		for (auto head:lists)
			if (head) pq.push(head);
		ListNode* head = new ListNode(-1);
		ListNode* i = head;
		while (!pq.empty()) {
			auto curr = pq.top(); pq.pop();
			i->next = curr;
			i = i->next;
			if (curr->next) pq.push(curr->next);
		}
		return head->next;
	}
};