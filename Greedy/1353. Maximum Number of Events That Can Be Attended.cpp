// https://leetcode.com/problems/maximum-number-of-events-that-can-be-attended/

/*
Given an array of events where events[i] = [startDayi, endDayi].
Every event i starts at startDayi and ends at endDayi.

You can attend an event i at any day d where startTimei <= d <= endTimei.
Notice that you can only attend one event at any time d.

Return the maximum number of events you can attend.


Example 1:


Input: events = [[1,2],[2,3],[3,4]]
Output: 3
Explanation: You can attend all the three events.
One way to attend them all is as shown.
Attend the first event on day 1.
Attend the second event on day 2.
Attend the third event on day 3.
Example 2:

Input: events= [[1,2],[2,3],[3,4],[1,2]]
Output: 4
Example 3:

Input: events = [[1,4],[4,4],[2,2],[3,4],[1,1]]
Output: 4
Example 4:

Input: events = [[1,100000]]
Output: 1
Example 5:

Input: events = [[1,1],[1,2],[1,3],[1,4],[1,5],[1,6],[1,7]]
Output: 7
 

Constraints:

1 <= events.length <= 105
events[i].length == 2
1 <= startDayi <= endDayi <= 105
*/







/*
Sort events increased by start time.
Priority queue pq keeps the current open events.

Iterate from the day 1 to day 100000,
Each day, we add new events starting on day d to the queue pq.
Also we remove the events that are already closed.

Then we greedily attend the event that ends soonest.
If we can attend a meeting, we increment the result res.


Complexity
Time O(d + nlogn), where D is the range of A[i][1]
Space O(N)

*/
class Solution {
public:
	int maxEvents(vector<vector<int>>& events) {
		// sort by starting time
		sort(events.begin(), events.end());
		priority_queue<int, vector<int>, greater<int>> pq;

		int totalDays = 0, ans = 0;
		// find totalDays (last day when any event ends)
		for (auto& e : events) totalDays = max(totalDays, e[1]);

		// check for every day, if an even is available to attend
		// attend the one that ends the soonest
		for (int d = events[0][0], i = 0; d <= totalDays; d++) {
			// remove finished events from pq
			while (!pq.empty() and pq.top() < d)
				pq.pop();
			// push all events starting today to heap (push end day only)
			while (i < events.size() and events[i][0] == d)
				pq.push(events[i][1]), i++;
			// attend the earliest ending event
			if (!pq.empty())
				pq.pop(), ans++;
		}

		return ans;
	}
};