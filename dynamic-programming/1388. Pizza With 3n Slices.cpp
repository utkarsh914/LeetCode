// https://leetcode.com/problems/pizza-with-3n-slices/

/*
There is a pizza with 3n slices of varying size, you and your friends will take slices of pizza as follows:

You will pick any pizza slice.
Your friend Alice will pick next slice in anti clockwise direction of your pick. 
Your friend Bob will pick next slice in clockwise direction of your pick.
Repeat until there are no more slices of pizzas.
Sizes of Pizza slices is represented by circular array slices in clockwise direction.

Return the maximum possible sum of slice sizes which you can have.

 

Example 1:



Input: slices = [1,2,3,4,5,6]
Output: 10
Explanation: Pick pizza slice of size 4, Alice and Bob will pick slices with size 3 and 5 respectively. Then Pick slices with size 6, finally Alice and Bob will pick slice of size 2 and 1 respectively. Total = 4 + 6.
Example 2:



Input: slices = [8,9,8,6,1,1]
Output: 16
Output: Pick pizza slice of size 8 in each turn. If you pick slice with size 9 your partners will pick slices of size 8.
Example 3:

Input: slices = [4,1,2,5,8,3,1,9,7]
Output: 21
Example 4:

Input: slices = [3,1,2]
Output: 3
 

Constraints:

1 <= slices.length <= 500
slices.length % 3 == 0
1 <= slices[i] <= 1000
*/










/*
We can understand the problem: pick n non-adjacent elements from circular array m=3n elements
so that the sum of the elements is maximum.
We can't pick 0th and (m-1)th elements at the same time, since it's adjacent in circular array.
So there are total 2 cases, then we can return the case with maximum sum:
Case 1: Don't pick (m-1)th element
=> Solve problem: pick n non-adjacent elements from linear array elements in ranges [0..m-2]
so that the sum of the elements is maximum.
Case 2: Don't pick 0th element
=> Solve problem: pick n non-adjacent elements from linear array elements in ranges [1..m-1]
so that the sum of the elements is maximum.


if we pick 0th, we can't pick last ele, and vice versa
to simplify problem of dealing with this case,
first we pick K ele from [0, end-1], and then from [1, end],
and return the max of both cases

** similar to: HOUSE ROBBER II


IMP: we only pick from the last,
so we always know the start index of the array to be considered
in next subproblem (i.e. 0 always).
so, subproblem is easy to understand,
i.e. pick K elements from the subarray of length L (i.e. [0, l-1])

we can pick from start too.
*/
class Solution {
public:
	int maxSizeSlices(vector<int>& s) {
		vector<int> slices1(s.begin(), --s.end());
		vector<int> slices2(++s.begin(), s.end());
		int k = s.size() / 3;
		return max(pick(slices1, k), pick(slices2, k));
	}


	int pick(vector<int>& slices, int K) {
		// dp[l][k] = max sum which we pick k ele from first `l` elements
		// Case k = 0 (pick 0 elements): dp[l][0] = 0
		// Case l = 0 (array is empty):  dp[0][k] = 0
		int dp[slices.size()+1][K+1];
		memset(dp, 0, sizeof(dp));

		for (int l = 1; l <= slices.size(); ++l) {
			for (int k = 1; k <= K; ++k) {
				// array has only 1 element, pick it
				if (l == 1) dp[l][k] = slices[0];
				else {
					int pick = slices[l-1] + dp[l-2][k-1];
					int dont_pick = dp[l-1][k];
					dp[l][k] = max(pick, dont_pick);
				}
			}
		}

		return dp[slices.size()][K];
	}
};