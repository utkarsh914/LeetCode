// https://leetcode.com/problems/checking-existence-of-edge-length-limited-paths/

/*
An undirected graph of n nodes is defined by edgeList, where edgeList[i] = [ui, vi, disi] denotes an edge between nodes ui and vi with distance disi. Note that there may be multiple edges between two nodes.

Given an array queries, where queries[j] = [pj, qj, limitj], your task is to determine for each queries[j] whether there is a path between pj and qj such that each edge on the path has a distance strictly less than limitj .

Return a boolean array answer, where answer.length == queries.length and the jth value of answer is true if there is a path for queries[j] is true, and false otherwise.

 

Example 1:


Input: n = 3, edgeList = [[0,1,2],[1,2,4],[2,0,8],[1,0,16]], queries = [[0,1,2],[0,2,5]]
Output: [false,true]
Explanation: The above figure shows the given graph. Note that there are two overlapping edges between 0 and 1 with distances 2 and 16.
For the first query, between 0 and 1 there is no path where each distance is less than 2, thus we return false for this query.
For the second query, there is a path (0 -> 1 -> 2) of two edges with distances less than 5, thus we return true for this query.
Example 2:


Input: n = 5, edgeList = [[0,1,10],[1,2,5],[2,3,9],[3,4,13]], queries = [[0,4,14],[1,4,13]]
Output: [true,false]
Exaplanation: The above figure shows the given graph.
 

Constraints:

2 <= n <= 105
1 <= edgeList.length, queries.length <= 105
edgeList[i].length == 3
queries[j].length == 3
0 <= ui, vi, pj, qj <= n - 1
ui != vi
pj != qj
1 <= disi, limitj <= 109
There may be multiple edges between two nodes.
*/






/*
All the queries are given in advance.
Is there a way you can reorder the queries to avoid repeated computations?


The key here is to notice that the queries are offline which means that we can reorganize them however we want.

Now to answer the question, whether there is a path between any two nodes where the maximum edge length or weight is less than limit, we can join all the edges whose weight is less than limit and if we are still not able to reach one node from the other it essentially means that there is no path between them where edge weight is less than limit.

Which is the best data structure that can help us join edges as we want and answer whether in that structure, node a and node b are connected ?
That's right! DSU.

Let's try and use these facts to solve the question.

Solution

First we need to sort the input queries and edgeList by edge length or weight.

We can now simply use a two pointer approach to Union all the nodes whose edges have weight less than query[i].

To know if there is a path between them all we need is to know whether their parents (in DSU) are same.
*/
class Solution {
	vector<int> p;
	
	inline int find(int x) {
		if (p[x] != x) p[x] = find(p[x]);
		return p[x];
	}
	
	inline void uni(int x, int y) {
		x = find(x), y = find(y);
		if (x != y) p[y] = x;
	}
	
public:
	vector<bool> distanceLimitedPathsExist(int n, vector<vector<int>>& edges,
		vector<vector<int>>& queries) {

		vector<bool> ans(queries.size());
		for (int i = 0; i < n; i++) p.push_back(i);
		
		// store index of queries in them
		for (int i = 0; i < queries.size(); i++)
			queries[i].push_back(i);
		// sort queries by size (q[2])
		sort(queries.begin(), queries.end(), [](auto& a, auto& b) { return a[2] < b[2]; });
		// sort edges by size (edges[2])
		sort(edges.begin(), edges.end(), [](auto& a, auto& b) { return a[2] < b[2]; });
		
		int i = 0;
		for (auto& q : queries) {
			int u = q[0], v = q[1], limit = q[2], ind = q[3];
			while (i < edges.size() and edges[i][2] < limit)
				uni(edges[i][0], edges[i][1]), i++;
			ans[ind] = find(u) == find(v);
		}
		
		return ans;
	}
};