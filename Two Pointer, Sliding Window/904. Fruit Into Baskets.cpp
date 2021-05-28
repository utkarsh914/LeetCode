// https://leetcode.com/problems/fruit-into-baskets/



/*
we need to basically find the longest subarray
containing at most 2 distinct elements
*/

class Solution {
public:
	int totalFruit(vector<int>& tree) {
		unordered_map<int, int> m;
		int ans = 1;
		for (int i = 0, j = 0; j < tree.size(); j++) {
			m[tree[j]]++;
			// remove from window if more than 2 distinct ele
			while (m.size() > 2) {
				if (--m[tree[i]] == 0)
					m.erase(tree[i]);
				i++;
			}
			ans = max(ans, j-i+1);
		}
		return ans;
	}
};