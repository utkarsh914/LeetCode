// https://leetcode.com/problems/n-ary-tree-preorder-traversal/

/*
// Definition for a Node.
class Node {
public:
	int val;
	vector<Node*> children;

	Node() {}

	Node(int _val) {
		val = _val;
	}

	Node(int _val, vector<Node*> _children) {
		val = _val;
		children = _children;
	}
};
*/

class Solution {
public:
	vector<int> preorder(Node* root) {
		vector<int> ans;
		stack<Node*> s;
		Node* cur = root;
		
		while (s.size() > 0 or cur != NULL) {
			// push leftmost
			while (cur != NULL) {
				s.push(cur);
				ans.push_back(cur->val);
				auto& child = cur->children;
				// reverse children array while pushing the node
				// so we can just pick from the back whenevr we need to pick a child
				reverse(child.begin(), child.end());
				cur = NULL;
				if (!child.empty()) {
					cur = child.back();
					child.pop_back();
				}
			}
			
			cur = s.top(); s.pop();
			auto& child = cur->children;
			// if it has more than 1 child, push it back again
			if (child.size() > 1) s.push(cur);
			// if it has children, cur will be the last children, otherwise NULL
			cur = NULL;
			if (!child.empty()) {
				cur = child.back();
				child.pop_back();
			}
		}

		return ans;
	}
};






















