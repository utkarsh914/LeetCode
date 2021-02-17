/*
https://leetcode.com/problems/is-graph-bipartite/

Given an undirected graph, return true if and only if it is bipartite.
Recall that a graph is bipartite if we can split its set of nodes into two independent subsets A and B,
such that every edge in the graph has one node in A and another node in B.
The graph is given in the following form: graph[i] is a list of indexes j for which the edge between nodes i and j exists.
Each node is an integer between 0 and graph.length - 1.
There are no self edges or parallel edges: graph[i] does not contain i, and it doesn't contain any element twice.

Example 1:
Input: graph = [[1,3],[0,2],[1,3],[0,2]]
Output: true
Explanation: We can divide the vertices into two groups: {0, 2} and {1, 3}.

*/
class Solution {
public:

vector<bool> visited, colour;

bool dfs(vector<vector<int>>& graph, int v, bool col) {
	visited[v] = true;
	colour[v] = col;
	for (auto i:graph[v]) {
		if (!visited[i]) {
			if (!dfs(graph,i,!col))
				return false;
		}
		else if (colour[i] == col)
			return false;
	}
	return true;
}

bool bfs(vector<vector<int>>& graph, int source) {
	queue<pair<int,bool>> q;
	q.push({source,true});
	while (!q.empty()) {
		int v = q.front().first;
		bool col = q.front().second; q.pop();
		visited[v] = true; colour[v] = col;
		for (auto i:graph[v]) {
			if (!visited[i])
				q.push({i, !col});
			else if (colour[i] == col)
				return false;
		}
	}
	return true;
}

bool isBipartite(vector<vector<int>>& graph) {
	visited = vector<bool> (graph.size(), false);
	colour = vector<bool> (graph.size(), false);
	for (int i=0; i<graph.size(); i++)
		if (!visited[i])
			if (!bfs(graph, i)) // use bfs or dfs (any)
				return false;
	return true;
}};














class Solution {
	vector<bool> vis, col;
public:
	bool isBipartite(vector<vector<int>>& graph) {
		int size = graph.size();
		vis.resize(size, false), col.resize(size, false);
		
		for (int i=0; i < size; i++) {
			if (!vis[i] && check(graph, i)==false)
				return false;
		}
		
		return true;
	}
	
	bool check(vector<vector<int>>& graph, int V) {
		queue<int> q;
		q.push(V);
		col[V] = true, vis[V] = true;
		
		while (!q.empty()) {
			int u = q.front(); q.pop();
			for (auto& v : graph[u]) {
				if (!vis[v]) {
					vis[v] = true;
					col[v] = !col[u];
					q.push(v);
				} // if visited already, color should be different
				else if (col[v] == col[u])
					return false;
			}
		}
		
		return true;
	}
};