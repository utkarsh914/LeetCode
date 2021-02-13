// https://leetcode.com/problems/trim-a-binary-search-tree/




class Solution {
public:
	TreeNode* trimBST(TreeNode* r, int low, int high) {
		if (!r) return NULL;
		if (r->val < low)
			return trimBST(r->right, low, high);
		else if (r->val > high)
			return trimBST(r->left, low, high);
		
		r->left = trimBST(r->left, low, r->val-1);
		r->right = trimBST(r->right, r->val+1, high);
		return r;
	}
};





class Solution {
public:
	TreeNode* trimBST(TreeNode* r, int low, int high) {
		if (!r) return NULL;
		r->left = trimBST(r->left, low, high);
		r->right = trimBST(r->right, low, high);
		if (r->val < low)
			return r->right;
		else if (r->val > high)
			return r->left;
		else
			return r;
	}
};



class Solution {
public:
	TreeNode* trimBST(TreeNode* r, int low, int high) {
		if (!r) return NULL;
		TreeNode* left = trimBST(r->left, low, high);
		TreeNode* right = trimBST(r->right, low, high);
		if (r->val>=low and r->val<=high) {
			r->left = left;
			r->right = right;
			return r;
		}
		return left ? left : right;
	}
};