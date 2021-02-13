// https://leetcode.com/problems/largest-rectangle-in-histogram/

class Solution {
public:
	int largestRectangleArea(vector<int>& h);
};

int Solution::largestRectangleArea(vector<int>& h) {
	int s = h.size();
	if (s<1) return 0;
	int justSmallOnLeft[s], justSmallOnRight[s];
	justSmallOnLeft[0]=-1, justSmallOnRight[s-1]=s;
	// fill justSmallOnLeft
	for (int i=1; i<s; i++) {
		int p = i-1;
		while (p>=0 && h[p]>=h[i])
			p = justSmallOnLeft[p];
		justSmallOnLeft[i] = p;
	}
	// fill justSmallOnRight
	for (int i=s-2; i>=0; i--) {
		int p = i+1;
		while (p<s && h[p]>=h[i])
			p = justSmallOnRight[p];
		justSmallOnRight[i] = p;
	}
	// find largest area
	// for every bar, we find the max area that contains full height of current bar
	int ans = 0;
	for (int i=0; i<s; i++)
		ans = max(ans, h[i]*(justSmallOnRight[i] - justSmallOnLeft[i] - 1));
	return ans;
}





// ********** optmized (use only one stack) *******
class Solution {
public:
	int largestRectangleArea(vector<int>& h) {
		int size = h.size();
		int area = 0;
		stack<pair<int,int>> s; // pair<index,val>

		for (int i=0; i<=size; i++) {
			int val = (i==size) ? 0 : h[i];
			while (!s.empty() && val < s.top().second) {
				auto deal = s.top(); s.pop();
				int leftIndex = !s.empty() ? s.top().first : -1;
				int width = i - leftIndex - 1;
				int currArea = deal.second * width;
				area = max(area, currArea);
			}
			s.push({i, val});
		}

		return area;
	}
};



// ********** optmized (use only one stack) *******
class Solution {
public:
	int largestRectangleArea(vector<int>& h) {
		int area = 0;
		stack<int> s; // stores index

		h.push_back(0);
		for (int i=0; i<h.size(); i++) {
			while (!s.empty() && h[i] < h[s.top()]) {
				int dealIndex = s.top(); s.pop();
				int leftIndex = !s.empty() ? s.top() : -1;
				int width = i - leftIndex - 1;
				int currArea = h[dealIndex] * width;
				area = max(area, currArea);
			}
			s.push(i);
		}

		return area;
	}
};