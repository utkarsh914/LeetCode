// https://leetcode.com/problems/number-of-good-ways-to-split-a-string/

class Solution {
public:
	int numSplits(string& s) {
		vector<vector<int>> dp(s.size()+1, vector<int> (26));
		// store pre-freq arrays for each index
		for (int i = 0; i < s.size(); i++) {
			dp[i+1] = dp[i];
			dp[i+1][s[i]-'a']++;
		}

		int count = 0;
		for (int i = 0; i < s.size()-1; i++) {
			if (unique(dp, 0, i) == unique(dp, i+1, s.size()-1))
				count++;
		}

		return count;
	}

	int unique(vector<vector<int>>& dp, int start, int end) {
		vector<int>& last = dp[end+1], &first = dp[start];
		int count = 0;
		for (int i = 0; i < 26; i++)
			if (last[i] - first[i] > 0) count++;
		return count;
	}
};









class Solution {
public:
	int numSplits(string& s) {
		vector<int> fwd(s.size()), rev(s.size());
		// store pre-freq arrays for each index
		// forward
		unordered_set<char> set;
		for (int i = 0; i < s.size(); i++) {
			set.insert(s[i]);
			fwd[i] = set.size();
		}
		// backward
		set.clear();
		for (int i = s.size()-1; i >= 0; i--) {
			set.insert(s[i]);
			rev[i] = set.size();
		}

		int count = 0;
		for (int i = 0; i < s.size()-1; i++) {
			if (fwd[i] == rev[i+1])
				count++;
		}

		return count;
	}
};