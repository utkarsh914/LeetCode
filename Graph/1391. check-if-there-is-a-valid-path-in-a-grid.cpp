// https://leetcode.com/problems/check-if-there-is-a-valid-path-in-a-grid/


// //the idea is you need to check port direction match,
// you can go to next cell and check whether you can come back.
class Solution {
public:
	bool hasValidPath(vector<vector<int>>& grid) {
		vector<vector<vector<int>>> directs({
			{{0, -1}, {0, 1}},
			{{-1, 0}, {1, 0}},
			{{0, -1}, {1, 0}},
			{{0, 1}, {1, 0}},
			{{0, -1}, {-1, 0}},
			{{0, 1}, {-1, 0}}
		});

		int m = grid.size(), n = grid[0].size();
		vector<vector<bool>> visited(m, vector<bool>(n, false));
		queue<array<int,2>> bfs;

		bfs.push({0, 0});
		visited[0][0] = true;

		while (!bfs.empty()) {

			auto cur = bfs.front(); bfs.pop();
			int row = cur[0], col = cur[1];
			int type = grid[row][col] - 1;

			for (auto& dir : directs[type]) {
				int nr = row + dir[0], nc = col + dir[1];
				if (nr < 0 or nr >= m or nc < 0 or nc >= n or visited[nr][nc])
					continue;
				// //go to the next cell and come back to orign to see if port directions are same
				auto& backDir = directs[grid[nr][nc] - 1];
				if ((nr + backDir[0][0] == row and nc + backDir[0][1] == col)
				or  (nr + backDir[1][0] == row and nc + backDir[1][1] == col)) {
					visited[nr][nc] = true;
					bfs.push({nr, nc});
				}

			}
		}

		return visited[m - 1][n - 1];
	}
};











// ********* USING UNION FIND ********
class Solution {

int m, n;
vector<int> parent;

void init_UF() {
	parent.resize(m * n);
	for (int i = 0; i < parent.size(); i++)
		parent[i] = i;
}

int find(int x) {
	if (parent[x] != x)
		parent[x] = find(parent[x]);
	return parent[x];
}

void uni(int x, int y) {
	x = find(x), y = find(y);
	if (x != y) parent[y] = x;
}

int ind(int i, int j) {
	return i * n + j;
}

public:
	bool hasValidPath(vector<vector<int>>& grid) {
		vector<vector<vector<int>>> directs({
			{{0, -1}, {0, 1}},
			{{-1, 0}, {1, 0}},
			{{0, -1}, {1, 0}},
			{{0, 1}, {1, 0}},
			{{0, -1}, {-1, 0}},
			{{0, 1}, {-1, 0}}
		});

		m = grid.size(), n = grid[0].size();
		init_UF();

		for (int row = 0; row < m; row++) {
			for (int col = 0; col < n; col++) {
				int type = grid[row][col] - 1;

				for (auto& dir : directs[type]) {
					int nr = row + dir[0], nc = col + dir[1];
					if (nr < 0 or nr >= m or nc < 0 or nc >= n)
						continue;
					// go to the next cell and come back to see if port directions are same
					// if satisfies, make a union with the current cell
					auto& backDir = directs[grid[nr][nc] - 1];
					if ((nr + backDir[0][0] == row and nc + backDir[0][1] == col)
					or  (nr + backDir[1][0] == row and nc + backDir[1][1] == col)) {
						uni(ind(row, col), ind(nr, nc));
					}
				}
			}
		}

		// start and end should be connected (same group)
		// i.e. their parent should be same
		return find(ind(0,0)) == find(ind(m-1,n-1));
	}
};