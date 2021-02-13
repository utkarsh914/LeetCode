// https://leetcode.com/problems/video-stitching/

/* ******* greedy ******

Intuition
We track our current stitching position (st). For each iteration, we check all overlapping clips,
and pick the one that advances our stitching position the furthest.

Solution
We sort our clips by the starting point. Since clips are sorted, we need to only analyze each clip once.
For each round, we check all overlapping clips (clips[i][0] <= st) and advance our stitching position
as far as we can (end = max(end, clips[i][1])).

Return -1 if we cannot advance our stitching position (st == end).
*/
class Solution {
public:
	int videoStitching(vector<vector<int>>& clips, int T) {
		sort(clips.begin(), clips.end());
		int pick = 0;
		for (int i=0, start=0, end=0; start<T; start=end, pick++) {
			while (i<clips.size() && clips[i][0]<=start)
				end = max(end, clips[i++][1]);
			if (start == end) return -1; // couldn't find next pair
		}
		return pick;
	}
};



/* ******** sort + dp solution ********
Sort clips first.
Then for each clip, update dp[clip[0]] ~ dp[clip[1]].

Time O(NlogN + NT), Space O(T)
*/
class Solution {
public:
	int videoStitching(vector<vector<int>>& clips, int T) {
		sort(clips.begin(), clips.end());
		vector<int> dp(101, 101);
		dp[0] = 0;
		for (auto& c:clips) {
			for (int i=c[0]+1; i<=c[1]; i++)
				dp[i] = min(dp[i], 1+dp[c[0]]);
		}
		return dp[T]==101 ? -1 : dp[T];
	}
};




/* ******** pure dp solution ********

Loop on i form 0 to T,
loop on all clips,
If clip[0] <= i <= clip[1], we update dp[i]

Time O(NT), Space O(T)
*/

class Solution {
public:
	int videoStitching(vector<vector<int>>& clips, int T) {
		sort(clips.begin(), clips.end());
		vector<int> dp(T+1, T+1);
		dp[0] = 0;
		for (int i=1; i<=T && dp[i-1]<T; i++) {
			for (auto& c:clips) {
				if (i>=c[0] && i<=c[1])
					dp[i] = min(dp[i], 1+dp[c[0]]);
			}
		}
		return dp[T]==T+1 ? -1 : dp[T];
	}
};