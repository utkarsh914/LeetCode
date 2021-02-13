// https://leetcode.com/problems/strange-printer-ii/
/*
Explanation
For each color, find its index of left most, top most, right most, bottom most point.
Then we need to paint this color from [top, left] to [bottom, right].

If in the rectangle, all the colors are either the same or 0,
we mark all of them to 0.

If we can mark the whole grid to 0, it means the target if printable.

Complexity
Time O(CCMN)
Space O(4C)
*/

class Solution {

	bool isSingleColor(vector<vector<int>>& g, array<int,4>& p, int color) {
		for (int i=p[0]; i<=p[2]; i++)
			for (int j=p[3]; j<=p[1]; j++)
				if (g[i][j]!=color && g[i][j]!=0)
					return false;
		return true;
	}

	void markZero(vector<vector<int>>& g, array<int,4>& p) {
		for (int i=p[0]; i<=p[2]; i++)
			for (int j=p[3]; j<=p[1]; j++)
				g[i][j] = 0;
	}

public:
	bool isPrintable(vector<vector<int>>& g) {
		// array<int, 4> :: top-row, right-col, bot-row, left-col
		vector<array<int,4>> points(61, {61, -1, -1, 61});
		unordered_set<int> colorSet;

		for (int i=0; i<g.size(); i++) {
			for (int j=0; j<g[i].size(); j++) {
				int color = g[i][j];
				colorSet.insert(color);
				auto& p = points[color];
				p[0] = min(p[0], i);
				p[1] = max(p[1], j);
				p[2] = max(p[2], i);
				p[3] = min(p[3], j);
			}
		}

		while (colorSet.size()) {
			unordered_set<int> tempColorSet;
			for (int c:colorSet) {
				if (isSingleColor(g, points[c], c))
					markZero(g, points[c]);
				else
					tempColorSet.insert(c);
			}
			if (colorSet.size() == tempColorSet.size())
				return false;
			colorSet = tempColorSet;
		}

		return true;
	}
};
