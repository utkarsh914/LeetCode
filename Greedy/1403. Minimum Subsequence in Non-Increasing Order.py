# https://leetcode.com/problems/minimum-subsequence-in-non-increasing-order/

class Solution:
	def minSubsequence(self, nums: List[int]) -> List[int]:
		nums.sort(reverse = True)
		ans = []
		total, cur = sum(nums), 0
		for n in nums:
			cur += n
			total -= n
			ans.append(n)
			if (cur > total): break
		return ans

