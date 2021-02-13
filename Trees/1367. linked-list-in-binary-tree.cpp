// https://leetcode.com/problems/linked-list-in-binary-tree/

class Solution {
	bool find(ListNode* head, TreeNode* root) {
		if (!head) return true;
		if (!root) return false;
		return head->val==root->val && (find(head->next, root->left) or find(head->next, root->right));
	}
public:
	bool isSubPath(ListNode* head, TreeNode* root) {
		if (!root) return false;
		return find(head, root) or isSubPath(head, root->left) or isSubPath(head, root->right);
	}
};



// ************* combined ************
class Solution {
public:
	bool isSubPath(ListNode* head, TreeNode* root, bool is_consecutive=false) {
		if (!head) return true;
		if (!root) return false;
		if (is_consecutive == true) {
			if (head->val != root->val) return false;
			return isSubPath(head->next, root->left, true) or isSubPath(head->next, root->right, true);
		}
		return isSubPath(head, root, true) or isSubPath(head, root->left, false) or isSubPath(head, root->right, false);
	}
};



// ********* gets TLE *************
class Solution {
	bool find(ListNode* head, ListNode* currHead, TreeNode* root) {
		if (!currHead) return true;
		if (!root) return false;
		if (currHead->val == root->val) {
			if (find(head, currHead->next, root->left) or find(head, currHead->next, root->right))
				return true;
		}
		return find(head, head, root->left) or find(head, head, root->right);
	}
public:
	bool isSubPath(ListNode* head, TreeNode* root) {
		return find(head, head, root);
	}
};




// ********** USING KMP STRING MATCHING ALGO **********
/*
Solution 2: DP
Iterate the whole link, find the maximum matched length of prefix.
Iterate the whole tree, find the maximum matched length of prefix.
About this dp, @fukuzawa_yumi gave a link of reference:
https://en.wikipedia.org/wiki/Knuth–Morris–Pratt_algorithm

Time O(N + L)
Space O(L + H)
where N = tree size, H = tree height, L = list length.
*/
class Solution {

	bool isSubPath(ListNode* head, TreeNode* root) {
		vector<int> A = {head->val}, dp = {0};
		int i = 0;
		head = head->next;
		while (head) {
			while (i && head->val != A[i])
				i = dp[i - 1];
			i += head->val == A[i];
			A.push_back(head->val);
			dp.push_back(i);
			head = head->next;
		}
		return dfs(root, 0, A, dp);
	}

	bool dfs(TreeNode* root, int i, vector<int>& A, vector<int>& dp) {
		if (!root) return false;
		while (i && root->val != A[i])
			i = dp[i - 1];
		i += root->val == A[i];
		return i == dp.size() || dfs(root->left, i, A, dp) || dfs(root->right, i, A, dp);
	}

};