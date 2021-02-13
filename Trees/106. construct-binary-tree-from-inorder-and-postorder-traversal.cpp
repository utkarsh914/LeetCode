// https://leetcode.com/problems/construct-binary-tree-from-inorder-and-postorder-traversal/

// ********* using map O(N) time ********
class Solution {
	unordered_map<int,int> index;

public:
	TreeNode* buildTree(vector<int>& in, vector<int>& post) {
		if (in.empty()) return NULL;
		for (int i=0; i<in.size(); i++) {
			index[in[i]] = i;
		}
		return build(post, in, post.size()-1, 0, in.size()-1);
	}

	TreeNode* build(vector<int>& post, vector<int>& in, int root, int iStart, int iEnd) {
		if (iStart > iEnd or root < 0) return NULL;

		TreeNode* rootNode = new TreeNode(post[root]);

		int pivot = index[post[root]];

		rootNode->left  = build(post, in, root-(iEnd-pivot+1), iStart, pivot-1);
		rootNode->right = build(post, in, root-1, pivot+1, iEnd);
		return rootNode;
	}
};





// ********* without using map O(N^2) time ********
class Solution {
public:
	TreeNode* buildTree(vector<int>& in, vector<int>& post) {
		if (in.empty()) return NULL;
		return build(post, in, post.size()-1, 0, in.size()-1);
	}

	TreeNode* build(vector<int>& post, vector<int>& in, int root, int iStart, int iEnd) {
		if (iStart > iEnd or root < 0) return NULL;

		TreeNode* rootNode = new TreeNode(post[root]);

		int pivot=-1;
		for (int i=iStart; i<=iEnd && pivot==-1; i++) {
			if (in[i] == post[root]) pivot = i;
		}

		rootNode->left  = build(post, in, root-(iEnd-pivot+1), iStart, pivot-1);
		rootNode->right = build(post, in, root-1, pivot+1, iEnd);
		return rootNode;
	}
};
