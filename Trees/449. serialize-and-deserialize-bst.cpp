// https://leetcode.com/problems/serialize-and-deserialize-bst/

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *	 int val;
 *	 TreeNode *left;
 *	 TreeNode *right;
 *	 TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

// ********** below answer is generalized for any Binary tree ************
// ************** same as problem #297 ***************

class Codec {
public:

	// Encodes a tree to a single string.
	string serialize(TreeNode* r) {
		string s;
		queue<TreeNode*> q;
		q.push(r);
		while (!q.empty()) {
			TreeNode* curr = q.front(); q.pop();
			if (curr == NULL) {
				s += "N";
				continue;
			}
			s += "."+to_string(curr->val)+".";
			q.push(curr->left);
			q.push(curr->right);
		}
		return s;
	}

	// Decodes your encoded data to tree.
	TreeNode* deserialize(string s) {
		if (s[0] == 'N') return NULL;

		queue<TreeNode*> q;
		int i=0, j=i+1;
		while (s[j]!='.') j++;
		TreeNode* root = new TreeNode(stoi(s.substr(i+1, j-i-1)));
		q.push(root);
		i=j+1;

		while (!q.empty() && i<s.length()) {
			TreeNode* curr = q.front(); q.pop();
			if (curr==NULL) continue;
			// get left child from string
			if (s[i]=='.') {
				j=i+1; while (s[j]!='.') j++;
				curr->left = new TreeNode(stoi(s.substr(i+1, j-i-1)));
				i = j+1;
			} else {
				i++;
			}
			// break condition
			if (i >= s.length()) break;
			// get right child from string
			if (s[i]=='.') {
				j=i+1; while (s[j]!='.') j++;
				curr->right = new TreeNode(stoi(s.substr(i+1, j-i-1)));
				i = j+1;
			} else {
				i++;
			}
			// push left/right nodes to queue
			if (curr->left) q.push(curr->left);
			if (curr->right) q.push(curr->right);
		}

		return root;
	}
};

// Your Codec object will be instantiated and called as such:
// Codec* ser = new Codec();
// Codec* deser = new Codec();
// string tree = ser->serialize(root);
// TreeNode* ans = deser->deserialize(tree);
// return ans;