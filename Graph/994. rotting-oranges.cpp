// https://leetcode.com/problems/rotting-oranges/

class Solution {
public:
	int orangesRotting(vector<vector<int>>& G) {
		int R = G.size(), C = G[0].size();
		queue<vector<array<int,2>>> q;
		// push initially rotten oranges
		int fresh = 0, minutes = 0;
		vector<array<int,2>> subQ;
		for (int i=0; i < R; i++) {
			for (int j=0; j < C; j++) {
				if (G[i][j] == 1) fresh++;
				else if (G[i][j] == 2) subQ.push_back({i,j});
			}
		}
		q.push(subQ);

		while (!q.empty()) {
			auto curQ = q.front(); q.pop();
			subQ.clear();
			for (auto& o : curQ) {
				fresh -= rotFromThis(G, subQ, o[0], o[1]);
			}
			if (subQ.empty()) break;
			else q.push(subQ);
			minutes++;
		}

		return fresh == 0 ? minutes : -1;
	}

	int rotFromThis(vector<vector<int>>& G,
		vector<array<int,2>>& subQ, int r, int c) {
		int R = G.size(), C = G[0].size();
		int rotten = 0;
		int dr[] = {-1,0,1,0};
		int dc[] = {0,1,0,-1};

		for (int i=0; i < 4; i++) {
			int x = r+dr[i], y = c+dc[i];
			if (x>=0 && x<R && y>=0 && y<C && G[x][y]==1) {
				rotten++;
				G[x][y] = 2;
				subQ.push_back({x,y});
			}
		}

		return rotten;
	}
};











class Solution { // O(n) BFS
public:
	const int dx[4] = {0, 0, 1, -1};
	const int dy[4] = {1, -1, 0, 0};
	
	int orangesRotting(vector<vector<int>>& grid) {
		if(grid.empty()) return 0;
		int m = grid.size(), n = grid[0].size(), days = 0, tot = 0, cnt = 0;
		queue<pair<int, int>> rotten;
		
		for(int i = 0; i < m; ++i) {
			for(int j = 0; j < n; ++j) {
				if(grid[i][j] != 0) tot++;
				if(grid[i][j] == 2) rotten.push({i, j});
			}
		}
		
		while(!rotten.empty()) {
			int k = rotten.size();
			cnt += k; 
			while(k--) {
				int x = rotten.front().first, y = rotten.front().second;
				rotten.pop();
				for(int i = 0; i < 4; ++i) {
					int nx = x + dx[i], ny = y + dy[i];
					if(nx < 0 || ny < 0 || nx >= m || ny >= n || grid[nx][ny] != 1) continue;
					grid[nx][ny] = 2;
					rotten.push({nx, ny});
				}
			}
			if(!rotten.empty()) days++;
		}
		
		return tot == cnt ? days : -1;
	}
};