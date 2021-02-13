// https://leetcode.com/problems/minimum-number-of-taps-to-open-to-water-a-garden/

// similar to: 1024. Video Stitching

/*
Create intervals of the area covered by each tap, sort intervals by the left end.
After that is is exactly same as 1024. Video Stitching

We need to cover the interval [0, n]. we can start with the first interval and out of all intervals
that intersect with it we choose the one that covers the farthest point to the right.
*/
class Solution {
public:
	int minTaps(int n, vector<int>& ranges) {

		vector<array<int,2>> intervals(n+1, {0,0});
		for (int i=0; i < n+1; i++) {
			int r = ranges[i];
			intervals[i] = { max(0, i-r), min(n, i+r) };
		}
		sort(intervals.begin(), intervals.end());
		// same as video stitching
		int taps = 0;
		for (int i=0, start=0, end=0; start < n; start=end, taps++) {
			for (; i<n+1 && intervals[i][0] <= start; i++)
				end = max(end, intervals[i][1]);
			if (start ==  end) return -1;
		}
		return taps;
	}
};
/*
Intuition
We track our current stitching position (st). For each iteration, we check all overlapping clips,
and pick the one that advances our stitching position the furthest.

Solution
We sort our clips by the starting point. Since clips are sorted, we need to only analyze each clip once.
For each round, we check all overlapping clips (clips[i][0] <= st) and advance our stitching position
as far as we can (end = max(end, clips[i][1])).
*/






// ********** DP ***********

class Solution {
public:
	int minTaps(int n, vector<int>& r) {
		
		// dp[i] is the min number of taps to water area from 0 to i
		vector<int> dp(n+1, n+2); // Initialize with max
		dp[0] = 0; // minimum taps needed to water area 0 is 0(basically no area)

		for(int i=0;i<=n;i++) {

			int left  = max(0, i - r[i]); // find the minimum point of garden(area) to water with tape i.
			int right = min(n, i + r[i]); // find the maximum point of garden(area) to water with tape i.

			for(int j=left+1; j <= right; j++) {
				//Check if this range from(left..right) can be watered using less number of taps than previous
				dp[j] = min(dp[j], 1 + dp[left]);
			}
		}
		
		// If mimimum taps needed to water area 0..n is greater than n , it means we could not found minimum number of taps
		return (dp[n] >= n+2) ? -1 : dp[n];
	}
};