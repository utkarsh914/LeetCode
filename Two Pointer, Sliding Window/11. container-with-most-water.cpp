// https://leetcode.com/problems/container-with-most-water/

/*
for every element in height array, we find the largest container we can make,
that has height equal to current element. So, we need to find left max, and right max for this ele
and area will be diff bw left-max/right-mx indices * height of current element;

we can store left and right max for every element, and then do the calculation,
but we can also do it in one pass using 2 pointers

similar to largest rectangle in a histogram
keep track of left max, and right max value;

if left ele is smaller than or equal to right val,
it is right time to update the value corresponding to left.
Bcz at this time there will be max diff bw left and right ptr,
so we get the widest container with h = height[i], and width = (j-i);

similarly, for other case, it would be right time to update for height[j];
*/

class Solution {
public:
	int maxArea(vector<int>& h) {
		int i = 0, j = h.size()-1, maxArea = 0;
		int lMax = 0, rMax = 0;
		while (i < j) {
			lMax = max(lMax, h[i]);
			rMax = max(rMax, h[j]);
			if (h[i] <= h[j]) {
				int curArea = h[i] * (j-i);
				maxArea = max(maxArea, curArea);
				i++;
			} else {
				int curArea = h[j] * (j-i);
				maxArea = max(maxArea, curArea);
				j--;
			}
		}
		return maxArea;
	}
};