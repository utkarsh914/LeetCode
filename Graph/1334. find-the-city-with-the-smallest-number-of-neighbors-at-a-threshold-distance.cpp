/*
https://leetcode.com/problems/find-the-city-with-the-smallest-number-of-neighbors-at-a-threshold-distance/

There are n cities numbered from 0 to n-1. Given the array edges where edges[i] = [fromi, toi, weighti] represents a bidirectional and weighted edge between cities fromi and toi, and given the integer distanceThreshold.
Return the city with the smallest number of cities that are reachable through some path and whose distance is at most distanceThreshold, If there are multiple such cities, return the city with the greatest number.
Notice that the distance of a path connecting cities i and j is equal to the sum of the edges' weights along that path.

Example 1:
Input: n = 4, edges = [[0,1,3],[1,2,1],[1,3,4],[2,3,1]], distanceThreshold = 4
Output: 3
Explanation: The figure above describes the graph. 
The neighboring cities at a distanceThreshold = 4 for each city are:
City 0 -> [City 1, City 2] 
City 1 -> [City 0, City 2, City 3] 
City 2 -> [City 0, City 1, City 3] 
City 3 -> [City 1, City 2] 
Cities 0 and 3 have 2 neighboring cities at a distanceThreshold = 4, but we have to return city 3 since it has the greatest number.

Example 2:
Input: n = 5, edges = [[0,1,2],[0,4,8],[1,2,3],[1,4,2],[2,3,1],[3,4,1]], distanceThreshold = 2
Output: 0
Explanation: The figure above describes the graph. 
The neighboring cities at a distanceThreshold = 2 for each city are:
City 0 -> [City 1] 
City 1 -> [City 0, City 4] 
City 2 -> [City 3, City 4] 
City 3 -> [City 2, City 4]
City 4 -> [City 1, City 2, City 3] 
The city 0 has 1 neighboring city at a distanceThreshold = 2.
*/

// ************ USING FLOYD WARSHALL ALGO (directly) ***********
class Solution {
public:

int findTheCity(int n, vector<vector<int>>& edges, int threshold) {
	vector<vector<int>> dp(n, vector<int>(n,10000));
	for (int i=0; i<n; i++) dp[i][i]=0;
	for (int i=0; i<edges.size(); i++) {
		int u=edges[i][0], v=edges[i][1], wt=edges[i][2];
		dp[u][v] = dp[v][u] = wt;
	}

	for (int k=0; k<n; k++)
		for (int i=0; i<n; i++)
			for (int j=0; j<n; j++)
				dp[i][j] = min(dp[i][j], dp[i][k]+dp[k][j]);

	pair<int,int> ans = {INT_MAX, INT_MAX}; // {node, count}
	for (int i=0; i<n; i++) {
		int count = 0;
		for (auto j:dp[i]) count += (j!=0 and j<=threshold);
		if (count < ans.second) ans = {i,count};
		else if (count==ans.second && i>ans.first) ans={i,count};
	}
	return ans.first;
}};








// ************ USING FLOYD WARSHALL ALGO (as separate function) ***********
class Solution {
public:

vector<vector<int>> floydWarshall(vector<pair<int,int>> graph[], int n) {
	// initialize dp same as graph weights
	vector<vector<int>> dp(n, vector<int>(n, 10000));
	for (int i=0; i<n; i++) dp[i][i]=0;
	for (int i=0; i<n; i++) {
		for (auto e:graph[i]) {
			int u=i, v=e.first, wt=e.second;
			dp[u][v] = wt;
		}
	}

	for (int k=0; k<n; k++)
		for (int i=0; i<n; i++)
			for (int j=0; j<n; j++)
				dp[i][j] = min(dp[i][j], dp[i][k]+dp[k][j]);

	return dp;
}

int findTheCity(int n, vector<vector<int>>& edges, int threshold) {
	// build graph
	vector<pair<int,int>> graph[n];
	for (auto e:edges) {
		int u=e[0], v=e[1], wt=e[2];
		graph[u].push_back({v,wt});
		graph[v].push_back({u,wt});
	}

	vector<vector<int>> distances = floydWarshall(graph, n);

	pair<int,int> ans = {INT_MAX, INT_MAX}; // {node, count}
	for (int i=0; i<n; i++) {
		int count = 0;
		for (auto j:distances[i]) count += (j!=0 and j<=threshold);
		if (count < ans.second) ans = {i,count};
		else if (count==ans.second && i>ans.first) ans={i,count};
	}
	return ans.first;
}};








// *********** USING DIJKSTRA/BELLMAN FORD *******
class Solution {
public:
// ********** IDEA ***********
// find min dist of all nodes from source,
// and return the no. of nodes having min dist <= threshold
int bellmanFord(vector<pair<int,int>> graph[], int n, int source, int threshold) {
	vector<int> dist(n, INT_MAX);
	dist[source]=0;
	// to update min distance {a path can have at most n-1 edges}
	for (int pathLenght=1; pathLenght<=n-1; pathLenght++) {
		for (int i=0; i<n; i++) {
			for (auto e:graph[i]) {
				int u=i, v=e.first, wt=e.second;
				if (dist[u]!=INT_MAX and dist[u]+wt<dist[v])
					dist[v] = dist[u]+wt;
			}
		}
	}
	// count the number of nodes having min dist <= threshold
	int count=0;
	for (auto i:dist) count += (i<=threshold);
	return count;
}

int findTheCity(int n, vector<vector<int>>& edges, int threshold) {
	// build graph
	vector<pair<int,int>> graph[n];
	for (auto e:edges) {
		int u=e[0], v=e[1], wt=e[2];
		graph[u].push_back({v,wt});
		graph[v].push_back({u,wt});
	}

	pair<int,int> ans = {INT_MAX, INT_MAX}; // {node, count}
	for (int i=0; i<n; i++) {
		int count = bellmanFord(graph, n, i, threshold);
		if (count < ans.second) ans = {i,count};
		else if (count==ans.second && i>ans.first) ans={i,count};
	}
	return ans.first;
}};







static auto _______ = [](){
	std::ios::sync_with_stdio(false);
	std::cin.tie(NULL);
	std::cout.tie(NULL);
	return 0;
}();
