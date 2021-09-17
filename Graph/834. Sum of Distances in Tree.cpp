// https://leetcode.com/problems/sum-of-distances-in-tree/

/*
There is an undirected connected tree with n nodes labeled from 0 to n - 1 and n - 1 edges.

You are given the integer n and the array edges where edges[i] = [ai, bi] indicates that there is an edge between nodes ai and bi in the tree.

Return an array answer of length n where answer[i] is the sum of the distances between the ith node in the tree and all other nodes.

 

Example 1:


Input: n = 6, edges = [[0,1],[0,2],[2,3],[2,4],[2,5]]
Output: [8,12,6,10,10,10]
Explanation: The tree is shown above.
We can see that dist(0,1) + dist(0,2) + dist(0,3) + dist(0,4) + dist(0,5)
equals 1 + 1 + 2 + 2 + 2 = 8.
Hence, answer[0] = 8, and so on.
Example 2:


Input: n = 1, edges = []
Output: [0]
Example 3:


Input: n = 2, edges = [[1,0]]
Output: [1,1]
 

Constraints:

1 <= n <= 3 * 104
edges.length == n - 1
edges[i].length == 2
0 <= ai, bi < n
ai != bi
The given input represents a valid tree.
*/











/*
What if given a tree, with a certain root 0?
In O(N) we can find sum of distances in tree from root and all other nodes.
Now for all N nodes?
Of course, we can do it N times and solve it in O(N^2).
C++ and Java may get accepted luckily, but it's not what we want.

When we move our root from one node to its connected node,
one part of nodes get closer, one the other part get further.

If we know exactly how many nodes in both parts, we can solve this problem.

With one single traversal in tree, we should get enough information for it and
don't need to do it again and again.
*/
class Solution {
	int totalSize;
	vector<int> ans;
	vector<vector<int>> g;
	vector<unordered_map<int,int>> subtreeSize;

public:
	vector<int> sumOfDistancesInTree(int n, vector<vector<int>>& edges) {
		ans = vector<int> (n, 0);
		g = vector<vector<int>> (n);
		subtreeSize = vector<unordered_map<int,int>> (n);
		
		for (auto& e : edges) {
			g[e[0]].push_back(e[1]);
			g[e[1]].push_back(e[0]);
		}
		
		ans[0] = getSum(0, 0).first;
		totalSize = n;
		dfs(-1, 0);
		return ans;
	}
	
	pair<int,int> getSum(int parent, int u) {
		int size = 1, sum = 0;
		for (int v : g[u]) {
			if (v == parent) continue;
			auto [subSum, subSize] = getSum(u, v);
			sum += subSum + subSize;
			size += subSize;
		}
		subtreeSize[parent][u] = size;
		return { sum, size };
	}
	
	void dfs(int parent, int u) {
		for (int v : g[u]) {
			if (v == parent) continue;
			int curSize = subtreeSize[u][v];
			int remainSize = totalSize - curSize;
			ans[v] = ans[u] - curSize + remainSize;
			dfs(u, v);
		}
	}
};








class Solution {
	vector<unordered_set<int>> tree;
	vector<int> res, count;

	vector<int> sumOfDistancesInTree(int N, vector<vector<int>>& edges) {
		tree.resize(N);
		res.assign(N, 0);
		count.assign(N, 1);

		for (auto e : edges) {
			tree[e[0]].insert(e[1]);
			tree[e[1]].insert(e[0]);
		}

		dfs(0, -1);
		dfs2(0, -1);
		return res;
	}

	void dfs(int root, int pre) {
		for (auto i : tree[root]) {
			if (i == pre) continue;
			dfs(i, root);
			count[root] += count[i];
			res[root] += res[i] + count[i];
		}
	}

	void dfs2(int root, int pre) {
		for (auto i : tree[root]) {
			if (i == pre) continue;
			res[i] = res[root] - count[i] + count.size() - count[i];
			dfs2(i, root);
		}
	}

};