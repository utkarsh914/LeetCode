// https://leetcode.com/problems/merge-in-between-linked-lists/

/*
You are given two linked lists: list1 and list2 of sizes n and m respectively.

Remove list1's nodes from the ath node to the bth node, and put list2 in their place.

The blue edges and nodes in the following figure incidate the result:


Build the result list and return its head.

 

Example 1:


Input: list1 = [0,1,2,3,4,5], a = 3, b = 4, list2 = [1000000,1000001,1000002]
Output: [0,1,2,1000000,1000001,1000002,5]
Explanation: We remove the nodes 3 and 4 and put the entire list2 in their place.
The blue edges and nodes in the above figure indicate the result.
*/


class Solution {
public:
	ListNode* mergeInBetween(ListNode* h1, int a, int b, ListNode* h2) {
		ListNode* dummy = new ListNode(0, h1);

		ListNode* start = dummy;
		for (int i=0; i < a; i++, start = start->next);
		ListNode* end = start;
		for (int i=0; i < b-a+2; i++, end = end->next);
		
		start->next = h2;
		for (; h2 && h2->next; h2 = h2->next);
		h2->next = end;
		
		return dummy->next;
	}
};