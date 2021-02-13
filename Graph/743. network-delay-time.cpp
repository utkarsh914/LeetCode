/*
https://leetcode.com/problems/network-delay-time/

There are N network nodes, labelled 1 to N.
Given times, a list of travel times as directed edges times[i] = (u, v, w), where u is the source node,
v is the target node, and w is the time it takes for a signal to travel from source to target.
Now, we send a signal from a certain node K. How long will it take for all nodes to receive the signal?
If it is impossible, return -1.

Example 1:
Input: times = [[2,1,1],[2,3,1],[3,4,1]], N = 4, K = 2
Output: 2
 
Note:
N will be in the range [1, 100].
K will be in the range [1, N].
The length of times will be in the range [1, 6000].
All edges times[i] = (u, v, w) will have 1 <= u, v <= N and 0 <= w <= 100.
*/

class Solution {
public:

	vector<pair<int,int>> *graph;

	int networkDelayTime(vector<vector<int>>& times, int N, int source) {
		// build graph
		// since given graph is 1 index based, so convert it to
		// zero index based (reason for source-1)
		graph = new vector<pair<int,int>>[N];
		for (auto i: times) {
			int u = i[0]-1, v = i[1]-1, weight = i[2];
			graph[u].push_back({v, weight});
		}
		// return bellmanFord(N, source-1);
		return dijkstra(N, source-1);
	}
	
	// ********** SLOWER ***********
	int bellmanFord(int N, int source) {
		vector<int> dist(N, INT_MAX); // min dist array
		dist[source]=0;
		// to update min distance {a path can have at most N-1 edges}
		for (int pathLenght=1; pathLenght<=N-1; pathLenght++) {
			for (int i=0; i<N; i++) { // explore all edges
				vector<pair<int,int>>& curr = graph[i];
				for (auto j:curr) {
					int u=i, v=j.first, weight=j.second;
					if (dist[u]!=INT_MAX and dist[u]+weight < dist[v])
						dist[v] = dist[u]+weight;
				}
			}
		}
		int ans = -1;
		for (auto i:dist) ans = max(ans, i);
		return (ans==INT_MAX) ? -1 : ans;
	}

	// ********** FASTER ***********
	int dijkstra(int N, int source) {
		vector<bool> finalized(N, false); // whether min dist is finalized for ith node
		vector<int> minDistArray(N, INT_MAX); // min dist array
		minDistArray[source] = 0; // dist to source is 0
		for (int count=0; count<N-1; count++) {
			// pick min dist vertex that isn't yet finalized
			int u = minDistance(finalized, minDistArray);
			finalized[u] = true; // mark finalized
			for (auto i:graph[u]) {
				int v = i.first, weight = i.second;
				if (!finalized[v]) // if not finalized, update min distance
					minDistArray[v] = min(minDistArray[v], minDistArray[u]+weight);
			}
		}
		int ans = -1;
		for (auto i:minDistArray) ans = max(ans, i);		
		return (ans==INT_MAX) ? -1 : ans;
	}

	int minDistance(vector<bool>& finalized, vector<int>& minDistArray) {
		int index, minDist = INT_MAX;
		for (int i=0; i<finalized.size(); i++) {
			if (!(finalized[i]) and minDistArray[i]<minDist)
				minDist=minDistArray[i], index=i;
		}
		return index;
	}
};