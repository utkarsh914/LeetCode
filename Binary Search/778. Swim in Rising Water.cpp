// https://leetcode.com/problems/swim-in-rising-water/




/*
as grid elements are at in range [0, N*N-1]
we can binary search the value of ans in above range
and run dfs ever time to see if we can reach the end with 'level'
*/
class Solution {
	int N;
	bool vis[50][50];
public:
	int swimInWater(vector<vector<int>>& g) {
		N = g.size();
		int lo = 0, hi = N*N;

		while (lo < hi) {
			int level = lo + (hi-lo)/2;
			memset(vis, 0, sizeof(vis));
			if (canReachEnd(g, 0, 0, level))
				hi = level;
			else lo = level + 1;
		}

		return lo;
	}

	bool canReachEnd(vector<vector<int>>& g, int r, int c, int level) {
		vis[r][c] = true;
		if (r == N-1 and c == N-1) return true;
		// curr square should also be <= level
		// only then I can jump from it to other square <= level
		if (g[r][c] > level) return false;
		vector<pair<int,int>> cords {{r+1,c}, {r-1,c}, {r,c+1}, {r,c-1}};
		for (auto [i, j] : cords) {
			if (i<0 or i>=N or j<0 or j>=N
				or g[i][j] > level or vis[i][j])
				continue;
			if (canReachEnd(g, i, j, level))
				return true;
		}
		return false;
	}
};