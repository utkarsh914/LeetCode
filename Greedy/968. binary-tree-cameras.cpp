// https://leetcode.com/problems/binary-tree-cameras/

/*
Given a binary tree, we install cameras on the nodes of the tree. 
Each camera at a node can monitor its parent, itself, and its immediate children.
Calculate the minimum number of cameras needed to monitor all nodes of the tree.
*/








/*
Consider a node in the tree.
It can be covered by its parent, itself, its two children.
Four options.

Consider the root of the tree.
It can be covered by left child, or right child, or itself.
Three options.

Consider one leaf of the tree.
It can be covered by its parent or by itself.
Two options.

If we set a camera at the leaf, the camera can cover the leaf and its parent.
If we set a camera at its parent, the camera can cover the leaf, its parent and its sibling.

We can see that the second plan is always better than the first.
Now we have only one option, set up camera to all leaves' parent.

Here is our greedy solution:

Set cameras on all leaves' parents, then remove all covered nodes.
Repeat step 1 until all nodes are covered.


Explanation:

Apply a recusion function dfs.
Return 0 if it's a leaf.
Return 1 if it's a parent of a leaf, with a camera on this node.
Return 2 if it's coverd, without a camera on this node.

For each node,
if it has a child, which is leaf (node 0), then it needs camera.
if it has a child, which is the parent of a leaf (node 1), then it's covered.

If it needs camera, then res++ and we return 1.
If it's covered, we return 2.
Otherwise, we return 0.
*/


class Solution {
	int cam;
	// int covered = -1, leaf = 0, camera = 1;
public:
	int minCameraCover(TreeNode* r) {
		cam = 0;
		if (dfs(r) == "leaf") cam++;
		return cam;
	}
	
	string dfs(TreeNode* r) {
		if (!r) return "covered";
		string left = dfs(r->left), right = dfs(r->right);
		if (left == "leaf" or right == "leaf") {
			cam++;
			return "camera";
		}
		if (left == "camera" or right == "camera")
			return "covered";
		return "leaf";
	}
};







class Solution {
	int cam;
	short covered = -1, leaf = 0, camera = 1;
public:
	int minCameraCover(TreeNode* root) {
		cam = 0;
		if (dfs(root) == leaf) cam++;
		return cam;
	}
	
	short dfs(TreeNode* r) {
		if (!r) return covered;
		short left = dfs(r->left), right = dfs(r->right);
		if (left == leaf or right == leaf) {
			cam++;
			return camera;
		}
		if (left == camera or right == camera)
			return covered;
		return leaf;
	}
};