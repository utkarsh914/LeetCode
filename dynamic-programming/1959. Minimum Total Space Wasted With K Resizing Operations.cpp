// https://leetcode.com/problems/minimum-total-space-wasted-with-k-resizing-operations/

/*
You are currently designing a dynamic array. You are given a 0-indexed integer array nums, where nums[i] is the number of elements that will be in the array at time i. In addition, you are given an integer k, the maximum number of times you can resize the array (to any size).

The size of the array at time t, sizet, must be at least nums[t] because there needs to be enough space in the array to hold all the elements. The space wasted at time t is defined as sizet - nums[t], and the total space wasted is the sum of the space wasted across every time t where 0 <= t < nums.length.

Return the minimum total space wasted if you can resize the array at most k times.

Note: The array can have any size at the start and does not count towards the number of resizing operations.

 

Example 1:

Input: nums = [10,20], k = 0
Output: 10
Explanation: size = [20,20].
We can set the initial size to be 20.
The total wasted space is (20 - 10) + (20 - 20) = 10.
Example 2:

Input: nums = [10,20,30], k = 1
Output: 10
Explanation: size = [20,20,30].
We can set the initial size to be 20 and resize to 30 at time 2. 
The total wasted space is (20 - 10) + (20 - 20) + (30 - 30) = 10.
Example 3:

Input: nums = [10,20,15,30,20], k = 2
Output: 15
Explanation: size = [10,20,20,30,30].
We can set the initial size to 10, resize to 20 at time 1, and resize to 30 at time 3.
The total wasted space is (10 - 10) + (20 - 20) + (20 - 15) + (30 - 30) + (30 - 20) = 15.
 

Constraints:

1 <= nums.length <= 200
1 <= nums[i] <= 106
0 <= k <= nums.length - 1
*/








/*
Given a range, how can you find the minimum waste
if you can't perform any resize operations?

Can we build our solution using dynamic programming using the current index
and the number of resizing operations performed as the states?


---------- APPROACH ---------

basically the problem asks us to split the array into k+1 subarrays
and sum the wastage from every array.

wastage of any subarray is the sum of (A[i] - maxEle)
for every element A[i] of the subarray.

In other words, a subarray represents a subproblem
where we can't perform any extra resize operations except the initial one.
so, in order to keep it valid, we will need to pick the highest ele of that subarray
as the initial size, and accordingly calculate the wastage for that subarray.


Now, the problem can be broken into subproblems of same substructure.
let array is [0, N-1]
if our 1st subarray is [0, i],
then for next subproblem the array becomes [i+1, N-1] and k becomes k-1.
*/
class Solution {
	int dp[201][201];
public:
	int minSpaceWastedKResizing(vector<int>& A, int k) {
		memset(dp, -1, sizeof(dp));
		return getWasted(A, 0, k);
	}
	
	int getWasted(vector<int>& A, int start, int k) {
		if (start == A.size()) return 0;
		if (k == 0) return calculateForZeroK(A, start);
		if (dp[start][k] != -1) return dp[start][k];
		
		int ans = INT_MAX, mx = 0, sum = 0, count = 0;
		for (int i = start; i < A.size(); i++) {
			mx = max(mx, A[i]);
			sum += A[i];
			count++;
			int cur = count * mx - sum;
			ans = min(ans, cur + getWasted(A, i+1, k-1));
		}
		
		return dp[start][k] = ans;
	}
	
	inline int calculateForZeroK(vector<int>& A, int start) {
		int mx = *max_element(A.begin()+start, A.end());
		int sum = accumulate(A.begin()+start, A.end(), 0);
		int total = (A.size() - start) * mx;
		return total - sum;
	}
};