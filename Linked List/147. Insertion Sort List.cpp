// https://leetcode.com/problems/insertion-sort-list/


/**
 * Definition for singly-linked list.
 * struct ListNode {
 *	 int val;
 *	 ListNode *next;
 *	 ListNode() : val(0), next(nullptr) {}
 *	 ListNode(int x) : val(x), next(nullptr) {}
 *	 ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */


/*
---- APPROACH -----

we traverse the list from start.
we break the current node from the list
i.e. we split the list into three parts
	prevList , curNode, furtherList
	
	Note: prevList will always be sorted.
	so, we insert curNode at correct position in prevList
	and advance to further Node as current node, in next iteration
*/
class Solution {
public:
	ListNode* insertionSortList(ListNode* head) {

		ListNode *first = head, *second = head->next;

		while (second) {
			ListNode *next = second->next; // store next node
			first->next = NULL; // break the list into 3 parts
			second->next = NULL;
			// insert curNode(second) at correct pos in prevList
			auto [newHead, newTail] = insert(head, second);
			// join merged list to furtherList
			newTail->next = next;
			// advance our iterating pointers
			first = newTail;
			second = next;
			// set new head
			head = newHead;
		}

		return head;
	}
	
	// inserts a node into correct position in a sorted list
	// and returns the new head and tail of the list
	inline pair<ListNode*, ListNode*> insert(ListNode* head, ListNode* node) {

		ListNode *dummy = new ListNode(0, head);
		ListNode *first = dummy, *second = head;
		
		// find correct first, second nodes such that
		// list should be first -> node -> second
		while (second and second->val < node->val) {
			first = first->next;
			second = second->next;
		}
		// insert the node
		first->next = node;
		node->next = second;

		// traverse to the end to find the tail
		ListNode* tail = node;
		while (tail and tail->next) {
			tail = tail->next;
		}
		
		return { dummy->next, tail };
	}
};




// ------- jAVA ------- (faster and cleaner)
public ListNode insertionSortList(ListNode head) {
	if( head == null ){
		return head;
	}
	
	ListNode helper = new ListNode(0); //new starter of the sorted list
	ListNode cur = head; //the node will be inserted
	ListNode pre = helper; //insert node between pre and pre.next
	ListNode next = null; //the next node will be inserted
	//not the end of input list
	while( cur != null ) {
		next = cur.next;
		//find the right place to insert
		while( pre.next != null && pre.next.val < cur.val ){
			pre = pre.next;
		}
		//insert between pre and pre.next
		cur.next = pre.next;
		pre.next = cur;
		pre = helper;
		cur = next;
	}
	
	return helper.next;
}