// https://leetcode.com/problems/number-of-good-leaf-nodes-pairs/

/*
Given the root of a binary tree and an integer distance.
A pair of two different leaf nodes of a binary tree is said to be good
if the length of the shortest path between them is less than or equal to distance.

Return the number of good leaf node pairs in the tree. 
*/






/*
Start DFS from each leaf node. stop the DFS when the number of steps done > distance.
If you reach another leaf node within distance steps, add 1 to the answer.
Note that all pairs will be counted twice so divide the answer by 2.
*/
class Solution {
	int count;
	unordered_set<TreeNode*> vis;
	unordered_map<TreeNode*, TreeNode*> parent;
	vector<TreeNode*> leaves;

public:
	int countPairs(TreeNode* root, int distance) {
		this->count = 0;
		dfs(root);
		parent[root] = nullptr;

		for (auto& leaf : leaves) {
			vis.clear();
			vis.insert(nullptr);
			vis.insert(leaf);
			dfsFromLeaf(parent[leaf], distance - 1);
		}

		return count / 2;
	}

	// this DFS is to populate parents and find all leaves
	void dfs(TreeNode* r) {
		// if (!r) return;
		if (!r->left and !r->right) {
			leaves.push_back(r);
			return;
		}
		if (r->left) {
			parent[r->left] = r;
			dfs(r->left);
		}
		if (r->right) {
			parent[r->right] = r;
			dfs(r->right);
		}
	}

	void dfsFromLeaf(TreeNode* r, int dist) {
		if (!r or dist < 0) return;
		vis.insert(r);
		if (!r->left and !r->right) count++;
		if (!vis.count(parent[r])) dfsFromLeaf(parent[r], dist - 1);
		if (!vis.count(r->left)) dfsFromLeaf(r->left, dist - 1);
		if (!vis.count(r->right)) dfsFromLeaf(r->right, dist - 1);
	}
};