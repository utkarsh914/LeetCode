// https://leetcode.com/problems/cheapest-flights-within-k-stops/

/*
There are n cities connected by some number of flights.
You are given an array flights where flights[i] = [fromi, toi, pricei]
indicates that there is a flight from city fromi to city toi with cost pricei.

You are also given three integers src, dst, and k,
return the cheapest price from src to dst with at most k stops.
If there is no such route, return -1.

 

Example 1:


Input: n = 3, flights = [[0,1,100],[1,2,100],[0,2,500]], src = 0, dst = 2, k = 1
Output: 200
Explanation: The graph is shown.
The cheapest price from city 0 to city 2 with at most 1 stop costs 200,
as marked red in the picture.
Example 2:


Input: n = 3, flights = [[0,1,100],[1,2,100],[0,2,500]], src = 0, dst = 2, k = 0
Output: 500
Explanation: The graph is shown.
The cheapest price from city 0 to city 2 with at most 0 stop costs 500,
as marked blue in the picture.
 

Constraints:

1 <= n <= 100
0 <= flights.length <= (n * (n - 1) / 2)
flights[i].length == 3
0 <= fromi, toi < n
fromi != toi
1 <= pricei <= 104
There will not be any multiple flights between two cities.
0 <= src, dst, k < n
src != dst
*/





class Solution {
	int inf = INT_MAX / 10;
	vector<vector<int>> dp;
	vector<vector<pair<int,int> > > g;
public:
	int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int k) {
		g.resize(n);
		dp.resize(n, vector<int> (n, -1));
		for (auto& f : flights)
			g[f[0]].push_back({ f[1], f[2] });

		int ans = getCheapest(src, dst, k);
		return ans < inf ? ans : -1;
	}

	int getCheapest(int src, int dst, int stops) {
		if (src == dst) return 0;
		if (stops < 0) return inf;
		if (dp[src][stops] != -1) return dp[src][stops];

		int ans = INT_MAX;
		for (auto& [v, price] : g[src]) {
			ans = min(ans, price + getCheapest(v, dst, stops-1));
		}
		if (ans > inf) ans = inf;
		return dp[src][stops] = ans;
	}
};








/*
----- bottom up DP (basis of BELLMAN FORD, but BF is a bit different) ------
if max allowed stops is k, it means max path length can be k+1

dp[i][j] = cost to reach i with at most the path length of j
*/
class Solution {
public:
	int findCheapestPrice(int n, vector<vector<int>>& flights,
			int src, int dst, int k) {
		vector<vector<int>> dp(n+1, vector<int> (k+2, INT_MAX));
		// base condition
		for (int length = 0; length <= k + 1; length++)
			dp[src][length] = 0;

		for (int length = 1; length <= k + 1; length++) {
			for (auto& f : flights) {
				int u = f[0], v = f[1], cost = f[2];
				if (dp[u][length-1] != INT_MAX)
					dp[v][length] = min(dp[v][length], dp[u][length-1] + cost);
			}
		}

		return dp[dst][k+1] == INT_MAX ? -1 : dp[dst][k+1];
	}
};





/*
----- bottom up DP (OPTIMIZED SPACE) ------
if max allowed stops is k, it means max path length can be k+1

dp[k][v] = cost to reach v with at most the path length of k

it is optimized space DP.
so we'll just store the previous state and current state
*/
class Solution {
public:
	int findCheapestPrice(int n, vector<vector<int>>& flights,
			int src, int dst, int k) {
		vector<vector<int>> dp(2, vector<int> (n+1, INT_MAX));
		// base condition
		dp[0][src] = dp[1][src] = 0;

		for (int length = 1; length <= k + 1; length++) {
			for (auto& f : flights) {
				int u = f[0], v = f[1], cost = f[2];
				int cur = length % 2, prev = !cur;
				if (dp[prev][u] != INT_MAX)
					dp[cur][v] = min(dp[cur][v], dp[prev][u] + cost);
			}
		}

		return dp[(k+1)%2][dst] == INT_MAX ? -1 : dp[(k+1)%2][dst];
	}
};





/*
-------- using modified BELLMAN FORD (same as optimized DP above) ------------
*/
class Solution {
public:
	int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int k) {
		vector<int> dist(n, INT_MAX);
		dist[src] = 0;

		for (int stops = 0; stops <= k; stops++) {
			vector<int> temp = dist;
			for (auto& f : flights) {
				int u = f[0], v = f[1], cost = f[2];
				if (dist[u] != INT_MAX)
					temp[v] = min(temp[v], dist[u] + cost);
			}
			dist = temp;
		}

		return dist[dst] == INT_MAX ? -1 : dist[dst];
	}
};

/*
 basically the Bellman Ford algorithm,
 keeps on updating the distance array while relaxing the edges
 ( i.e it relax the next edge (u,v) based on updated distance(u) )...
 so it hides the track of number of edges visited in between...
 while here we hold the updated distance till we traverse all the edges
 ..and then update the distance for the next iteration...

 so in case when k==n-1 this algo will produce the output just like Bellman ford.
*/












/*
can't use Dijkstra here directly
need to modify it


The key difference with the classic Dijkstra algo is, we don't maintain the global optimal distance to each node, i.e. ignore below optimization:
alt ← dist[u] + length(u, v)
if alt < dist[v]:
Because there could be routes which their length is shorter but pass more stops, and those routes don't necessarily constitute the best route in the end. To deal with this, rather than maintain the optimal routes with 0..K stops for each node, the solution simply put all possible routes into the priority queue, so that all of them has a chance to be processed. IMO, this is the most brilliant part.
And the solution simply returns the first qualified route, it's easy to prove this must be the best route.

// above will give TLE. Need an optimization here as well.
use an array to track the number of stops it took to reach a node,
and then only visit the node again if the current path took
fewer moves to reach the node than any previous path.
*/

// gives TLE
typedef tuple<int,int,int> ti;
class Solution {
public:
	int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int K) {
		// build graph
		vector<vector<pair<int,int> > > G(n);
		for (auto& f : flights)
			G[f[0]].emplace_back(f[1], f[2]);

		vector<int> stops_visited(n, -1);
		priority_queue< ti, vector<ti>, greater<ti>> pq;
		pq.emplace(0, src, K+1);

		while (!pq.empty()) {
			auto [ cost, u, stops] = pq.top(); pq.pop();
			if (u == dst) return cost;
			if (stops_visited[u] > stops) continue;
			stops_visited[u] = stops;
			if (stops == 0) continue;
			for (auto [v, w] : G[u]) {
				pq.emplace(cost + w, v, stops - 1);
			}
		}

		return -1;
	}
};






/*


======= WRONG =======
fails in below test case

4
[[0,1,1],[0,2,5],[1,2,1],[2,3,1]]
0
3
1


class Solution {
public:
	int findCheapestPrice(int n, vector<vector<int>>& flights,
			int src, int dst, int k) {

		vector<vector<pair<int,int> > > g(n);
		for (auto& f : flights) {
			g[f[0]].push_back({ f[1], f[2] });
		}

		vector<int> dist(n, INT_MAX);
		priority_queue<array<int,3>, vector<array<int,3>>,
			greater<array<int,3>> > pq;
		pq.push({ 0, -1, src }); // <dist, stops, node>

		while (!pq.empty()) {
			auto cur = pq.top(); pq.pop();
			int d = cur[0], stops = cur[1], u = cur[2];
			if (d < dist[u] and stops <= k) {
				dist[u] = d;
				if (stops == k) continue;
				for (auto& [v, wt] : g[u])
					pq.push({ d + wt, stops + 1, v });
			}
		}

		return dist[dst] == INT_MAX ? -1 : dist[dst];
	}
};
*/