// https://leetcode.com/problems/maximize-grid-happiness/



// --------- INCORRECT SOLUTION ----------
// ----------- TO DO LATER ------------
class Solution {
	int R, C, maxHappiness;
	vector<string> G;
	unordered_set<int> set;
	
public:
	int getMaxGridHappiness(int R, int C, int in, int ex) {
		this->R = R, this->C = C, this->maxHappiness = 0;
		G.resize(R, string(C, '.'));
		backtrack(0, in, ex);
		return this->maxHappiness;
	}

	void backtrack(int cell, int in, int ex) {
		
		if (set.count(mask(cell, in, ex))) return;
		
		if (cell >= R*C or in + ex == 0) {
			maxHappiness = max(maxHappiness, getHappiness());
			return;
		}

		int r = cell / C, c = cell % C;
		
		if (in > 0) {
			G[r][c] = 'I';
			backtrack(cell + 1, in - 1, ex);
			maxHappiness = max(maxHappiness, getHappiness());
		}

		if (ex > 0) {
			G[r][c] = 'E';
			backtrack(cell + 1, in, ex - 1);
			maxHappiness = max(maxHappiness, getHappiness());
		}

		G[r][c] = '.';
		backtrack(cell + 1, in, ex);
		maxHappiness = max(maxHappiness, getHappiness());

		// store to set
		set.insert(mask(cell, in, ex));
	}

	int getHappiness() {
		int happiness = 0;
		for (int i = 0; i < R; i++)
			for (int j = 0; j < C; j++)
				happiness += getScore(i, j);
		return happiness;
	}

	int getScore(int i, int j) {
		int dr[] = {-1,0,0,1}, dc[] = {0,-1,1,0};
		int neighbors = 0;
		for (int k = 0; k < 4; k++) {
			int x = i+dr[k], y = j+dc[k];
			if (x<0 or x>=R or y<0 or y>=C) continue;
			if (G[x][y] != '.') neighbors++;
		}
		if (G[i][j] == '.') return 0;
		else if (G[i][j] == 'I') return 120 - 30 * neighbors;
		else return 40 + 20 * neighbors;
	}

	int mask(int cell, int in, int ex) {
		int m = cell;
		m = ((m << 8) | in);
		m = ((m << 8) | ex);
		return m;
		// return to_string(cell)+","+to_string(in)+","+to_string(ex);
	}
};