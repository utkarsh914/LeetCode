// https://leetcode.com/problems/minimum-absolute-difference-queries/

/*
The minimum absolute difference of an array a is defined as the minimum value of |a[i] - a[j]|, where 0 <= i < j < a.length and a[i] != a[j]. If all elements of a are the same, the minimum absolute difference is -1.

For example, the minimum absolute difference of the array [5,2,3,7,2] is |2 - 3| = 1. Note that it is not 0 because a[i] and a[j] must be different.
You are given an integer array nums and the array queries where queries[i] = [li, ri]. For each query i, compute the minimum absolute difference of the subarray nums[li...ri] containing the elements of nums between the 0-based indices li and ri (inclusive).

Return an array ans where ans[i] is the answer to the ith query.

A subarray is a contiguous sequence of elements in an array.

The value of |x| is defined as:

x if x >= 0.
-x if x < 0.
 

Example 1:

Input: nums = [1,3,4,8], queries = [[0,1],[1,2],[2,3],[0,3]]
Output: [2,1,4,1]
Explanation: The queries are processed as follows:
- queries[0] = [0,1]: The subarray is [1,3] and the minimum absolute difference is |1-3| = 2.
- queries[1] = [1,2]: The subarray is [3,4] and the minimum absolute difference is |3-4| = 1.
- queries[2] = [2,3]: The subarray is [4,8] and the minimum absolute difference is |4-8| = 4.
- queries[3] = [0,3]: The subarray is [1,3,4,8] and the minimum absolute difference is |3-4| = 1.
Example 2:

Input: nums = [4,5,2,2,7,10], queries = [[2,3],[0,2],[0,5],[3,5]]
Output: [-1,1,1,3]
Explanation: The queries are processed as follows:
- queries[0] = [2,3]: The subarray is [2,2] and the minimum absolute difference is -1 because all the
  elements are the same.
- queries[1] = [0,2]: The subarray is [4,5,2] and the minimum absolute difference is |4-5| = 1.
- queries[2] = [0,5]: The subarray is [4,5,2,2,7,10] and the minimum absolute difference is |4-5| = 1.
- queries[3] = [3,5]: The subarray is [2,7,10] and the minimum absolute difference is |7-10| = 3.
 

Constraints:

2 <= nums.length <= 105
1 <= nums[i] <= 100
1 <= queries.length <= 2 * 104
0 <= li < ri < nums.length
*/









/*
The most important Constraint: 1 <= nums[i] <= 100.
So we can collect all of the indice for each number in an array with size 101.
*/
class Solution {
public:
	vector<int> minDifference(vector<int>& A, vector<vector<int>>& Q) {

		vector<vector<int>> indices(101);
		vector<int> ans; ans.reserve(Q.size());
		// store inc ordered list of indices for every number
		// since numbers are in range [1, 100]
		for (int i = 0; i < A.size(); i++) {
			indices[A[i]].push_back(i);
		}

		// process every query
		for (auto& q : Q) {
			int start = q[0], end = q[1];
			vector<int> temp;
			// try all possible numbers and check
			// if their are indices are in range [start, end]
			for (int i = 1; i <= 100; i++) {
				auto lb = lower_bound(
					indices[i].begin(), indices[i].end(), start);
				if (lb != indices[i].end() and *lb <= end)
					temp.push_back(i);
			}
			// find min diff from temp array now
			if (temp.size() <= 1) {
				ans.push_back(-1);
			}
			else {
				int mindiff = INT_MAX;
				for (int j = 1; j < temp.size(); j++)
					mindiff = min(mindiff, temp[j] - temp[j-1]);
				ans.push_back(mindiff);
			}
		}
		
		return ans;
	}
};






/*
Solution 1. Prefix Sum
Intuition: Since 1 <= nums[i] <= 100, we can encode a large subarray into a cnt array where cnt[i] is the frequence of number i in the subarray.

Algorithm:

Generate the prefix sum array of counts. So prefix[i+1][j] is the frequence of number j in subarray A[0..i].
For each query L = Q[i][0], R = Q[i][1], we can get a cnt array where cnt[j] = prefix[R + 1][j] - prefix[L][j].
We can calculate the minimum absolute difference using this cnt array in O(100) = O(1) time.
*/

// OJ: https://leetcode.com/contest/weekly-contest-246/problems/minimum-absolute-difference-queries/
// Author: github.com/lzl124631x
// Time: O(R * (N + M)) where `R` is the range of numbers in `nums`, `N` and `M` are the length of `nums` and `queries` respectively
// Space: O(RN)
class Solution {
public:
	vector<int> minDifference(vector<int>& A, vector<vector<int>>& Q) {
		vector<int> ans(Q.size());
		int prefix[100001][101] = {}, cnt[101] = {}, N = A.size(), M = Q.size();
		for (int i = 0; i < N; ++i) {
			cnt[A[i]]++;
			for (int j = 0; j < 101; ++j) prefix[i + 1][j] = cnt[j];
		}
		for (int i = 0; i < M; ++i) {
			int L = Q[i][0], R = Q[i][1], cnt[101] = {};
			for (int j = 0; j < 101; ++j) cnt[j] += prefix[R + 1][j] - prefix[L][j];
			int prev = -1, minAbs = INT_MAX;
			for (int j = 1; j < 101; ++j) {
				if (cnt[j] == 0) continue;
				if (prev != -1 && j - prev < minAbs) minAbs = j - prev;
				prev = j;
			}
			ans[i] = minAbs == INT_MAX ? -1 : minAbs;
		}
		return ans;
	}
};