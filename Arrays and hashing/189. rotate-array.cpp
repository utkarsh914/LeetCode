// https://leetcode.com/problems/rotate-array/

class Solution {
public:
	void rotate(vector<int>& n, int k) {
		k = n.size() - (k%n.size());
		reverse(n.begin(), n.begin()+k);
		reverse(n.begin()+k, n.end());
		reverse(n.begin(), n.end());
	}
};