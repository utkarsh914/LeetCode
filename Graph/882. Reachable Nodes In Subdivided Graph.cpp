// https://leetcode.com/problems/reachable-nodes-in-subdivided-graph/

class Solution {
public:
	int reachableNodes(vector<vector<int>>& edges, int maxMoves, int n) {
		// create adj list graph
		vector<vector<pair<int,int>>> g(n);
		for (auto& e : edges) {
			int u = e[0], v = e[1], w = e[2] + 1;
			g[u].push_back({ v, w });
			g[v].push_back({ u, w });
		}

		// run dijkstra first
		vector<int> dist(n, INT_MAX);
		typedef pair<int,int> pii;
		priority_queue<pii, vector<pii>, greater<pii>> pq;
		dist[0] = 0;
		pq.push({ 0, 0 });

		while (!pq.empty()) {
			auto [d, u] = pq.top(); pq.pop();
			// no need to have any dist > maxMoves, we can stop safely
			if (d > maxMoves) break;
			for (auto [v, w] : g[u]) {
				if (dist[u] + w < dist[v]) {
					dist[v] = dist[u] + w;
					pq.push({ dist[v], v });
				}
			}
		}

		// count actual nodes that can be visited
		int ans = 0;
		for (int v = 0; v < n; ++v) {
			if (dist[v] <= maxMoves) ans++;
		}

		// tricky part (count new middle nodes between each edge)
		for (auto& e : edges) {
			int u = e[0], v = e[1], newNodes = e[2];
			int from_front = dist[u] >= maxMoves ? 0
				: min(maxMoves - dist[u], newNodes);
			int from_back = dist[v] >= maxMoves ? 0
				: min(maxMoves - dist[v], newNodes);
			ans += min(from_front + from_back, newNodes);
		}

		return ans;
	}
};