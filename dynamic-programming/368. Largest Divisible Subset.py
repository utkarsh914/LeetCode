# https://leetcode.com/problems/largest-divisible-subset/

"""
Given a set of distinct positive integers nums,
return the largest subset answer such that every pair
(answer[i], answer[j]) of elements in this subset satisfies:

answer[i] % answer[j] == 0, or
answer[j] % answer[i] == 0
If there are multiple solutions, return any of them.

 

Example 1:

Input: nums = [1,2,3]
Output: [1,2]
Explanation: [1,3] is also accepted.
Example 2:

Input: nums = [1,2,4,8]
Output: [1,2,4,8]
 

Constraints:

1 <= nums.length <= 1000
1 <= nums[i] <= 2 * 109
All the integers in nums are unique.
"""

class Solution:
	def largestDivisibleSubset(self, A: List[int]) -> List[int]:
		A.sort()
		# find the longest increasing subsequence
		dp = [1] * len(A);

		for i in range(len(A)):
			for j in range(i):
				if (A[i] % A[j] == 0):
					dp[i] = max(dp[i], 1 + dp[j])
		
		# trace back the longest subsequence
		maxSize, maxSizeIndex = max(dp), dp.index(max(dp))
		last = A[maxSizeIndex]
		ans = []
		
		for i in range(maxSizeIndex, -1, -1):
			# essential to check last % A[i] == 0
			if dp[i] == maxSize and last % A[i] == 0:
				ans.append(A[i])
				last = A[i]
				maxSize -= 1
		
		return ans;