// https://leetcode.com/problems/subarray-product-less-than-k/

class Solution {
public:
	int numSubarrayProductLessThanK(vector<int>& n, int k) {
		int count = 0, product = 1;
		for (int i=0,j=0; j<n.size(); j++) {
			product *= n[j];
			while (i<=j && product >= k)
				product /= n[i++];
			count += j-i+1;
		}
		return count;
	}
};