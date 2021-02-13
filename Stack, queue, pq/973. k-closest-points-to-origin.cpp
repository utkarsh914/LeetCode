
class Solution {
public:
	vector<vector<int>> kClosest(vector<vector<int>>& points, int K) {
		priority_queue<array<int,3>> pq;
		for (auto& p: points) {
			pq.push({p[0]*p[0] + p[1]*p[1], p[0], p[1]});
			if (pq.size() > K) pq.pop();
		}
		vector<vector<int>> ans;
		while (!pq.empty()) ans.push_back({pq.top()[1], pq.top()[2]}), pq.pop();
		return ans;
	}
};