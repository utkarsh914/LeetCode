// https://leetcode.com/problems/minimum-cost-for-tickets/

// ********* RECURSION **********
class Solution {
public:
	int mincostTickets(vector<int>& days, vector<int>& cost, int start=0) {
		int size = days.size();
		if (start >= size) return 0;

		int i=start+1;
		int day_pass	 = cost[0] + mincostTickets(days, cost, i);
		while (i<size && days[i]<days[start]+7) i++;
		int week_pass	= cost[1] + mincostTickets(days, cost, i);
		while (i<size && days[i]<days[start]+30) i++;
		int month_pass = cost[2] + mincostTickets(days, cost, i);

		return min(day_pass, min(week_pass, month_pass));
	}
};


// *************** BOTTOM-UP DP ***********
class Solution {
public:
	int mincostTickets(vector<int>& daysArr, vector<int>& cost, int start=0) {
		int size = daysArr.size();
		if (start >= size) return 0;

		unordered_set<int> days(daysArr.begin(), daysArr.end());
		vector<int> dp(367, 0);

		for (int i=365; i>=0; i--) {
			dp[i] = dp[i+1];
			if (!days.count(i)) continue;
			int day_pass	 = cost[0] + dp[min(365,i+1)];
			int week_pass	= cost[1] + dp[min(365,i+7)];
			int month_pass = cost[2] + dp[min(365,i+30)];
			dp[i] = min({ day_pass, week_pass, month_pass });
		}
	
		return dp[0];
	}
};


//********* more space optimized *********
// https://leetcode.com/problems/minimum-cost-for-tickets/discuss/226659/Two-DP-solutions-with-pictures

int mincostTickets(vector<int>& days, vector<int>& costs) {
	unordered_set<int> travel(begin(days), end(days));
	int dp[30] = {};
	for (int i = days.front(); i <= days.back(); ++i) {
		if (travel.find(i) == travel.end()) dp[i % 30] = dp[(i - 1) % 30];
		else dp[i % 30] = min({ dp[(i - 1) % 30] + costs[0],
				dp[max(0, i - 7) % 30] + costs[1], dp[max(0, i - 30) % 30] + costs[2] });
	}
	return dp[days.back() % 30];
}