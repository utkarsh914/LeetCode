// https://leetcode.com/problems/largest-color-value-in-a-directed-graph/

/*
There is a directed graph of n colored nodes and m edges. The nodes are numbered from 0 to n - 1.

You are given a string colors where colors[i] is a lowercase English letter representing the color of the ith node in this graph (0-indexed). You are also given a 2D array edges where edges[j] = [aj, bj] indicates that there is a directed edge from node aj to node bj.

A valid path in the graph is a sequence of nodes x1 -> x2 -> x3 -> ... -> xk such that there is a directed edge from xi to xi+1 for every 1 <= i < k. The color value of the path is the number of nodes that are colored the most frequently occurring color along that path.

Return the largest color value of any valid path in the given graph, or -1 if the graph contains a cycle.

 

Example 1:



Input: colors = "abaca", edges = [[0,1],[0,2],[2,3],[3,4]]
Output: 3
Explanation: The path 0 -> 2 -> 3 -> 4 contains 3 nodes that are colored "a" (red in the above image).
Example 2:



Input: colors = "a", edges = [[0,0]]
Output: -1
Explanation: There is a cycle from 0 to 0.
 

Constraints:

n == colors.length
m == edges.length
1 <= n <= 105
0 <= m <= 105
colors consists of lowercase English letters.
0 <= aj, bj < n
*/





class Solution {
	vector<vector<int>> g;
	vector<vector<int>> dp;
	vector<bool> vis, stk;
	int mx = 0;

public:
	int largestPathValue(string& colors, vector<vector<int>>& edges) {		
		int N = colors.size();
		g.resize(N);
		vis.resize(N, false);
		stk.resize(N, false);
		dp.resize(N, vector<int> (26, 0));
		// build graph
		for (auto& e : edges)
			g[e[0]].push_back(e[1]);
		
		// dfs from each vertex
		for (int u = 0; u < N; u++)
			if (!vis[u] and dfs(colors, u))
				return -1;
		
		return mx;
	}
	// returns true on finding a cycle
	// also keeps updating the answer in other case
	bool dfs(string& colors, int u) {
		vis[u] = stk[u] = true;
		vector<int>& ans = dp[u];
		
		for (int v : g[u]) {
			if (!vis[v]) {
				if (dfs(colors, v))
					return true;
			}
			else if (stk[v])
				return true;

			vector<int>& subans = dp[v];
			for (int i = 0; i < 26; i++)
				ans[i] = max(ans[i], subans[i]);
		}
		
		ans[colors[u] - 'a']++;
		// update global ans if cycle hasn't been detected
		for (int i = 0; i < 26; i++)
			mx = max(mx, ans[i]);

		stk[u] = false;
		return false;
	}
};







/*
----- Topological Sort ------

Intuition: We can use BFS Topological Sort to visit the nodes.
When visiting the next node, we can forward the color information to the next node.
Also Topo-sort can help detect circle.
*/
class Solution {
	typedef array<int, 26> T;
public:
	int largestPathValue(string C, vector<vector<int>>& E) {
		unordered_map<int, vector<int>> G;
		vector<int> indegree(C.size());
		for (auto &e : E) {
			G[e[0]].push_back(e[1]); // build graph
			indegree[e[1]]++; // count indegrees
		}
		vector<T> cnt(C.size(), T{}); // cnt[i][j] is the maximum count of j-th color from the ancester nodes to node i.
		queue<int> q;
		for (int i = 0; i < C.size(); ++i) {
			if (indegree[i] == 0) { // if this node has 0 indegree, we can use it as a source node
				q.push(i);
				cnt[i][C[i] - 'a'] = 1; // the count of the current color should be 1
			}
		}
		int ans = 0, seen = 0;
		while (q.size()) {
			auto u = q.front();
			q.pop();
			int val = *max_element(begin(cnt[u]), end(cnt[u])); // we use the maximum of all the maximum color counts as the color value.
			ans = max(ans, val);
			++seen;
			for (int v : G[u]) {
				for (int i = 0; i < 26; ++i) {
					cnt[v][i] = max(cnt[v][i], cnt[u][i] + (i == C[v] - 'a')); // try to use node `u` to update all the color counts of node `v`.
				}
				if (--indegree[v] == 0) {
					q.push(v);
				}
			}
		}
		return seen < C.size() ? -1 : ans;
	}
};
/*
This line int val = *max_element(begin(cnt[u]), end(cnt[u]));
can be replaced with int val = cnt[u][C[u] - 'a'];
because there must be a path that has the greatest color value
and ends with the corresponding color.
*/