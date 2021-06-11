// https://leetcode.com/problems/ways-to-make-a-fair-array/

/*
You are given an integer array nums. You can choose exactly one index (0-indexed) and remove the element. Notice that the index of the elements may change after the removal.

For example, if nums = [6,1,7,4,1]:

Choosing to remove index 1 results in nums = [6,7,4,1].
Choosing to remove index 2 results in nums = [6,1,4,1].
Choosing to remove index 4 results in nums = [6,1,7,4].
An array is fair if the sum of the odd-indexed values equals the sum of the even-indexed values.

Return the number of indices that you could choose such that after the removal, nums is fair.

 

Example 1:

Input: nums = [2,1,6,4]
Output: 1
Explanation:
Remove index 0: [1,6,4] -> Even sum: 1 + 4 = 5. Odd sum: 6. Not fair.
Remove index 1: [2,6,4] -> Even sum: 2 + 4 = 6. Odd sum: 6. Fair.
Remove index 2: [2,1,4] -> Even sum: 2 + 4 = 6. Odd sum: 1. Not fair.
Remove index 3: [2,1,6] -> Even sum: 2 + 6 = 8. Odd sum: 1. Not fair.
There is 1 index that you can remove to make nums fair.
Example 2:

Input: nums = [1,1,1]
Output: 3
Explanation: You can remove any index and the remaining array is fair.
Example 3:

Input: nums = [1,2,3]
Output: 0
Explanation: You cannot make a fair array after removing any index.
 

Constraints:

1 <= nums.length <= 105
1 <= nums[i] <= 104
*/









/*
if we delete an index, then for all indices after it,
odd indices become even, and evens become odds.
so, for subarray [i+1, end] odd sum should become eve sum, and vice versa

so, we can just store odd, even indices sum for every index.
both from left and right

or just keep 2 prefix sum arrays
one for even indices, another for odds
*/
class Solution {
public:
	int waysToMakeFair(vector<int>& A) {
		int N = A.size(), count = 0;
		// array -> { even indices sum, odd sum } upto index i (inclusive)
		vector<array<int,2>> left(N+1), right(N+1);
		
		for (int i = 0; i < N; i++) {
			left[i+1] = left[i];
			if (i % 2 == 0) left[i+1][0] += A[i];
			else left[i+1][1] += A[i];
		}
		
		for (int i = N-1; i >= 0; i--) {
			right[i] = right[i+1];
			if (i % 2 == 0) right[i][0] += A[i];
			else right[i][1] += A[i];
		}
		
		for (int i = 0; i < N; i++) {
			auto l = left[i], r = right[i+1];
			if (l[0]+r[1] == l[1]+r[0])
				count++;
		}
		
		return count;
	}
};