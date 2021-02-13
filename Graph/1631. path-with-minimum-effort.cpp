/*
https://leetcode.com/problems/path-with-minimum-effort/

You are a hiker preparing for an upcoming hike. You are given heights, a 2D array of size rows x columns,
where heights[row][col] represents the height of cell (row, col). You are situated in the top-left cell,
(0, 0), and you hope to travel to the bottom-right cell, (rows-1, columns-1) (i.e., 0-indexed).
You can move up, down, left, or right, and you wish to find a route that requires the minimum effort.
A route's effort is the maximum absolute difference in heights between two consecutive cells of the route.
Return the minimum effort required to travel from the top-left cell to the bottom-right cell.

Example 1:
Input: heights = [[1,2,2],[3,8,2],[5,3,5]]
Output: 2
Explanation: The route of [1,3,5,3,5] has a maximum absolute difference of 2 in consecutive cells.
This is better than the route of [1,2,2,2,5], where the maximum absolute difference is 3.

Example 2:
Input: heights = [[1,2,3],[3,8,4],[5,3,5]]
Output: 1
Explanation: The route of [1,2,3,4,5] has a maximum absolute difference of 1 in consecutive cells, which is better than route [1,3,5,3,5].

Example 3:
Input: heights = [[1,2,1,1,1],[1,2,1,2,1],[1,2,1,2,1],[1,2,1,2,1],[1,1,1,2,1]]
Output: 0
Explanation: This route does not require any effort.

Constraints:
rows == heights.length
columns == heights[i].length
1 <= rows, columns <= 100
1 <= heights[i][j] <= 106
*/

// ****************** USING DIJKSTRA *******************
class Solution {
public:
// To compare two points
class myComp {
public:
	int operator() (const vector<int>& v1, const vector<int>& v2) {
		return v1[0] > v2[0];
	}
};

int minimumEffortPath(vector<vector<int>>& h) {
	int R=h.size(), C=h[0].size();
	int dr[4] = {-1,1,0,0}, dc[4] = {0,0,1,-1};
	vector<vector<int>> dist(R, vector<int>(C, INT_MAX));
	// run dijkstra
	priority_queue<vector<int>, vector<vector<int>>, myComp> pq;
	pq.push(vector<int>(3,0));
	while (!pq.empty()) {
		vector<int> curr = pq.top(); pq.pop();
		int d=curr[0], r=curr[1], c=curr[2];
		if (d > dist[r][c]) continue;
		if (r==R-1 and c==C-1) return d; // reached last
		for (int k=0; k<4; k++) {
			int rr=r+dr[k], cc=c+dc[k];
			if (rr<0 or rr>=R or cc<0 or cc>=C) continue;
			int newDist = max(d, abs(h[r][c]-h[rr][cc]));
			if (newDist < dist[rr][cc]) {
				dist[rr][cc] = newDist;
				pq.push({newDist, rr, cc});
			}
		}
	}
	return 0;
}};





/* **************** PYTHON (UNION FIND) ****************
My initial approach is gather all the unique links between cells, (If you have cell u at (i, j) and v at (i+1, j),
(u, v) is the tuple that uniquely represents the link between them), and go through all the links in ascending effort.
For each u, v in a link, union the cells u and v ala the disjoint-set datastructure.
We stop if we discover cell (0, 0) and (rows-1, columns-1) becomes connected, ie.
when they become part of the same disjoint-set. If we have M rows and N columns,
the run-time is O(MN) + O(MN * (log(MN) + union_cost + find_cost)).
Where union_cost and find_cost should be something smaller than O(log(MN)).

Correctness of the solution is "obvious". At some point we will union enough cells so that there's a path
from (0, 0) to (M - 1, N - 1). And since we union cells in ascending absolute difference in height,
as soon as (0, 0) becomes reachable to (M - 1, N - 1), the route effort will be the maximum over links
with the smallest height differences. So it a guaranteed to be the minimum route effort.
*/
class Solution:
	def minimumEffortPath(self, heights: List[List[int]]) -> int:
		# parent and rank for union-find 
		p = {}
		rank = collections.defaultdict(int)
		
		# Record the links by ascending effort in heap so we only pay the cost of popping
		# the links needed to get `start` connected to `end`.
		h = []
		for i in range(len(heights)):
			for j in range(len(heights[i])):
				u = (i, j)
				p[u] = u
				# Record the link to the neighbor immediately to the right
				v = (i, j + 1)
				if v[1] < len(heights[i]):
					heapq.heappush(h, [abs(heights[u[0]][u[1]] - heights[v[0]][v[1]]), u, v])
				# Record the link to the neighbor immediately below
				v = (i + 1, j)
				if v[0] < len(heights):
					heapq.heappush(h, [abs(heights[u[0]][u[1]] - heights[v[0]][v[1]]), u, v])
		
		
		def find(u):
			if p[u] == u:
				return u
			p[u] = find(p[u])
			return p[u]
		
		def union(u, v):
			root_u, root_v = find(u), find(v)
			if root_u == root_v:
				return
			if rank[root_u] < rank[root_v]:
				p[root_u] = root_v
			elif rank[root_v] < rank[root_u]:
				p[root_v] = root_u
			else:
				p[root_u] = root_v
				rank[root_v] += 1

		start = (0, 0)
		end = (len(heights) - 1, len(heights[-1]) - 1)
		while len(h) > 0:
			min_effort, u, v = heapq.heappop(h)
			union(u, v)
			if find(start) == find(end):
				return min_effort
			
		return 0




/* ************ incomplete ***********

class Solution {
public:
int R, C;
int ind(int i, int j) {
	return C*i + j;
}
int minimumEffortPath(vector<vector<int>>& h) {
	R=h.size(), C=h[0].size();
	int dr[4] = {-1,1,0,0};
	int dc[4] = {0,0,1,-1};
	// build graph
	vector<vector<pair<int,int>>> graph(R);
	int maxWeight = 0;
	for (int i=0; i<R; i++) {
		for (int j=0; j<C; j++) {
			for (int k=0; k<4; k++) {
				int rr=i+dr[k], cc=j+dc[k];
				if (rr<0 or rr>=R or cc<0 or cc>=C) continue;
				int wt = abs(h[i][j]-h[rr][cc]);
				maxWeight = max(maxWeight, wt);
				graph[ind(i,j)].push_back({ind(i-1,j), wt});
			}
		}
	}

	for (int k=0; k<=maxWeight; k++) {
		// perform dfs and if we find h[R-1][C-1], return path sum

	}

}};
*/

