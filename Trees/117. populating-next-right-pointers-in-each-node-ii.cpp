// https://leetcode.com/problems/populating-next-right-pointers-in-each-node-ii/


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
class Solution {
public:
	Node* connect(Node* root) {
		
		Node* nextLevelHead = NULL; // head of the next level
		Node* prev = NULL;          // the leading node on the next level
		Node* curr = root;          // current node of current level
		
		// we'll iterate on all levels one by one
		while(curr != NULL) {
			// Keep going to the right in curr level
			while(curr != NULL) {
				// left child
				if(curr->left) {
					if (prev) prev->next = curr->left;
					else nextLevelHead = curr->left;
					prev = curr->left;
				}
				// right child
				if(curr->right) {
					if (prev) prev->next = curr->right;
					else nextLevelHead = curr->right;
					prev = curr->right;
				}
				// move to next node in this level
				curr = curr->next;
			}

			curr = nextLevelHead;
			nextLevelHead = NULL;
			prev = NULL;
		}
		
		return root;
	}
};









class Solution {
	Node* getNextNode(Node* root) {
		while (root) {
			if (root->left) return root->left;
			if (root->right) return root->right;
			root = root->next;
		}
		return root;
	}

public:
	Node* connect(Node* root) {
		
		Node* level_start = root;
		
		while(level_start!=NULL) {
			//curr is the first node in that level
			Node* curr = level_start;

			//Keep going to the right in that level
			while(curr != NULL) {
				if(curr->left) {
					curr->left->next = (curr->right) ? curr->right : getNextNode(curr->next);
				}
				if(curr->right) {
					curr->right->next = getNextNode(curr->next);
				}
				curr = curr->next;
			}

			// go to next level's start node
			if (level_start->left) {
				level_start = level_start->left;
			} else if (level_start->right) {
				level_start = level_start->right;
			} else {
				level_start = getNextNode(level_start->next);
			}

		}
		
		return root;
	}
};