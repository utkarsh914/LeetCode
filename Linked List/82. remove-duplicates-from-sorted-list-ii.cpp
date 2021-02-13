// https://leetcode.com/problems/remove-duplicates-from-sorted-list-ii/

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
	ListNode* deleteDuplicates(ListNode* head) {
		if (!head) return NULL;
		
		auto start = new ListNode(0, head);
		auto prev = start;

		while (head and head->next) {
			if (head->next->val == head->val) {
				while (head->next and head->next->val == head->val) {
					head->next = head->next->next;
				}
				prev->next = head->next;
				head = prev->next;
			}
			else {
				prev = head;
				head = head->next;
			}
		}

		return start->next;
	}
};







class Solution {
public:
	ListNode* deleteDuplicates(ListNode* head) {
		if (!head) return NULL;
		
		auto start = head;
		unordered_set<int> set;
		while (head && head->next) {
			if (head->next->val == head->val) {
				set.insert(head->val);
				head->next = head->next->next;
			} else {
				head = head->next;
			}
		}

		head = start;
		while (head && head->next) {
			if (set.count(head->next->val)) {
				head->next = head->next->next;
			} else {
				head = head->next;
			}
		}

		return (start && set.count(start->val)) ? start->next : start;
	}
};