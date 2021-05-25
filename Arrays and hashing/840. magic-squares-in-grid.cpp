// https://leetcode.com/problems/magic-squares-in-grid/

class Solution {
public:
	int numMagicSquaresInside(vector<vector<int>>& G) {
		int R = G.size(), C = G[0].size();
		int count = 0;

		for (int i = 0; i+2 < R; i++)
			for (int j = 0; j+2 < C; j++)
				if (isMagic(G, i, j)) count++;

		return count;
	}

	bool isMagic(vector<vector<int>>& G, int x, int y) {
		unordered_set<int> set;
		for (int i = x; i < x+3; i++) {
			for (int j = y; j < y+3; j++) {
				set.insert(G[i][j]);
				if (G[i][j] > 9) return false;
			}
		}
		if (set.size() < 9) return false;

		// check all rows
		for (int i = x; i < x+3; i++)
			if (G[i][y+0] + G[i][y+1] + G[i][y+2] != 15)
				return false;
		// check all cols
		for (int j = y; j < y+3; j++)
			if (G[x+0][j] + G[x+1][j] + G[x+2][j] != 15)
				return false;
		// check diagonals
		int d1 = G[x+0][y+0] + G[x+1][y+1] + G[x+2][y+2];
		int d2 = G[x+0][y+2] + G[x+1][y+1] + G[x+2][y+0];

		return (d1 == 15 and d2 == 15);
	}
};