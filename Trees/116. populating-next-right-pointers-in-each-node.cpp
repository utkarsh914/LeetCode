// https://leetcode.com/problems/populating-next-right-pointers-in-each-node/

/*
// Definition for a Node.
class Node {
public:
	int val;
	Node* left;
	Node* right;
	Node* next;

	Node() : val(0), left(NULL), right(NULL), next(NULL) {}

	Node(int _val) : val(_val), left(NULL), right(NULL), next(NULL) {}

	Node(int _val, Node* _left, Node* _right, Node* _next)
		: val(_val), left(_left), right(_right), next(_next) {}
};
*/


// ******** O(N) time, O(1) space *********
class Solution {
public:
	Node* connect(Node* root) {
		
		Node* ans = root;

		while (root && root->left) {
			Node* nextNode = root->left;
			while (root) {
				root->left->next = root->right;
				root->right->next = (root->next) ? root->next->left : NULL;
				root = root->next;
			}
			root = nextNode;
		}
		
		return ans;
	}
};





// ******** O(N) time, O(1) space *********
class Solution {
public:
	Node* connect(Node* root) {
		
		Node* level_start = root;
		
		while(level_start!=NULL) {
			//curr is the first node in that level
			Node* curr = level_start;
			//Keep going to the right in that level
			while(curr!=NULL) {
				if(curr->left) curr->left->next = curr->right;
				if(curr->right && curr->next) curr->right->next = curr->next->left;
				curr = curr->next;
			}
			level_start = level_start->left;
		}
		
		return root;
	}
};





// ******** O(N) time, O(H) space *********
class Solution {
	void dfs(Node* root) {
		if (!root or !root->left) return;
		root->left->next = root->right;
		root->right->next = (root->next) ? root->next->left : NULL;
		dfs(root->left);
		dfs(root->right);
	}

public:
	Node* connect(Node* root) {
		if (!root) return NULL;
		dfs(root);
		return root;
	}
};



// ******** O(N) time, O(N) space *********
class Solution {
	void dfs(Node* first, Node* second) {
		if (!first or !second) return;
		first->next = second;
		dfs(first->left, first->right);
		dfs(second->left, second->right);
		dfs(first->right, second->left);
	}

public:
	Node* connect(Node* root) {
		dfs(root->left, root->right);
		return root;
	}
};





// ******** O(N) time, O(N) space *********
class Solution {
public:
	Node* connect(Node* root) {
		if (!root) return NULL;

		queue<Node*> q; q.push(root);
		while (!q.empty()) {
			Node* prev = NULL;
			int size = q.size();
			while (size--) {
				Node* curr = q.front(); q.pop();
				if (prev) prev->next = curr;
				prev = curr;
				if (curr->left)  q.push(curr->left);
				if (curr->right) q.push(curr->right);
			}
		}
		return root;
	}
};