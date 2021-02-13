// https://leetcode.com/problems/out-of-boundary-paths/

/*
total moves for N steps is sum of all moves from neighbors with N-1 steps
ans corner cells have 2 ways for 1 step, other boundary cells have 1 way for 1 step
*/

class Solution {
public:
	int findPaths(int R, int C, int N, int r, int c) {

		long long int dp[50][50][51] = {};
		long long int M = 1e9+7;

		for (int n=1; n<=N; n++) {
			for (int i=0; i<R; i++) {
				for (int j=0; j<C; j++) {
					long long int up    = (i>0)   ? dp[i-1][j][n-1] : 1;
					long long int down  = (i+1<R) ? dp[i+1][j][n-1] : 1;
					long long int left  = (j>0)   ? dp[i][j-1][n-1] : 1;
					long long int right = (j+1<C) ? dp[i][j+1][n-1] : 1;
					dp[i][j][n] = (up + down + left + right) % M;
				}
			}
		}

		return dp[r][c][N];
	}
};




/*
We can also reduce the memory usage by using two grids instead of N, as we only need to look one step back.
We can use N%2 and (N-1)%2 to alternate grids so we do not have to copy.
*/
class Solution {
public:
	int findPaths(int R, int C, int N, int r, int c) {

		long long int dp[50][50][2] = {};
		long long int M = 1e9+7;

		for (int n=1; n<=N; n++) {
			int nc = n % 2, np = (n-1) % 2; // n-current, and n-previous
			for (int i=0; i<R; i++) {
				for (int j=0; j<C; j++) {
					long long int up    = (i>0)   ? dp[i-1][j][np] : 1;
					long long int down  = (i+1<R) ? dp[i+1][j][np] : 1;
					long long int left  = (j>0)   ? dp[i][j-1][np] : 1;
					long long int right = (j+1<C) ? dp[i][j+1][np] : 1;
					dp[i][j][nc] = (up + down + left + right) % M;
				}
			}
		}

		return dp[r][c][N%2];
	}
};




/*
We can further decrease the memory usage (2 * m * n >> m * (n + 1))as we only looking one row up.
We will store new values for the current row in an array, and write these values back to the matrix as we process cells
in the next row. This approach, however, impacts the runtime as we need extra copying for each step.
I experimented with different n and m (50 - 500), and N (5,000 - 50,000),
and the second solution is approximately 10% faster than this one.
*/

int findPaths(int m, int n, int N, int i, int j) {
	unsigned int g[50][50] = {}, r[50];
	while (N-- > 0)
		for (auto k = 0; k <= m; ++k)
			for (auto l = 0; l < n; ++l) {
				auto tmp = r[l];
				r[l] = (k == m ? 0 : ((k == 0 ? 1 : g[k - 1][l]) + (k == m - 1 ? 1 : g[k + 1][l])
					+ (l == 0 ? 1 : g[k][l - 1]) + (l == n - 1 ? 1 : g[k][l + 1])) % 1000000007);
				if (k > 0) g[k - 1][l] = tmp;
			}
	return g[i][j];
}





// ********** (unoptimized) gives TLE *******
class Solution {
	bool reached(int R, int C, int i, int j) {
		return i<0 or j<0 or i>=R or j>=C;
	}
public:
	int findPaths(int R, int C, int N, int r, int c) {

		int pathsCount = 0;
		queue<array<int,3>> q;
		q.push({r, c, N});

		while (!q.empty()) {
			int size = q.size();

			while (size--) {
				auto curr = q.front(); q.pop();
				int i=curr[0], j=curr[1], stepsRemain=curr[2];
				if (reached(R, C, i, j)) {
					pathsCount++;
					continue;
				}
				
				if (stepsRemain == 0)
					continue;
				
				q.push({i-1, j, stepsRemain-1});
				q.push({i+1, j, stepsRemain-1});
				q.push({i, j-1, stepsRemain-1});
				q.push({i, j+1, stepsRemain-1});
			}
		}

		return pathsCount;
	}
};