// https://leetcode.com/problems/construct-binary-tree-from-preorder-and-inorder-traversal/

/*
The basic idea is here:
Say we have 2 arrays, PRE and IN.
Preorder traversing implies that PRE[0] is the root node.
Then we can find this PRE[0] in IN, say it's IN[5].
Now we know that IN[5] is root, so we know that IN[0] - IN[4] is on the left side, IN[6] to the end is on the right side.
Recursively doing this on subarrays, we can build a tree out of it :)
*/


// ********* using map O(N) time ********
class Solution {
	unordered_map<int,int> index;

public:
	TreeNode* buildTree(vector<int>& pre, vector<int>& in) {
		if (pre.empty()) return NULL;
		for (int i=0; i<in.size(); i++) {
			index[in[i]] = i;
		}
		return build(pre, in, 0, 0, in.size()-1);
	}

	TreeNode* build(vector<int>& pre, vector<int>& in, int root, int iStart, int iEnd) {
		if (iStart > iEnd or root >= pre.size()) return NULL;

		TreeNode* rootNode = new TreeNode(pre[root]);
		int pivot = index[pre[root]];
		
		rootNode->left  = build(pre, in, root+1, iStart, pivot-1);
		rootNode->right = build(pre, in, root+(pivot-iStart+1), pivot+1, iEnd);
		return rootNode;
	}
};





// ********* without using map O(N^2) time ********
class Solution {
public:
	TreeNode* buildTree(vector<int>& pre, vector<int>& in) {
		if (pre.empty()) return NULL;
		return build(pre, in, 0, 0, in.size()-1);
	}

	TreeNode* build(vector<int>& pre, vector<int>& in, int root, int iStart, int iEnd) {
		if (iStart > iEnd or root >= pre.size()) return NULL;

		TreeNode* rootNode = new TreeNode(pre[root]);
		int pivot=-1;
		for (int i=iStart; i<=iEnd && pivot==-1; i++) {
			if (in[i] == pre[root]) pivot = i;
		}

		rootNode->left  = build(pre, in, root+1, iStart, pivot-1);
		rootNode->right = build(pre, in, root+(pivot-iStart+1), pivot+1, iEnd);
		return rootNode;
	}
};










// ************ less efficient *************
class Solution {
public:
	TreeNode* buildTree(vector<int>& pre, vector<int>& in) {
		if (pre.empty()) return NULL;
		TreeNode* root = new TreeNode(pre[0]);
		int leftSize = find(in.begin(), in.end(), pre[0]) - in.begin();

		vector<int> leftPre(pre.begin()+1, pre.begin()+leftSize);
		vector<int> leftIn(in.begin(), in.begin()+leftSize);
		root->left = buildTree(leftPre, leftIn);

		vector<int> rightPre(pre.begin()+1+leftSize, pre.end());
		vector<int> rightIn(in.begin()+leftSize+1, in.end());
		root->right = buildTree(rightPre, rightIn);

		return root;
	}
};