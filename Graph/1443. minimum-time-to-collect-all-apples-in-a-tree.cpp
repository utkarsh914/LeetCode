// https://leetcode.com/problems/minimum-time-to-collect-all-apples-in-a-tree/

/*
Given an undirected tree consisting of n vertices numbered from 0 to n-1, which has some apples in their vertices. You spend 1 second to walk over one edge of the tree. Return the minimum time in seconds you have to spend to collect all apples in the tree, starting at vertex 0 and coming back to this vertex.

The edges of the undirected tree are given in the array edges, where edges[i] = [ai, bi] means that exists an edge connecting the vertices ai and bi. Additionally, there is a boolean array hasApple, where hasApple[i] = true means that vertex i has an apple; otherwise, it does not have any apple.

Example 1:



Input: n = 7, edges = [[0,1],[0,2],[1,4],[1,5],[2,3],[2,6]], hasApple = [false,false,true,false,true,true,false]
Output: 8 
Explanation: The figure above represents the given tree where red vertices have an apple. One optimal path to collect all apples is shown by the green arrows.  

Example 2:

Input: n = 7, edges = [[0,1],[0,2],[1,4],[1,5],[2,3],[2,6]], hasApple = [false,false,true,false,false,true,false]
Output: 6
Explanation: The figure above represents the given tree where red vertices have an apple. One optimal path to collect all apples is shown by the green arrows.  

Example 3:

Input: n = 7, edges = [[0,1],[0,2],[1,4],[1,5],[2,3],[2,6]], hasApple = [false,false,false,false,false,false,false]
Output: 0
*/








/*
Note that if a node u contains an apple then all edges in the path from the root to the node u have to be used forward and backward (2 times).
Therefore use a depth-first search (DFS) to check if an edge will be used or not.
*/
class Solution {
	vector<vector<int>> G;
	vector<bool> vis;
	vector<bool> subtreeHasApple;

public:
	int minTime(int n, vector<vector<int>>& edges, vector<bool>& hasApple) {
		G.resize(n);
		for (auto& e : edges) {
			G[e[0]].push_back(e[1]);
			G[e[1]].push_back(e[0]);
		}
		vis.resize(n, false);
		subtreeHasApple.resize(n, false); // if subtree of i has any apple

		// check if subtree has apples
		bool treeHasApples = checkIfsubtreeHasApples(0, hasApple);
		if (!treeHasApples) return 0;

		vis = vector<bool> (n, false);
		return dfs(0);
	}

	int dfs(int u) {
		vis[u] = true;
		int ans = 0;
		for (auto& v : G[u]) {
			if (!vis[v] and subtreeHasApple[v])
				ans += 2 + dfs(v);
		}
		return ans;
	}

	bool checkIfsubtreeHasApples(int u, vector<bool>& hasApple) {
		vis[u] = true;
		bool ans = hasApple[u];
		for (auto& v : G[u]) {
			if (!vis[v] && checkIfsubtreeHasApples(v, hasApple))
				ans = true;
		}
		return subtreeHasApple[u] = ans;
	}
};