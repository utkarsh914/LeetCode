// https://leetcode.com/problems/maximum-number-of-points-with-cost/

/*
You are given an m x n integer matrix points (0-indexed). Starting with 0 points, you want to maximize the number of points you can get from the matrix.

To gain points, you must pick one cell in each row. Picking the cell at coordinates (r, c) will add points[r][c] to your score.

However, you will lose points if you pick a cell too far from the cell that you picked in the previous row. For every two adjacent rows r and r + 1 (where 0 <= r < m - 1), picking cells at coordinates (r, c1) and (r + 1, c2) will subtract abs(c1 - c2) from your score.

Return the maximum number of points you can achieve.

abs(x) is defined as:

x for x >= 0.
-x for x < 0.
 

Example 1:


Input: points = [[1,2,3],[1,5,1],[3,1,1]]
Output: 9
Explanation:
The blue cells denote the optimal cells to pick, which have coordinates (0, 2), (1, 1), and (2, 0).
You add 3 + 5 + 3 = 11 to your score.
However, you must subtract abs(2 - 1) + abs(1 - 0) = 2 from your score.
Your final score is 11 - 2 = 9.
Example 2:


Input: points = [[1,5],[2,3],[4,2]]
Output: 11
Explanation:
The blue cells denote the optimal cells to pick, which have coordinates (0, 1), (1, 1), and (2, 0).
You add 5 + 3 + 4 = 12 to your score.
However, you must subtract abs(1 - 1) + abs(1 - 0) = 1 from your score.
Your final score is 12 - 1 = 11.
 

Constraints:

m == points.length
n == points[r].length
1 <= m, n <= 105
1 <= m * n <= 105
0 <= points[r][c] <= 105
*/












/*
This is similar to 931. Minimum Falling Path Sum.

The difference is that, instead of checking 3 items above (⬆, ↖ and ↗),
we need to check the entire row. If we do just that,
the complexity will be O(m * n * n) and we will get TLE.

Also note that the path sum can overflow,
so we cannot use the input grid directly.

To make it efficient, we first go left-to-right,
and track the running maximum value (run_max).
For each step, we decrement it to account for the distance,
and compare with the value right above.
Then, we do the same right-to-left,
and add the maximum of two running values to each cell.
*/
class Solution {
public:
	long long maxPoints(vector<vector<int>>& g) {
		int R = g.size(), C = g[0].size();
		vector<long> cur(C);
		vector<long> prev(g[0].begin(), g[0].end());
		
		for (long i = 1; i < R; i++) {
			// go from left to right
			for (long j = 0, mx = prev[0]; j < C; j++) {
				mx = max(mx - 1, prev[j]);
				cur[j] = mx + g[i][j];
			}
			// go from right to left
			for (long j = C-1, mx = prev[C-1]; j >= 0; j--) {
				mx = max(mx - 1, prev[j]);
				cur[j] = max(cur[j], mx + g[i][j]);
			}
			cur.swap(prev);
		}
		
		return *max_element(prev.begin(), prev.end());
	}
};