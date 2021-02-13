// https://leetcode.com/problems/copy-list-with-random-pointer/

/*
// Definition for a Node.
class Node {
public:
	int val;
	Node* next;
	Node* random;
	
	Node(int _val) {
		val = _val;
		next = NULL;
		random = NULL;
	}
};
*/

class Solution {
public:
	Node* copyRandomList(Node* head) {
		if (!head) return head;
		// isert a copy of each node just after that node
		Node* i = head;
		while (i) {
			i->next = new Node(i->val, i->next, NULL);
			i = i->next->next;
		}
		// copy random pointers for copied list
		i = head;
		while (i && i->next) {
			i->next->random = i->random ? i->random->next : NULL;
			i = i->next->next;
		}
		// separate the cloned list from original list
		i = head;
		head = head->next;
		Node* prev = NULL;
		while (i && i->next) {
			if (prev) prev->next = i->next;
			prev = i->next;
			i->next = i->next->next;
			i = i->next;
		}

		return head;
	}
};