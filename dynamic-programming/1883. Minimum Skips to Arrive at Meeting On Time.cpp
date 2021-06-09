// https://leetcode.com/problems/minimum-skips-to-arrive-at-meeting-on-time/

class Solution {
	double speed;
	int hoursBefore;
	vector<unordered_map<long, int>> dp;
	int times = 0;
public:
	int minSkips(vector<int>& D, int speed, int hoursBefore) {
		this->speed = speed;
		this->hoursBefore = hoursBefore;
		dp.clear();
		dp.resize(D.size()+1);
		int ans = recur(D, 0, 0);
		return ans >= INT_MAX/3 ? -1 : ans;
	}

	int recur(vector<int>& D, int i, double prevEnd) {
		long key = long(prevEnd*1000);
		if (i >= D.size())
			return key <= long(hoursBefore*1000) ? 0 : INT_MAX/2;
		else if (key > long(hoursBefore*1000))
			return INT_MAX/2;
		if (dp[i].count(key)) {
			// cout<<++times<<" ";
			return dp[i][key];
		}
		
		int skip = INT_MAX/2, not_skip = INT_MAX/2;
		if (ceil((prevEnd + 1.0*D[i]/speed)) > (prevEnd + 1.0*D[i]/speed))
			skip = 1 + recur(D, i+1, (prevEnd + 1.0*D[i]/speed));
		
		not_skip = recur(D, i+1, ceil(prevEnd + 1.0*D[i]/speed));
		return dp[i][key] = min(skip, not_skip);
	}
};







class Solution:
	def minSkips(self, D: List[int], speed: int, hoursBefore: int) -> int:
		dp = dict()
		INT_MAX = int(1e15)
		
		def recur(i, prevEnd) -> int:
			if (i >= len(D)):
				return 0 if prevEnd <= hoursBefore else INT_MAX;
			if prevEnd > hoursBefore:
				return INT_MAX
			if dp.get((i, prevEnd)) != None:
				return dp.get((i, prevEnd))
			
			skip, not_skip = INT_MAX, INT_MAX
			if (math.ceil((prevEnd + 1.0*D[i]/speed)) > (prevEnd + 1.0*D[i]/speed)):
				skip = 1 + recur(i+1, (prevEnd + 1.0*D[i]/speed))
			not_skip = recur(i+1, math.ceil(prevEnd + 1.0*D[i]/speed))
			dp[(i, prevEnd)] = min(skip, not_skip)
			return min(skip, not_skip)
		
		dp.update({(-2.0,-0.1) : 1})
		# print(dp)
		ans = recur(0, 0)
		return -1 if ans == INT_MAX else ans