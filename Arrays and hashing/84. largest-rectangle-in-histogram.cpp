/*
https://leetcode.com/problems/largest-rectangle-in-histogram/

Given n non-negative integers representing the histogram's bar height where the width of each bar is 1,
find the area of largest rectangle in the histogram.


========= SOLUTION ========

For any bar i the maximum rectangle is of width r - l - 1
where r - is the last coordinate of the bar to the right with height h[r] >= h[i]
and l - is the last coordinate of the bar to the left which height h[l] >= h[i]

The meaning of r and l is somewhat confusing, to put them more accurately:
l: the first coordinate of the bar to the left with height h[l] < h[i].
r: the first coordinate of the bar to the right with height h[r] < h[i].

IMAGE: https://i.loli.net/2018/10/29/5bd65b33c2798.png
*/


class Solution {
public:
    int largestRectangleArea(vector<int>& h);
};

int Solution::largestRectangleArea(vector<int>& h) {
    int s = h.size();
    if (s==0) return 0;
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
    int ans = INT_MIN;
    for (int i=0; i<s; i++)
        ans = max(ans, h[i]*(justSmallOnRight[i] - justSmallOnLeft[i] - 1));
    return ans;
}