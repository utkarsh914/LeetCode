// https://leetcode.com/problems/critical-connections-in-a-network/


/*
There are n servers numbered from 0 to n - 1 connected by undirected
server-to-server connections forming a network where connections[i] = [ai, bi]
represents a connection between servers ai and bi.
Any server can reach other servers directly or indirectly through the network.

A critical connection is a connection that, if removed,
will make some servers unable to reach some other server.

Return all critical connections in the network in any order.

 

Example 1:


Input: n = 4, connections = [[0,1],[1,2],[2,0],[1,3]]
Output: [[1,3]]
Explanation: [[3,1]] is also accepted.
Example 2:

Input: n = 2, connections = [[0,1]]
Output: [[0,1]]
 

Constraints:

2 <= n <= 105
n - 1 <= connections.length <= 105
0 <= ai, bi <= n - 1
ai != bi
There are no repeated connections.
*/








class FindBridges {
	int time;
	vector<bool> visited;
	vector<int> discoveryTime, lowLink;
	vector<vector<int>> ans;

public:
	vector<vector<int>> getBridges(vector<vector<int>>& graph) {
		int N = graph.size();
		time = 0;
		visited = vector<bool> (N, false);
		lowLink = vector<int> (N);
		discoveryTime = vector<int> (N);
		ans = vector<vector<int>> ();

		// run dfs on each unvisited node
		for (int u = 0; u < N; u++) {
			if (!visited[u]) dfs(graph, u, -1);
		}
		return ans;
	}

	void dfs(vector<vector<int>>& graph, int u, int parent) {
		visited[u] = true;
		discoveryTime[u] = lowLink[u] = time++;

		for (int v : graph[u]) {
			if (v == parent) continue;
			if (!visited[v]) {
				dfs(graph, v, u);
				lowLink[u] = min(lowLink[u], lowLink[v]);
				if (lowLink[v] > discoveryTime[u]) {
					ans.push_back({ u, v });
				}
			}
			else {
				lowLink[u] = min(lowLink[u], discoveryTime[v]);
			}
		}
	}
};


class Solution {
public:
	vector<vector<int>> criticalConnections(int n, vector<vector<int>>& edges) {
		vector<vector<int>> g(n);
		for (auto& e : edges) {
			g[e[0]].push_back(e[1]);
			g[e[1]].push_back(e[0]);
		}
		
		FindBridges obj;
		return obj.getBridges(g);
	}
};









import collections
class Solution:
	def criticalConnections(self, n: int, connections: List[List[int]]) -> List[List[int]]:

		def dfs(rank, curr, prev):
			low[curr], result = rank, []
			for neighbor in edges[curr]:
				if neighbor == prev: continue
				if not low[neighbor]:
					result += dfs(rank + 1, neighbor, curr)
				low[curr] = min(low[curr], low[neighbor])
				if low[neighbor] >= rank + 1:
					result.append([curr, neighbor])
			return result

		
		low, edges = [0] * n, collections.defaultdict(list)
		for u, v in connections:
			edges[u].append(v)
			edges[v].append(u)

		return dfs(1, 0, -1)