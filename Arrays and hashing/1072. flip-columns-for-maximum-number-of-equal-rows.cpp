// https://leetcode.com/problems/flip-columns-for-maximum-number-of-equal-rows/

/*
You are given an m x n binary matrix matrix.

You can choose any number of columns in the matrix and flip every cell in that column (i.e., Change the value of the cell from 0 to 1 or vice versa).

Return the maximum number of rows that have all values equal after some number of flips.


Example 1:

Input: matrix = [[0,1],[1,1]]
Output: 1
Explanation: After flipping no values, 1 row has all values equal.

Example 2:
Input: matrix = [[0,1],[1,0]]
Output: 2
Explanation: After flipping values in the first column, both rows have equal values.

Example 3:
Input: matrix = [[0,0,0],[0,0,1],[1,1,0]]
Output: 2
Explanation: After flipping values in the first two columns, the last two rows have equal values.
*/







/*
The core of the algorithm is to find the "pattern" of the row.
"Pattern" here can be characterized by whether each element in the
row is different with the first element or not.
Then we return the highest frequency of the pattern.

e.g. for the matrix -
[[0,0,0],
 [0,0,1],
 [1,1,0]]

pattern will be -
[[T,T,T],
 [T,T,F],
 [T,T,F]]

here, the pattern "TTF" appears 2 times(highest)
so, 2 is the answer


the method above works because,
in the rows having the same pattern,
we can either flip all the columns having 'F', or 'T',
and they will become equal.
*/
class Solution {
public:
	int maxEqualRowsAfterFlips(vector<vector<int>>& M) {
		unordered_map<string, int> map;

		for (auto& r : M) {
			// generate the pattern for the current row
			string s(r.size(), 'T');
			for (int i = 1; i < r.size(); i++)
				if (r[i] != r[0]) s[i] = 'F';
			map[s]++;
		}

		// find the highest freq of the pattern
		int ans = 0;
		for (auto& p : map)
			ans = max(ans, p.second);
		
		return ans;
	}
};