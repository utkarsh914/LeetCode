// https://leetcode.com/problems/pacific-atlantic-water-flow/

class Solution {
	bool vis[150][150];
public:
	vector<vector<int>> pacificAtlantic(vector<vector<int>>& M) {
		vector<vector<int>> ans;
		if (M.size() == 0) return ans;
		
		for (int i=0; i < M.size(); i++) {
			for (int j=0; j < M[0].size(); j++) {
				if (bfs(M, i, j) == "11")
					ans.push_back({i,j});
			}
		}

		return ans;
	}
	
	string bfs(vector<vector<int>>& M, int r, int c) {
		int dr[] = {-1, 0, 1,  0};
		int dc[] = { 0, 1, 0, -1};

		string ans = "00";
		queue<array<int,2>> q;
		memset(vis, 0, sizeof(vis));
		q.push({r,c});
		vis[r][c] = true;

		while (!q.empty()) {
			auto cur = q.front(); q.pop();
			int r = cur[0], c = cur[1];
			for (int k=0; k < 4; k++) {
				int x = r + dr[k], y = c + dc[k];
				if (x<0 or y<0) {
					ans[0] = '1';
				} else if (x >= M.size() or y >= M[0].size()) {
					ans[1] = '1';
				} else if (M[x][y] <= M[r][c] and vis[x][y] == false) {
					q.push({x,y});
					vis[x][y] = true;
				}
			}
		}

		return ans;
	}
};







class Solution {
	bool vis[150][150];
	int R, C;
public:
	vector<vector<int>> pacificAtlantic(vector<vector<int>>& M) {
		vector<vector<int>> ans;
		if (M.size() == 0) return ans;
		R = M.size(), C = M[0].size();

		vector<vector<bool>> atlantic(R, vector<bool>(C, false));
		vector<vector<bool>> pacific (R, vector<bool>(C, false));
		memset(vis, 0, sizeof(vis));

		for (int j=0; j < C; j++)
			if (!vis[0][j]) bfs(M, 0, j, pacific);

		for (int i=0; i < R; i++)
			if (!vis[i][0]) bfs(M, i, 0, pacific);

		memset(vis, 0, sizeof(vis));

		for (int j=0; j < C; j++)
			if (!vis[R-1][j]) bfs(M, R-1, j, atlantic);

		for (int i=0; i < R; i++)
			if (!vis[i][C-1]) bfs(M, i, C-1, atlantic);
		
		for (int i=0; i < R; i++) {
			for (int j=0; j < C; j++) {
				if (atlantic[i][j] && pacific[i][j])
					ans.push_back({i,j});
			}
		}

		return ans;
	}
	
	void bfs(vector<vector<int>>& M, int r, int c, vector<vector<bool>>& ocean) {
		int dr[] = {-1, 0, 1,  0};
		int dc[] = { 0, 1, 0, -1};

		queue<array<int,2>> q;
		q.push({r,c});
		vis[r][c] = true;
		ocean[r][c] = true;

		while (!q.empty()) {
			auto cur = q.front(); q.pop();
			int r = cur[0], c = cur[1];
			for (int k=0; k < 4; k++) {
				int x = r + dr[k], y = c + dc[k];
				if (x<0 or y<0 or x >= R or y >= C) continue;
				if (M[x][y] >= M[r][c] and vis[x][y] == false) {
					q.push({x,y});
					vis[x][y] = true;
					ocean[x][y] = true;
				}
			}
		}
	}
};