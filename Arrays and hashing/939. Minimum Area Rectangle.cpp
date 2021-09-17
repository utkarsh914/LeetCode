// https://leetcode.com/problems/minimum-area-rectangle/submissions/

/*
You are given an array of points in the X-Y plane points where points[i] = [xi, yi].

Return the minimum area of a rectangle formed from these points,
with sides parallel to the X and Y axes. If there is not any such rectangle, return 0.

Example 1:
Input: points = [[1,1],[1,3],[3,1],[3,3],[2,2]]
Output: 4

Example 2:
Input: points = [[1,1],[1,3],[3,1],[3,3],[4,1],[4,3]]
Output: 2
 

Constraints:

1 <= points.length <= 500
points[i].length == 2
0 <= xi, yi <= 4 * 104
All the given points are unique.
*/







class Solution {
public:
	int minAreaRect(vector<vector<int>>& points) {

		unordered_map<int, vector<int>> map;
		for (auto& p : points) map[p[1]].push_back(p[0]);
		
		if (map.size() < 2) return 0;
		
		vector<pair<int, vector<int>>> v(map.begin(), map.end());
		for (auto& [k, vec] : v) sort(vec.begin(), vec.end());
		
		int ans = INT_MAX;
		
		// try all prev-next combinations
		for (int prev_it = 0; prev_it < v.size(); prev_it++) {
			for (int cur_it = prev_it+1; cur_it < v.size(); cur_it++) {

				int height = abs(v[cur_it].first - v[prev_it].first);
				auto& A = v[cur_it].second, &B = v[prev_it].second;
				int i = 0, j = 0, prevX, curX;
				// find first valid pos
				advance(A, B, i, j);
				if (!isValidPos(A, B, i, j)) continue;
				prevX = A[i];
				
				while (true) {
					// find second valid pos
					i++, j++;
					advance(A, B, i, j);
					if (!isValidPos(A, B, i, j)) break;
					curX = A[i];
					int width = curX - prevX;
					ans = min(ans, height * width);
					prevX = curX;
				}

			}
		}
		
		return ans < INT_MAX ? ans : 0;
	}
	
	inline void advance(vector<int>& A, vector<int>& B, int& i, int& j) {
		while (i < A.size() and j < B.size() and A[i] != B[j]) {
			if (A[i] < B[j]) i++;
			else j++;
		}
	}
	
	inline bool isValidPos(vector<int>& A, vector<int>& B, int& i, int& j) {
		return i < A.size() and j < B.size() and A[i] == B[j];
	}
};






	def minAreaRect(self, points):
		seen = set()
		res = float('inf')
		for x1, y1 in points:
			for x2, y2 in seen:
				if (x1, y2) in seen and (x2, y1) in seen:
					area = abs(x1 - x2) * abs(y1 - y2)
					if area and area < res:
						res = area
			seen.add((x1, y1))
		return res if res < float('inf') else 0