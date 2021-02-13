// https://leetcode.com/problems/binary-search-tree-iterator/

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
class BSTIterator {
	int curr=0;
	vector<int> arr;

public:

	BSTIterator(TreeNode* root) {
		curr = 0; //index
		arr.push_back(-1);
		inorder(root);
	}

	void inorder(TreeNode* root) {
		if (root->left) inorder(root->left);
		arr.push_back(root->val);
		if (root->right) inorder(root->right);
	}

	int next() {
		return arr[++curr];
	}
	
	bool hasNext() {
		return (curr+1 < arr.size());
	}
};



// ****************** USING STACK ***********************
class BSTIterator {
	stack<TreeNode*> s;

	void pushAllLeftNodes(TreeNode* root) {
		while (root) {
			s.push(root);
			root = root->left;
		}
	}

public:

	BSTIterator(TreeNode* root) {
		pushAllLeftNodes(root);
	}

	int next() {
		int ans = s.top()->val;
		TreeNode* curr = s.top(); s.pop();
		if (curr->right) pushAllLeftNodes(curr->right);
		return ans;
	}
	
	bool hasNext() {
		return !s.empty();
	}
};

/**
 * Your BSTIterator object will be instantiated and called as such:
 * BSTIterator* obj = new BSTIterator(root);
 * int param_1 = obj->next();
 * bool param_2 = obj->hasNext();
 */