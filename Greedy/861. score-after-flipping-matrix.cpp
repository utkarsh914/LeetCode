// https://leetcode.com/problems/score-after-flipping-matrix/

class Solution {
public:
	int matrixScore(vector<vector<int>>& G) {
		// flip rows if (row[0] != 1)
		for (auto& r : G) {
			if (r[0] != 1)
				for (int& n : r) n = !n;
		}
		// flip columns if count of 1s is less than zeros
		for (int j = 1; j < G[0].size(); j++) {
			// count ones
			int ones = 0, zeros = G.size();
			for (int i = 0; i < G.size(); i++)
				ones += G[i][j], zeros -= G[i][j];
			// flip if ones are lesser
			if (ones < zeros) {
				for (int i = 0; i < G.size(); i++)
					G[i][j] = !G[i][j];
			}
		}

		long ans = 0;
		for (auto& r : G) {
			int n = r[0];
			for (int i = 1; i < r.size(); i++)
				n = (n << 1) | r[i];
			ans += n;
		}

		return ans;
	}
};