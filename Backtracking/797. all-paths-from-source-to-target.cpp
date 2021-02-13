class Solution {
public:
	int N;
	vector<vector<int>> graph;
	vector<vector<int>> result;
	vector<int> curr;
	vector<bool> visited;

	vector<vector<int>> allPathsSourceTarget(vector<vector<int>>& givenGraph) {
		N = givenGraph.size();
		visited = vector<bool> (N, false);
		graph = givenGraph;
		backtrack(0);
		return result;
	}

	void backtrack(int source) {
		if (curr.size()>0 and curr.back() == N-1)
			result.push_back(curr);
		for (auto i:graph[source]) {
			curr.push_back(i); visited[i]=true;
			backtrack(i);
			curr.pop_back(); visited[i]=false;
		}
	}
};