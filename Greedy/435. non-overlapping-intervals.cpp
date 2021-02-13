// https://leetcode.com/problems/non-overlapping-intervals/

/*
Given a collection of intervals, find the minimum number of intervals
you need to remove to make the rest of the intervals non-overlapping.

Example 1:

Input: [[1,2],[2,3],[3,4],[1,3]]
Output: 1
Explanation: [1,3] can be removed and the rest of intervals are non-overlapping.
Example 2:

Input: [[1,2],[1,2],[1,2]]
Output: 2
Explanation: You need to remove two [1,2] to make the rest of intervals non-overlapping.
*/




/*
A classic greedy case: interval scheduling problem.

The heuristic is: always pick the interval with the earliest end time.
Then you can get the maximal number of non-overlapping intervals. (or minimal number to remove).
This is because, the interval with the earliest end time produces the maximal capacity to hold rest intervals.
E.g. Suppose current earliest end time of the rest intervals is x.
Then available time slot left for other intervals is [x:]. If we choose another interval with end time y,
then available time slot would be [y:]. Since x ≤ y, there is no way [y:] can hold more intervals then [x:].
Thus, the heuristic holds.

Therefore, we can sort interval by ending time and key track of current earliest end time.
Once next interval's start time is earlier than current end time, then we have to remove one interval.
Otherwise, we update earliest end time.



 ***** pochman's explanation ******
Which interval would be the best first (leftmost) interval to keep?
One that ends first, as it leaves the most room for the rest. So take one with smallest end,
remove all the bad ones overlapping it, and repeat (taking the one with smallest end of the remaining ones).
For the overlap test, just keep track of the current end, initialized with negative infinity.
*/

class Solution {
public:
	int eraseOverlapIntervals(vector<vector<int>>& intervals) {
		// sort by end time
		sort(intervals.begin(), intervals.end(), [](auto& i1, auto& i2) {
			return i1[1] < i2[1];
		});

		int end = INT_MIN, count = 0;
		for (auto& interval: intervals) {
			if (interval[0] >= end) end = interval[1];
			else count++;
		}
		
		return count;
	}
};

/*
can also be done by sorting wrt start time in decreasing order
*/
class Solution {
public:
	int eraseOverlapIntervals(vector<vector<int>>& intervals) {
		// sort by start time in dec order (latest starting interval first)
		sort(intervals.begin(), intervals.end(), greater<vector<int>>());
		int start = INT_MAX, count = 0;
		for (auto& interval: intervals) {
			if (interval[1] <= start) start = interval[0];
			else count++;
		}
		
		return count;
	}
};






// *********** DP (MEMORIZATION) **********
class Solution {
	vector<int> dp;
public:
	int eraseOverlapIntervals(vector<vector<int>>& intervals) {
		sort(intervals.begin(), intervals.end());
		dp.resize(intervals.size(), -1);
		return intervals.size() - collect(intervals, 0);
	}
	
	// length of max arr having non-overlapping intervals
	int collect(vector<vector<int>>& arr, int start) {
		if (start >= arr.size()) return 0;
		if (dp[start] != -1) return dp[start];
		// find next non-overlapping interval
		int i = start+1;
		while (i<arr.size() && arr[i][0]<arr[start][1]) i++;
		int take = 1 + collect(arr, i);
		int notTake = collect(arr, start+1);

		return dp[start] = max(take, notTake);
	}
};