
class Solution {
public:
int maximalNetworkRank(int n, vector<vector<int>>& roads) {
	vector<vector<bool>> connected(n, vector<bool>(n, false));
	vector<int> degree(n, 0);
	for (auto& r:roads) {
		int u=r[0], v=r[1];
		connected[u][v] = connected[v][u] = true;
		degree[u]++, degree[v]++;
	}
	int ans = 0;
	for (int u=0; u<n; u++) {
		for (int v=u+1; v<n; v++) {
			ans = max(ans, degree[u]+degree[v]-connected[u][v]);
		}
	}
	return ans;
}};