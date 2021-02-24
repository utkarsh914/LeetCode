// https://leetcode.com/problems/search-a-2d-matrix-ii/

class Solution {
public:
	bool searchMatrix(vector<vector<int>>& m, int target) {
		int r = m.size(), c = m[0].size();
		int i = 0, j = c-1;
		while (i < r and j >= 0) {
			if (m[i][j] == target)
				return true;
			if (target > m[i][j]) i++;
			else j--;
		}
		return false;
	}
};