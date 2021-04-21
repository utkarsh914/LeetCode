/*
https://leetcode.com/problems/number-of-islands/

Given an m x n 2d grid map of '1's (land) and '0's (water), return the number of islands.
An island is surrounded by water and is formed by connecting adjacent lands horizontally or vertically.
You may assume all four edges of the grid are all surrounded by water.

Example 1:

Input: grid = [
  ["1","1","1","1","0"],
  ["1","1","0","1","0"],
  ["1","1","0","0","0"],
  ["0","0","0","0","0"]
]
Output: 1
*/


class Solution {
public:

int R, C;
vector<int> parent;

int find(int x) {
	if (parent[x] != x)
		parent[x] = find(parent[x]);
	return parent[x];
}

void uni(int x, int y) {
	x = find(x);
	y = find(y);
	if (x != y) {
		parent[y] = x;
	}
}

int ind(int i, int j) {
	return i*C + j;
}

bool isValid(int r, int c, vector<vector<char>>& grid) {
	return (r>=0 && r<R && c>=0 && c<C && grid[r][c]=='1');
}

int numIslands(vector<vector<char>>& grid) {
	R = grid.size(), C=grid[0].size();
	parent = vector<int> (R*C);
	for (int i=0; i<parent.size(); i++)
		parent[i]=i;
	// make unions
	for (int i=0; i<R; i++) {
		for (int j=0; j<C; j++) {
			if (!isValid(i,j,grid))
				continue;
			if (isValid(i-1,j,grid)) uni(ind(i,j), ind(i-1,j));
			if (isValid(i+1,j,grid)) uni(ind(i,j), ind(i+1,j));
			if (isValid(i,j-1,grid)) uni(ind(i,j), ind(i,j-1));
			if (isValid(i,j+1,grid)) uni(ind(i,j), ind(i,j+1));
		}
	}

	vector<int> freq(R*C, 0);
	int count = 0;
	for (int i=0; i<R; i++) {
		for (int j=0; j<C; j++) {
			if (grid[i][j] != '1')
				continue;
			int p = find(ind(i,j));
			if (freq[p] == 0)
				count++;
			freq[p]++;
		}
	}

	return count;
}};


// //*********** more cleaner implementation *********
// class Solution {
// public:
// 	int removeStones(vector<vector<int>>& stones) {
// 		for (int i = 0; i < stones.size(); ++i)
// 			uni(stones[i][0], ~stones[i][1]);
// 		return stones.size() - islands;
// 	}

// 	unordered_map<int, int> f;
// 	int islands = 0;

// 	int find(int x) {
// 		if (!f.count(x)) f[x] = x, islands++;
// 		if (x != f[x]) f[x] = find(f[x]);
// 		return f[x];
// 	}

// 	void uni(int x, int y) {
// 		x = find(x), y = find(y);
// 		if (x != y) f[x] = y, islands--;
// 	}
// };