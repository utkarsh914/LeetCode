// https://leetcode.com/problems/as-far-from-land-as-possible/

/************* FASTEST SOLUTION (USING DP)************/
class Solution {
public:
	int maxDistance(vector<vector<int>>& matrix) {

		int R = matrix.size();
		int C = matrix[0].size();
		int range = R*C;

		// flip 0 and 1, so it becomes 01 matrix problem
		// and we need to find the nearest 0 for each 1;
		// then take the max of whole matrix as answer
		int zeroCount = 0;
		for (int i=0; i<R; i++)
		for (int j=0; j<C; j++) {
			matrix[i][j] = !matrix[i][j];
			if (matrix[i][j] == 0) zeroCount++;
		}
		if (zeroCount==0 or zeroCount==R*C) return -1;

		for (int i=0; i<R; i++)
		for (int j=0; j<C; j++)
		if (matrix[i][j] != 0) {
			int upCell = i>0 ? matrix[i-1][j] : range;
			int leftCell = j>0 ? matrix[i][j-1] : range;
			matrix[i][j] = min(upCell, leftCell) + 1;
		}

		for (int i=R-1; i>=0; i--)
		for (int j=C-1; j>=0; j--)
		if (matrix[i][j] != 0) {
			int downCell = i+1<R ? matrix[i+1][j] : range;
			int rightCell = j+1<C ? matrix[i][j+1] : range;
			matrix[i][j] = min( matrix[i][j], 1+min(downCell, rightCell) );
		}

		int ans = -1;
		for (int i=0; i<R; i++)
		for (int j=0; j<C; j++)
			ans = max(ans, matrix[i][j]);

		return ans;
	}
};

/************* CLEANER THAN ABOVE SOLUTION (USING DP)************/
/*
class Solution {
public:
	int maxDistance(vector<vector<int>>& matrix) {

		int R = matrix.size();
		int C = matrix[0].size();
		int range = (R*C)+1;
    int ans = 0;

		for (int i=0; i<R; i++)
		for (int j=0; j<C; j++)
		if (matrix[i][j] != 1) {
      matrix[i][j] = range;
      if (i>0) matrix[i][j] = min( matrix[i][j], 1+matrix[i-1][j] );
      if (j>0) matrix[i][j] = min( matrix[i][j], 1+matrix[i][j-1] );
		}

		for (int i=R-1; i>=0; i--)
		for (int j=C-1; j>=0; j--)
		if (matrix[i][j] != 1) {
      if (i+1<R) matrix[i][j] = min( matrix[i][j], 1+matrix[i+1][j] );
      if (j+1<C) matrix[i][j] = min( matrix[i][j], 1+matrix[i][j+1] );
      ans = max(ans, matrix[i][j]);
		}

		return ans==range ? -1 : ans-1;
	}
};

*/

/*
// ************** USING BFS (SLOWER) **************

class Solution {
public:
	int maxDistance(vector<vector<int>>& grid) {
		
		queue<pair<int, int>> q;
		int steps = 0;

		for (int i=0; i<grid.size(); i++) {
		for (int j=0; j<grid[0].size(); j++) {
			if (grid[i][j] == 1) {
				q.push({i, j+1}), q.push({i, j-1});
				q.push({i+1, j}), q.push({i-1, j});
			}
		}}

		while (!q.empty()) {
			steps++;
			int size = q.size();
			while (size--) {
				int i = q.front().first;
				int j = q.front().second;
				q.pop();
				if (i>=0 && j>=0 && i<grid.size() && j<grid[0].size() && grid[i][j]==0) {
					grid[i][j] = steps;
					q.push({i, j+1}), q.push({i, j-1});
					q.push({i+1, j}), q.push({i-1, j});
				}
			}
		}

		return (steps==1) ? -1 : steps-1;
	}
};

*/