// https://leetcode.com/problems/max-value-of-equation/

// // ******* wrong ans ******
// class Solution {
// public:
// 	int findMaxValueOfEquation(vector<vector<int>>& p, int k) {
// 		// make use of the fact that arr is sorted according to x value
// 		int i = 0, j = 1, ans = INT_MIN;
// 		while (j < p.size()) {
// 			int d = abs(p[j][0] - p[i][0]);
// 			if (d > k) i++;
// 			else if (i == j) j++;
// 			else {
// 				ans = max( ans, p[i][1]+p[j][1]+d );
// 				j++;
// 			}
// 		}
// 		return ans;
// 	}
// };