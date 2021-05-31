// https://leetcode.com/problems/possible-bipartition/


// we can get rid of vis array
class Solution {
	int N;
	vector<vector<int>> G;
	vector<int> color, vis;

public:
	bool possibleBipartition(int N, vector<vector<int>>& dislikes) {
		// build graph
		G.resize(N + 1);
		vis.resize(N + 1, false);
		color.resize(N + 1, false);
		for (auto& e : dislikes) {
			G[e[0]].push_back(e[1]);
			G[e[1]].push_back(e[0]);
		}

		this->N = N;
		return isBipartite();
	}

	bool isBipartite() {
		for (int i = 1; i <= N; i++)
			if (!vis[i] and !canPartition(i, true))
				return false;
		return true;
	}

	bool canPartition(int u, bool col) {
		color[u] = col;
		vis[u] = true;

		for (auto& v : G[u]) {
			if (!vis[v]) {
				if (!canPartition(v, !col))
					return false;
			}
			else if (color[v] == col)
				return false;
		}

		return true;
	}
};