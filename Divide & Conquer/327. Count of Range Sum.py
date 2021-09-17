'''
https://leetcode.com/problems/count-of-range-sum/


Given an integer array nums and two integers lower and upper, return the number of range sums that lie in [lower, upper] inclusive.

Range sum S(i, j) is defined as the sum of the elements in nums between indices i and j inclusive, where i <= j.

 

Example 1:

Input: nums = [-2,5,-1], lower = -2, upper = 2
Output: 3
Explanation: The three ranges are: [0,0], [2,2], and [0,2] and their respective sums are: -2, -1, 2.
Example 2:

Input: nums = [0], lower = 0, upper = 0
Output: 1
 

Constraints:

1 <= nums.length <= 105
-231 <= nums[i] <= 231 - 1
-105 <= lower <= upper <= 105
The answer is guaranteed to fit in a 32-bit integer.

'''






'''
First compute the prefix sums: first[m] is the sum of the first m numbers.
Then the sum of any subarray nums[i:k] is simply first[k] - first[i].
So we just need to count those where first[k] - first[i] is in [lower,upper].

To find those pairs, I use mergesort with embedded counting.
The pairs in the left half and the pairs in the right half get counted in the recursive calls.
We just need to also count the pairs that use both halves.

For each left in first[lo:mid] I find all right in first[mid:hi]
so that right - left lies in [lower, upper].
Because the halves are sorted, these fitting right values are a subarray first[i:j].
With increasing left we must also increase right,
meaning must we leave out first[i] if it's too small
and and we must include first[j] if it's small enough.

Besides the counting,
I also need to actually merge the halves for the sorting.
I let sorted() do that.
'''
class Solution:
	def countRangeSum(self, nums: List[int], lower: int, upper: int) -> int:
		# create prefix array
		presum = [0]
		for n in nums:
			presum.append(presum[-1] + n)
			
		def mergeSort(lo, hi):
			if lo + 1 == hi: return 0
			m = (lo + hi) // 2
			# recursively count pairs in left and right subarrays
			pairs = mergeSort(lo, m) + mergeSort(m, hi)
			# count pairs that use both the subarrays
			i = j = m
			for first in presum[lo : m]:
				while i < hi and presum[i] - first < lower : i += 1
				while j < hi and presum[j] - first <= upper: j += 1
				pairs += j - i
			# sort current subarray
			presum[lo : hi] = sorted(presum[lo : hi])
			return pairs
		
		return mergeSort(0, len(presum))