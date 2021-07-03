// https://leetcode.com/problems/remove-max-number-of-edges-to-keep-graph-fully-traversable/

/*
Alice and Bob have an undirected graph of n nodes and 3 types of edges:

Type 1: Can be traversed by Alice only.
Type 2: Can be traversed by Bob only.
Type 3: Can by traversed by both Alice and Bob.
Given an array edges where edges[i] = [typei, ui, vi] represents a bidirectional edge of type typei between nodes ui and vi, find the maximum number of edges you can remove so that after removing the edges, the graph can still be fully traversed by both Alice and Bob. The graph is fully traversed by Alice and Bob if starting from any node, they can reach all other nodes.

Return the maximum number of edges you can remove, or return -1 if it's impossible for the graph to be fully traversed by Alice and Bob.
*/









/*
Build the network instead of removing extra edges.
Suppose you have the final graph (after removing extra edges). Consider the subgraph with only the edges that Alice can traverse. What structure does this subgraph have? How many edges are there?
Use disjoint set union data structure for both Alice and Bob.
Always use Type 3 edges first, and connect the still isolated ones using other edges.
*/
class Solution {
public:
	vector<vector<int>> p;

	int find(int x, int type) {
		if (p[type-1][x] != x)
			p[type-1][x] = find(p[type-1][x], type);
		return p[type-1][x];
	}

	void uni(int x, int y, int type) {
		x = find(x, type);
		y = find(y, type);
		if (x != y) p[type-1][x] = y;
	}

	int maxNumEdgesToRemove(int n, vector<vector<int>>& edges) {
		// initialize Union Find data structure
		p.resize(2, vector<int> (n+1));
		for (int i = 1; i <= n; i++)
			p[0][i] = p[1][i] = i;

		int type1 = 0, type2 = 0, type3 = 0;

		// pick common edges first (i.e. type 3)
		// and add it in both subgraphs
		for (auto& e : edges) {
			if (e[0] != 3) continue;
			if (find(e[1], 1) != find(e[2], 1)) {
				uni(e[1], e[2], 1);
				uni(e[1], e[2], 2);
				type3++;
			}
		}

		// now pick needed type 1 edges to build subgraph of Alice
		for (auto& e : edges) {
			if (e[0] != 1) continue;
			if (find(e[1], 1) != find(e[2], 1)) {
				uni(e[1], e[2], 1);
				type1++;
			}
		}

		// now pick needed type 2 edges to build subgraph of Bob
		for (auto& e : edges) {
			if (e[0] != 2) continue;
			if (find(e[1], 2) != find(e[2], 2)) {
				uni(e[1], e[2], 2);
				type2++;
			}
		}
		
		if (type1 + type3 != n-1 or type2 + type3 != n-1)
			return -1;
		return edges.size() - (type1 + type2 + type3);
	}
};