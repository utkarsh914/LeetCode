/*
https://leetcode.com/problems/minimum-height-trees/

A tree is an undirected graph in which any two vertices are connected by exactly one path. In other words,
any connected graph without simple cycles is a tree.
Given a tree of n nodes labelled from 0 to n - 1, and an array of n - 1 edges where edges[i] = [ai, bi] indicates
that there is an undirected edge between the two nodes ai and bi in the tree,
you can choose any node of the tree as the root. When you select a node x as the root,
the result tree has height h. Among all possible rooted trees, those with minimum height (i.e. min(h))
are called minimum height trees (MHTs).

Return a list of all MHTs' root labels. You can return the answer in any order.
The height of a rooted tree is the number of edges on the longest downward path between the root and a leaf.

Example 1:
Input: n = 4, edges = [[1,0],[1,2],[1,3]]
Output: [1]
Explanation: As shown, the height of the tree is 1 when the root is the node with label 1 which is the only MHT.

Example 2:
Input: n = 6, edges = [[3,0],[3,1],[3,2],[3,4],[5,4]]
Output: [3,4]

Example 3:
Input: n = 1, edges = []
Output: [0]

Example 4:
Input: n = 2, edges = [[0,1]]
Output: [0,1]

Constraints:
1 <= n <= 2 * 104
edges.length == n - 1
0 <= ai, bi < n
ai != bi
All the pairs (ai, bi) are distinct.
The given input is guaranteed to be a tree and there will be no repeated edges.
*/


// *************** USING KAHN'S ALGO **********************
// IDEA: keep removing leaves until only 1 or 2 leaves left

class Solution {
public:
vector<int> findMinHeightTrees(int N, vector<vector<int>>& edges) {
	if (edges.size()==0) return {0};
	// build graph
	vector<vector<int>> graph(N, vector<int>());
	vector<int> degree(N, 0);
	for (auto& e:edges) {
		int u=e[0], v=e[1];
		graph[u].push_back(v), graph[v].push_back(u);
		degree[u]++, degree[v]++;
	}
	// push leaves to queue
	queue<int> q;
	for (int i=0; i<N; i++)
		if (degree[i]==1) q.push(i);

	// keep popping and decreasing the total number of nodes
	while (N > 2) {
		int size = q.size();
		N -= size;
		while (size--) {
			int u = q.front(); q.pop();
			for (auto v:graph[u])
				if (--degree[v]==1)
					q.push(v);
		}
	}

	vector<int> ans;
	while (!q.empty()) {
		ans.push_back(q.front()); q.pop();
	}
	return ans;
}};



// *************** USING DFS *****************
// ********* BY FINDING LONGEST PATH *********
// ************* (SLOWER) ********************
class Solution {
public:
// find longest path using dfs
vector<int> longestPath(int V, vector<vector<int>> &graph, vector<bool>& vis) {
	vis[V] = true;
	vector<vector<int>> paths;
	for (auto n:graph[V]) {
		if (vis[n]) continue;
		paths.push_back(longestPath(n,graph,vis));
	}
	if (paths.size()==0) return vector<int>(1,V);
	// find and return path with max length
	int maxl=0, ind=-1;
	for (int i=0; i<paths.size(); i++)
		if (paths[i].size()>maxl) maxl=paths[i].size(), ind=i;
	// push curr node in that path and return
	paths[ind].push_back(V);
	return paths[ind];
}

vector<int> findMinHeightTrees(int N, vector<vector<int>>& edges) {
	// build graph
	vector<vector<int>> graph(N, vector<int>());
	for (auto& e:edges)
		graph[e[0]].push_back(e[1]), graph[e[1]].push_back(e[0]);
	//find farthest node from node 0
	vector<bool> vis(N, false);
	int A = longestPath(0, graph, vis).front();
	fill(vis.begin(), vis.end(), false);
	// find longst path from that furthest node(A).
	// this is the overall longst path
	vector<int> path = longestPath(A, graph, vis);
	int s = path.size();
	// return middle element if path length is odd, else middle 2 elements
	if (s%2 == 1) return {path[s/2]};
	else return {path[(s/2)-1], path[s/2]};
}};