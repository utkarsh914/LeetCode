/*
https://leetcode.com/problems/interval-list-intersections/submissions/

Given two lists of closed intervals, each list of intervals is pairwise disjoint and in sorted order.

Return the intersection of these two interval lists.

(Formally, a closed interval [a, b] (with a <= b) denotes the set of real numbers x with a <= x <= b.  The intersection of two closed intervals is a set of real numbers that is either empty, or can be represented as a closed interval.  For example, the intersection of [1, 3] and [2, 4] is [2, 3].)

Example 1:
Input: A = [[0,2],[5,10],[13,23],[24,25]], B = [[1,5],[8,12],[15,24],[25,26]]
Output: [[1,2],[5,5],[8,10],[15,23],[24,24],[25,25]]
*/

class Solution {
public:
	vector<vector<int>> intervalIntersection(vector<vector<int>>& A, vector<vector<int>>& B) {
		// use two pointer method
		int i=0, j=0;
		vector<vector<int>> ans;
		while (i<A.size() and j<B.size()) {
			int start = max(A[i][0], B[j][0]);
			int end = min(A[i][1], B[j][1]);
			if (start<=end) ans.push_back({start, end});
			if (A[i][1]==B[j][1]) i++,j++;
			else if (A[i][1] < B[j][1]) i++;
			else j++;
		}
		return ans;
	}
};