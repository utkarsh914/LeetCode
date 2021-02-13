// https://leetcode.com/problems/split-linked-list-in-parts/

/*
If there are N nodes in the list, and k parts, then every part has N/k elements,
except the first N%k parts have an extra one.
*/

class Solution {
public:
	vector<ListNode*> splitListToParts(ListNode* root, int k) {
		if (!root) return vector<ListNode*>(k, NULL);

		int len = 0;
		for (ListNode* i=root; i!=NULL; i=i->next, len++) {}

		vector<ListNode*> ans;

		for (int i=1; i<=k; i++) {
			ans.push_back(root);
			ListNode* prev = root;
			int curPartLen = (i<=len%k) ? 1+len/k : len/k;
			for (int j=0; j<curPartLen && root; j++) {
				prev = root;
				root = root->next;
			}
			if (prev) prev->next = NULL;
		}

		return ans;
	}
};