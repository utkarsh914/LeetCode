// https://leetcode.com/problems/01-matrix/

/* ************* USING DP **************/
class Solution {
public:
	vector<vector<int>> updateMatrix(vector<vector<int>>& matrix) {
		
		int R = matrix.size();
		int C = matrix[0].size();

		int range = R*C;

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

		return matrix;
	}
};


/*
// ************** USING BFS **************

class Solution {
public:

int R, C;

int bfs(int r, int c, vector<vector<int>>& matrix) {

	queue<pair<int, int>> q;
	q.push({r,c});
	int steps = 0;

	while (!q.empty()) {
		steps++;
		int size = q.size();
		while (size--) {
			r = q.front().first, c = q.front().second; q.pop();
			int dr[4] = {-1,1,0,0}; int dc[4] = {0,0,1,-1};
			for (int i=0; i<4; i++) {
				int rr = r+dr[i], cc = c+dc[i];
				if (rr<0 or rr>=R or cc<0 or cc>=C) continue;
				if (matrix[rr][cc] == 0) return steps;
				q.push({ rr, cc });
			}
		}
	}

	return 0;
}

vector<vector<int>> updateMatrix(vector<vector<int>>& matrix) {
	R = matrix.size();
	C = matrix[0].size();
	vector<vector<int>> ans(R, vector<int> (C,0));

	for (int i=0; i<R; i++) {
		for (int j=0; j<C; j++) {
			if (matrix[i][j]==1)
				ans[i][j] = bfs(i, j, matrix);
		}
	}

	return ans;
}
};

*/