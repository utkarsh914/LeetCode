// https://leetcode.com/problems/maximum-sum-of-3-non-overlapping-subarrays/

/*
Given an integer array nums and an integer k,
find three non-overlapping subarrays of length k with maximum sum and return them.

Return the result as a list of indices representing the starting position
of each interval (0-indexed).
If there are multiple answers, return the lexicographically smallest one.

Example 1:

Input: nums = [1,2,1,2,6,7,5,1], k = 2
Output: [0,3,5]
Explanation: Subarrays [1, 2], [2, 6], [7, 5] correspond to the starting indices [0, 3, 5].
We could have also taken [2, 1], but an answer of [1, 3, 5] would be lexicographically larger.
Example 2:

Input: nums = [1,2,1,2,1,2,1,2,1], k = 2
Output: [0,2,4]
 

Constraints:

1 <= nums.length <= 2 * 104
1 <= nums[i] < 216
1 <= k <= floor(nums.length / 3)
*/






class Solution {
public:
	vector<int> maxSumOfThreeSubarrays(vector<int>& A, int k) {
		int N = A.size();
		vector<int> sum = A;
		for (int i = 1; i < N; i++) {
			sum[i] += sum[i-1];
		}

		vector<pair<int,int>> one(N+1), two(N+1), three(N+1);

		for (int i = k-1; i < N; i++) {
			int curSubSum = sum[i] - sum[i-k+1] + A[i-k+1];
			if (curSubSum > one[i].first)
				one[i+1] = { curSubSum, i };
			else one[i+1] = one[i];
		}

		for (int i = 2*k-1; i < N; i++) {
			int curSubSum = (sum[i] - sum[i-k+1] + A[i-k+1]) + one[i-k+1].first;
			if (curSubSum > two[i].first)
				two[i+1] = { curSubSum, i };
			else two[i+1] = two[i];
		}

		for (int i = 3*k-1; i < N; i++) {
			int curSubSum = (sum[i] - sum[i-k+1] + A[i-k+1]) + two[i-k+1].first;
			if (curSubSum > three[i].first)
				three[i+1] = { curSubSum, i };
			else three[i+1] = three[i];
		}
		
		int last = three[N-1-0*k + 1].second - (k-1);
		int mid = two[last-1 + 1].second - (k-1);
		int first = one[mid-1 + 1].second - (k-1);
		return { first, mid, last };
	}
};
/*
[1,2,1,2,6,7,5,1], k = 2
*/





// doesn't deal with case k = 1
class Solution {
public:
	vector<int> maxSumOfThreeSubarrays(vector<int>& A, int k) {
		int N = A.size();
		vector<int> sum = A;
		for (int i = 1; i < N; i++) {
			sum[i] += sum[i-1];
		}

		vector<pair<int,int>> one(N), two(N), three(N);

		for (int i = k-1; i < N; i++) {
			int curSubSum = sum[i] - sum[i-k+1] + A[i-k+1];
			if (curSubSum > one[i-1].first)
				one[i] = { curSubSum, i };
			else one[i] = one[i-1];
		}

		for (int i = 2*k-1; i < N; i++) {
			int curSubSum = (sum[i] - sum[i-k+1] + A[i-k+1]) + one[i-k].first;
			if (curSubSum > two[i-1].first)
				two[i] = { curSubSum, i };
			else two[i] = two[i-1];
		}

		for (int i = 3*k-1; i < N; i++) {
			int curSubSum = (sum[i] - sum[i-k+1] + A[i-k+1]) + two[i-k].first;
			if (curSubSum > three[i-1].first)
				three[i] = { curSubSum, i };
			else three[i] = three[i-1];
		}
		
		int last = three[N-1-0*k].second - (k-1);
		int mid = two[last-1].second - (k-1);
		int first = one[mid-1].second - (k-1);
		return { first, mid, last };
	}
};