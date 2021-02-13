// https://leetcode.com/problems/maximum-product-subarray/

class Solution {
public:
	int maxProduct(vector<int>& n) {
		// store the result that is the max we have found so far
		// maxP/minP stores the max/min product of
		// subarray that ends with the current number n[i]
		int ans = n[0], maxP = n[0], minP = n[0];
		
		for (int i=1; i < n.size(); i++) {
			// multiplied by a negative makes big number smaller, small number bigger
			// so we redefine the extremums by swapping them
			if (n[i] < 0) swap(maxP, minP);
			// max/min product for the current number is either the current number itself
			// or the max/min by the previous number times the current one
			maxP = max(n[i], maxP*n[i]);
			minP = min(n[i], minP*n[i]);
			// the newly computed max value is a candidate for our global result
			ans = max(ans, maxP);
		}
		
		return ans;
	}
};






class Solution:
	def maxProduct(self, nums: List[int]) -> int:
		prefix, suffix, max_so_far = 0, 0, float('-inf')
		for i in range(len(nums)):
			prefix = (prefix or 1) * nums[i]
			suffix = (suffix or 1) * nums[~i]
			max_so_far = max(max_so_far, prefix, suffix)
		return max_so_far