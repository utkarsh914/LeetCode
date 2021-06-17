// https://leetcode.com/problems/minimum-number-of-refueling-stops/








/*
Approach 2: Priority Queue, O(NlogN)

i is the index of next stops to refuel.
ans is the times that we have refeuled.
pq is a priority queue that we store all available gas.

We initial ans = 0 and in every loop:

We add all reachable stop to priority queue.
We pop out the largest gas from pq and refeul once.
If we can't refuel, means that we can not go forward and return -1
*/
class Solution {
public:
	int minRefuelStops(int target, int startFuel, vector<vector<int>>& s) {
		priority_queue<int> pq;
		int i = 0, ans = 0, curDist = startFuel;

		for (; curDist < target; ans++) {
			while (i < s.size() and s[i][0] <= curDist)
				pq.push(s[i][1]), i++;
			if (pq.empty()) return -1;
			curDist += pq.top(), pq.pop();
		}

		return ans;
	}
};
/*
A note to those who find 'greedy' solution confusing:

The 'greedy' solution never kick out any entry from the priority queue.
Besides, the 'greedy' solution won't choose the station in order.
Instead, it might pick station-4 and then pick station-2 later.
After knowing this, the correctness should be obvious by now.
The car always move until it cannot move any further.
Then it must re-fuel once. Which station to pick?
Of course the one that has the largest amount of fuel. And keep moving.
The magic is: the car needs to re-fuel at station-5, but the fuel comes from station-2.
*/









/*
-------- TLE --------
*/
class Solution {
	vector<unordered_map<int, int>> dp;
	long inf = INT_MAX/10;
	long target;

public:
	int minRefuelStops(int target, int startFuel, vector<vector<int>>& stations) {
		dp.resize(stations.size());
		this->target = target;
		sort(stations.begin(), stations.end());
		int ans = recur(startFuel, stations, 0);
		return ans < inf ? ans : -1;
	}
	
	int recur(long dist, vector<vector<int>>& s, int i) {
		if (i == s.size()) return dist >= target ? 0 : inf;
		if (dist < s[i][0]) return inf; // can't reach here (at i)
		if (dist >= target) return 0;   // target reached already
		if (dp[i].count(dist)) return dp[i][dist]; // ans in dp
		
		int refuel = 1 + recur(dist + long(s[i][1]), s, i+1);
		int dontRefuel = recur(dist, s, i+1);
		
		return dp[i][dist] = min(refuel, dontRefuel);
	}
};
