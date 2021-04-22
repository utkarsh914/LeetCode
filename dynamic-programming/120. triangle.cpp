// https://leetcode.com/problems/triangle/

/*
Given a triangle array, return the minimum path sum from top to bottom.

For each step, you may move to an adjacent number of the row below.
More formally, if you are on index i on the current row, you may move
to either index i or index i + 1 on the next row.

Example 1:

Input: triangle = [[2],[3,4],[6,5,7],[4,1,8,3]]
Output: 11
Explanation: The triangle looks like:
   2
  3 4
 6 5 7
4 1 8 3
The minimum path sum from top to bottom is 2 + 3 + 5 + 1 = 11 (underlined above).
*/

// O(N^2) space
class Solution {
public:
	int minimumTotal(vector<vector<int>>& t) {
		for (int i=1; i < t.size(); i++) {
			for (int j=0; j < t[i].size(); j++) {
				int top = j<t[i-1].size() ? t[i-1][j] : INT_MAX;
				int left = j>0 ? t[i-1][j-1] : INT_MAX;
				t[i][j] += min(top, left);
			}
		}
		int s = t.size()-1;
		return *min_element(t[s].begin(), t[s].end());
	}
};






// O(N^2) space
class Solution {
public:
	int minimumTotal(vector<vector<int>>& t) {
		vector<int> dp(t.size()+1, INT_MAX);
		dp[1] = t[0][0];

		for (int i=1; i < t.size(); i++) {
			for (int j=t[i].size()-1; j >= 0; j--) {
				dp[j+1] = t[i][j] + min(dp[j+1], dp[j]);
			}
		}
		
		return *min_element(dp.begin(), dp.end());
	}
};