// https://leetcode.com/problems/find-the-shortest-superstring/

// it is a variation of Travelling Salesman problem





/*
gives TLE / Heap-buffer overflow for bigger input
*/
class Solution {
	map<pair<string,string>, string> dp;
public:
	string shortestSuperstring(vector<string>& W) {
		return solve(W, string(W.size(), 'F'), "");
	}

	string solve(vector<string>& W, string vis, string base) {
		if (vis == string(W.size(), 'T'))
			return base;

		if (dp.count({vis,base})) return dp[{vis,base}];

		string ans = string(241, '.');

		for (int i = 0; i < W.size(); i++) {
			if (vis[i] == 'T') continue;
			vis[i] = 'T';
			string ans1 = solve(W, vis, joinAtBegin(base, W[i]));
			string ans2 = solve(W, vis, joinAtEnd(base, W[i]));
			vis[i] = 'F';
			// set ans
			if (ans1.size() < ans.size()) ans = ans1;
			if (ans2.size() < ans.size()) ans = ans2;
		}

		// return ans;
		return dp[{vis,base}] = ans;
	}

	string joinAtBegin(string& base, string& s) {
		if (!base.size()) return s;
		for (int i = 0; i < s.size(); i++) {
			string sub = s.substr(i);
			if (equal(sub.begin(), sub.end(), base.begin()))
				return s.substr(0, i) + base;
		}
		return s + base;
	}

	string joinAtEnd(string& base, string& s) {
		if (!base.size()) return s;
		for (int i = s.size()-1; i >= 0; i--) {
			string sub = s.substr(0, i+1);
			if (equal(sub.rbegin(), sub.rend(), base.rbegin()))
				return base + s.substr(i+1);
		}
		return base + s;
	}
};