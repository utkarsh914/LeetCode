// https://leetcode.com/problems/convert-sorted-list-to-binary-search-tree/

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
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *	 int val;
 *	 TreeNode *left;
 *	 TreeNode *right;
 *	 TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *	 TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *	 TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */

class Solution {
	ListNode* getMid(ListNode* head) {
		if (!head) return NULL;
		ListNode *slow=head, *fast=head;
		ListNode* prev = new ListNode(0, head);
		while (fast && fast->next) {
			prev = slow;
			slow = slow->next;
			fast = fast->next->next;
		}
		prev->next = NULL; // disconnect left part from this list
		return slow;
	}
public:
	TreeNode* sortedListToBST(ListNode* head) {
		if (!head) return NULL;
		if (!head->next)
			return new TreeNode(head->val);

		ListNode* mid = getMid(head);
		TreeNode* root = new TreeNode(mid->val);
		root->left = sortedListToBST(head);
		root->right = sortedListToBST(mid->next);

		return root;
	}
};