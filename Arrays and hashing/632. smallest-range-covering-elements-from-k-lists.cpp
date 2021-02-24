// https://leetcode.com/problems/smallest-range-covering-elements-from-k-lists/

// similar to: 23.merge-k-sorted-lists

/*
You have k lists of sorted integers in non-decreasing order. Find the smallest range that includes at least one number from each of the k lists.

We define the range [a, b] is smaller than range [c, d] if b - a < d - c or a < c if b - a == d - c.

 

Example 1:

Input: nums = [[4,10,15,24,26],[0,9,12,20],[5,18,22,30]]
Output: [20,24]
Explanation: 
List 1: [4, 10, 15, 24,26], 24 is in range [20,24].
List 2: [0, 9, 12, 20], 20 is in range [20,24].
List 3: [5, 18, 22, 30], 22 is in range [20,24].
*/

// can use priority queue too
class Solution {
public:
	vector<int> smallestRange(vector<vector<int>>& nums) {
		multiset<array<int,3>> s;
		// insert first elements
		for (int i=0; i < nums.size(); i++)
			s.insert({ nums[i][0], i, 0 });

		int mn = (*s.begin())[0], mx = (*s.rbegin())[0];
		vector<int> ans = { mn, mx };

		while (true) {
			auto cur = *s.begin(); s.erase(s.begin());
			int n = cur[0], i = cur[1], j = cur[2];
			if (j == nums[i].size()-1)
				break;

			s.insert({ nums[i][j+1], i, j+1 });
			mn = (*s.begin())[0], mx = (*s.rbegin())[0];
			if (mx - mn < ans[1]-ans[0]) {
				ans = { mn, mx };
			}
		}

		return ans;
	}
};







class Solution {
public:
	vector<int> smallestRange(vector<vector<int>>& nums) {
		typedef vector<int>::iterator vi;
		auto comp = [](auto& p1, auto& p2) {
			return *(p1.first) < *(p2.first);
		};

		multiset<pair<vi, vi>, decltype(comp)> s(comp);
		// insert first elements
		for (int i=0; i < nums.size(); i++)
			s.insert({ nums[i].begin(), nums[i].end() });

		int mn = *((*s.begin()).first), mx = *((*s.rbegin()).first);
		vector<int> ans = { mn, mx };

		while (true) {
			auto cur = *s.begin(); s.erase(s.begin());
			if (++cur.first == cur.second)
				break;

			s.insert(cur);
			mn = *((*s.begin()).first), mx = *((*s.rbegin()).first);
			if (mx - mn < ans[1]-ans[0]) {
				ans = { mn, mx };
			}
		}

		return ans;
	}
};