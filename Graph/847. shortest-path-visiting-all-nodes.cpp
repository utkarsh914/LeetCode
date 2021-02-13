
class Solution {
public:
int shortestPathLength(vector<vector<int>>& graph) {
	int N = graph.size();
	queue<vector<int>> q;
	unordered_set<string> st;
	int totalMask = (1<<N)-1;
	// add all paths to queue
	for (int i=0; i<N; i++) {
		int bitMask = (1<<i);
		q.push({bitMask, i, 0}); // {bitMask, currNode, pathCost}
		st.insert(to_string(bitMask) + ":" + to_string(i));
	}

	// run bfs now
	while (!q.empty()) {
		vector<int> curr = q.front(); q.pop();
		int bitMask=curr[0], currNode=curr[1], pathCost=curr[2];
		if (bitMask == totalMask) // if all bits set (all nodes visited)
			return pathCost;
		for (auto v:graph[currNode]) {
			int newBitMask = bitMask | (1<<v);
			string temp = to_string(newBitMask) + ":" + to_string(v);
			if (st.count(temp)) continue;
			st.insert(temp);
			q.push({newBitMask, v, pathCost+1});
		}
	}

	return -1;
}};