// https://leetcode.com/problems/subtree-of-another-tree/

/*
generate preorder/postorder string and find if t exists in s
t->val is enclosed by '.' to handle cases like [12], [2]
*/
class Solution {
	string preorderString(TreeNode* t) {
		if (!t) return "#";
		return "."+to_string(t->val)+"." + "," + preorderString(t->left) + "," + preorderString(t->right);
	}

public:
	bool isSubtree(TreeNode* s, TreeNode* t) {
		string s_str = preorderString(s);
		string t_str = preorderString(t);
		return (s_str.find(t_str) != string::npos);
	}
};