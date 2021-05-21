// https://leetcode.com/problems/filter-restaurants-by-vegan-friendly-price-and-distance/

class Solution {
public:
	vector<int> filterRestaurants(vector<vector<int>>& R,
		int vegan, int maxPrice, int maxDistance) {
		sort(R.begin(), R.end(), [](auto& a, auto& b) {
			if (a[1] == b[1]) return a[0] > b[0];
			return a[1] > b[1];
		});

		vector<int> ans;
		for (auto& r : R) {
			if (vegan && r[2] == 0) continue;
			if (r[3] <= maxPrice and r[4] <= maxDistance)
				ans.push_back(r[0]);
		}
		return ans;
	}
};




class Solution {
public:
	vector<int> filterRestaurants(vector<vector<int>>& R,
		int vegan, int maxPrice, int maxDistance) {

		vector<vector<int>> cand;
		for (auto& r : R) {
			if (vegan && r[2] == 0) continue;
			if (r[3] <= maxPrice and r[4] <= maxDistance)
				cand.push_back(r);
		}

		sort(cand.begin(), cand.end(), [](auto& a, auto& b) {
			if (a[1] == b[1]) return a[0] > b[0];
			return a[1] > b[1];
		});

		vector<int> ans(cand.size());
		for (int i = 0; i < cand.size(); i++)
			ans[i] = cand[i][0];

		return ans;
	}
};



/*
javascript 1 liner

var filterRestaurants = function(R, vegan, maxPrice, maxDistance) {
	return R
	.filter(r => (!(vegan && r[2]===0) && r[3] <= maxPrice && r[4] <= maxDistance))
	.sort((a, b) => (a[1] !== b[1] ? b[1] - a[1] : b[0] - a[0]))
	.map(([id]) => id);
};

*/