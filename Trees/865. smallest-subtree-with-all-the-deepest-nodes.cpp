// https://leetcode.com/problems/smallest-subtree-with-all-the-deepest-nodes/

/*
Given the root of a binary tree, the depth of each node is the shortest distance to the root.

Return the smallest subtree such that it contains all the deepest nodes in the original tree.

A node is called the deepest if it has the largest depth possible among any node in the entire tree.

The subtree of a node is tree consisting of that node, plus the set of all descendants of that node.

Note: This question is the same as 1123: https://leetcode.com/problems/lowest-common-ancestor-of-deepest-leaves/

*/
class Solution {
public:
	TreeNode* subtreeWithAllDeepest(TreeNode* root) {
		return depth(root).second;
	}
	
	pair<int,TreeNode*> depth(TreeNode* r) {
		if (!r) return { 0, NULL };

		auto left = depth(r->left);
		auto right = depth(r->right);

		if (left.first == right.first)
			return { left.first+1, r };
		if (left.first > right.first)
			return { left.first+1, left.second };
		else
			return { right.first+1, right.second };
	}
};



/**
 * The question is unclear. For example, if we did not have nodes 7 and 4, the answer would
 * be TreeNode(3). If we did not have node 4, the answer would be TreeNode(7) and not
 * TreeNode(2). Similarly, if we did not have 7, the answer would be TreeNode(4) and not
 * TreeNode(2).
 *
 * Intuitively, we should be traversing from the children to the parent and calculate the
 * height from bottom. So the null nodes would have height 0. The leaf nodes would have the
 * height 1 and the root would have the max height.
 
 * At each node, we keep a pair<height_of_node_from_bottom, node>. At a given node, if we
 * realize that the leftHeight == rightHeight, it means we have found the deepest subtree
 * rooted at node. If leftHeight > rightHeight, it means the deepest subtree must be rooted
 * at left child. If rightHeight > leftHeight, it means the deepest subtree must be rooted
 * at right child.
 
 * Which traversal allows us to traverse from bottom-up? Postorder! So we use it in the code.
 */