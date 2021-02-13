// https://leetcode.com/problems/minimum-number-of-arrows-to-burst-balloons/

/*
There are some spherical balloons spread in two-dimensional space. For each balloon,
provided input is the start and end coordinates of the horizontal diameter. Since it's horizontal,
y-coordinates don't matter, and hence the x-coordinates of start and end of the diameter suffice.
The start is always smaller than the end.

An arrow can be shot up exactly vertically from different points along the x-axis.
A balloon with xstart and xend bursts by an arrow shot at x if xstart ≤ x ≤ xend.
There is no limit to the number of arrows that can be shot. An arrow once shot keeps traveling up infinitely.

Given an array points where points[i] = [xstart, xend],
return the minimum number of arrows that must be shot to burst all balloons.

 

Example 1:

Input: points = [[10,16],[2,8],[1,6],[7,12]]
Output: 2
Explanation: One way is to shoot one arrow for example at x = 6 (bursting the balloons [2,8] and [1,6]) and another arrow at x = 11 (bursting the other two balloons).
*/

// same as: 1024. video stitching
class Solution {
public:
	int findMinArrowShots(vector<vector<int>>& points) {
		sort(points.begin(), points.end(), greater<vector<int>>());
		int arrow = 0, size = points.size();
		for (int s=0, e=0; s<size; arrow++) {
			while (e<size && points[e][1]>=points[s][0]) e++;
			s = e;
		}
		return arrow;
	}
};