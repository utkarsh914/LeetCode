// https://leetcode.com/problems/minimum-degree-of-a-connected-trio-in-a-graph/

/*
HINTS:

1) Consider a trio with nodes u, v, and w.
The degree of the trio is just degree(u) + degree(v) + degree(w) - 6.
The -6 comes from subtracting the edges u-v, u-w, and v-w,
which are counted twice each in the vertex degree calculation.

2) To get the trios (u,v,w), you can iterate on u,
then iterate on each w,v such that w and v are neighbors of u
and are neighbors of each other.

*/
class Solution {
public:
	int minTrioDegree(int n, vector<vector<int>>& edges) {
		vector<int> deg(n+1);
		vector<vector<bool>> adj(n+1, vector<bool>(n+1, false));
		// count degrees of all nodes, and also form adjacency list
		for (auto& e : edges) {
			int u = e[0], v = e[1];
			deg[u]++; deg[v]++;
			adj[u][v] = adj[v][u] = true;
		}

		int minDeg = INT_MAX;

		for (int i=1; i <= n; i++) {
			if (deg[i] < 2) continue; // to form a trio, atleast 2 degree is needed
			for (int j=i+1; j <= n; j++) {
				if (deg[j] < 2) continue;
				for (int k=j+1; k <= n; k++) {
					if (deg[k] < 2) continue;
					if (adj[i][j] && adj[j][k] && adj[k][i]) { // check if i, j, k are actually connected
						int trioDeg = deg[i] + deg[j] + deg[k] - 6;
						minDeg = min(minDeg, trioDeg);
					}
				}
			}
		}
		
		return minDeg==INT_MAX ? -1 : minDeg;
	}
};