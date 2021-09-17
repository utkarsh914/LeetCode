// https://leetcode.com/problems/smallest-sufficient-team/







class Solution {
public:
	vector<int> smallestSufficientTeam(vector<string>& req_skills,
			vector<vector<string>>& people_) {
		
		unordered_map<string, int> map;
		for (int i = 0; i < req_skills.size(); i++) {
			map[req_skills[i]] = i;
		}
		
		vector<vector<int>> p;
		
		for (auto& pp : people_) {
			vector<int> v;
			for (auto& s : pp)
				v.push_back(map[s]);
			p.push_back(v);
		}
		
		int maskCount = 1 << req_skills.size();
		int N = p.size();
		int dp[N+1][maskCount];

		for (int i = 0; i <= N; i++) {
			for (int mask = 0; mask < maskCount; mask++) {
				if (mask == 0) dp[i][mask] = 0;
				else if (i == 0) dp[i][mask] = INT_MAX / 2;
				else {
					int notTake = dp[i-1][mask], take = INT_MAX;
					bool canTake = false;
					// check if current person can be taken
					for (int skill : p[i-1]) {
						if (mask & (1 << skill)) canTake = true;
					}
					if (canTake == true) {
						int newmask = mask;
						for (int skill : p[i-1])
							newmask = newmask & ~(1 << skill); // clear this bit
						take = 1 + dp[i-1][newmask];
					}
					dp[i][mask] = min(take, notTake);
				}
			}
		}
		

		// trace back the most optimal answer

		vector<int> ans;
		int i = N, mask = maskCount-1;

		while (i > 0 and mask > 0) {
			int prevmask = mask;
			for (int skill : p[i-1]) {
				prevmask = prevmask & ~(1 << skill); // clear this bit
			}
			if (dp[i][mask] != dp[i-1][mask] and dp[i][mask] != dp[i][prevmask])
				ans.push_back(i-1);
			if (dp[i-1][mask] <= dp[i][mask]) i--;
			else mask = prevmask;
		}

		return ans;
	}
};







class Solution {
public:
	int smallestSufficientTeam(vector<string>& req_skills,
			vector<vector<string>>& people_) {
		
		unordered_map<string, int> map;
		for (int i = 0; i < req_skills.size(); i++) {
			map[req_skills[i]] = i;
		}
		
		vector<vector<int>> p;
		
		for (auto& pp : people_) {
			vector<int> v;
			for (auto& s : pp)
				v.push_back(map[s]);
			p.push_back(v);
		}
		
		int n = req_skills.size();
		return pick((1 << n) - 1, p, 0);
	}
	
	int pick(int mask, vector<vector<int>>& p, int ind) {
		if (mask == 0) return 0;
		if (ind == p.size()) return INT_MAX / 2;
		if (dp[mask][ind] != -1) return dp[mask][ind];
		
		int notTake = pick(mask, p, ind + 1);
		int take = INT_MAX;
		bool canTake = false;
		for (int skill : p[ind]) {
			if (mask & (1 << skill))
				canTake = true;
		}
		if (canTake) {
			int newmask = mask;
			for (int skill : newmask) {
				newmask = newmask & ~(1 << skill); // clear this bit
			}
			take = 1 + pick(newmask, p, ind + 1);
		}
		
		return dp[mask][ind] = min(take, notTake);
	}
};