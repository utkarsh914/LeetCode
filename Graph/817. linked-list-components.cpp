// https://leetcode.com/problems/linked-list-components/

/*
We are given head, the head node of a linked list containing unique integer values.

We are also given the list G, a subset of the values in the linked list.

Return the number of connected components in G,
where two values are connected if they appear consecutively in the linked list.

Example 1:

Input: 
head: 0->1->2->3
G = [0, 1, 3]
Output: 2
Explanation: 
0 and 1 are connected, so [0, 1] and [3] are the two connected components.
*/



/*
If you use the concepts from Union-Find, it becomes easy to understand.

G is the initail state of a Union-Find problem, each number in G is a node,
every nodes is disjointed from other nodes.

Whenever we Union two nodes, components decrease by 1.

How do we know which two nodes to Union?
Description says "two values are connected if they appear consecutively in the linked list."

So we traverse the linked list,
for each edge, if both vals are in G, we decrease components by 1.
*/
class Solution {
public:
	int numComponents(ListNode* head, vector<int>& G) {
		unordered_set<int> s(G.begin(), G.end());
		int count = s.size();

		while (head && head->next) {
			if (s.count(head->val) and s.count(head->next->val))
				count--;
			head = head->next;
		}

		return count;
	}
};







/*
Counting heads may make the code simpler:
*/
def numComponents(self, head: ListNode, G: List[int]) -> int:
	G, cnt, prev = set(G), 0, None
	while head:
		if head.val in G and prev not in G:
			cnt += 1
		prev, head = head.val, head.next
	return cnt