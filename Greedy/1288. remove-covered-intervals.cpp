// https://leetcode.com/problems/remove-covered-intervals/

/*
Given a list of intervals, remove all intervals
that are covered by another interval in the list.

Interval [a,b) is covered by interval [c,d) if and only if c <= a and b <= d.

After doing so, return the number of remaining intervals.

Example 1:

Input: intervals = [[1,4],[3,6],[2,8]]
Output: 2
Explanation: Interval [3,6] is covered by [2,8], therefore it is removed.
*/



class Solution {
public:
	int removeCoveredIntervals(vector<vector<int>>& A) {
		sort(A.begin(), A.end());
		int remain = A.size();
		for (int i = 1; i < A.size(); i++) {
			auto &cur = A[i], &prev = A[i-1];
			// if prev covers cur
			if (prev[1] >= cur[1])
				cur = prev, remain--;
			// if cur covers prev
			else if (cur[0] <= prev[0] && cur[1] >= prev[1])
				remain--;
		}

		return remain;
	}
};
