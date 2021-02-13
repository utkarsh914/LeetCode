// https://leetcode.com/problems/merge-intervals/

class Solution {
public:
	vector<vector<int>> merge(vector<vector<int>>& arr) {
		sort(arr.begin(), arr.end());
		for (int i=1; i<arr.size(); i++) {
			auto &curr = arr[i], &prev = arr[i-1]; // current, previous
			if (prev[1]>=curr[0]) {
				curr[0] = prev[0], curr[1] = max(curr[1], prev[1]);
				prev[0] = prev[1] = -1; // mark previous as invalid
			}
		}

		vector<vector<int>> result;
		for (auto& v:arr)
			if (v[0]!=-1) result.emplace_back(v);
		return result;
	}
};