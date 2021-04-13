// https://leetcode.com/problems/longest-string-chain/

class Solution {
public:
	int longestStrChain(vector<string>& words) {
		sort(words.begin(), words.end(), [](auto& w1, auto& w2) {
			if (w1.size() == w2.size()) return w1<w2;
			return w1.size() < w2.size();
		});
		vector<int> dp(words.size(), 1);
		int ans = 1;

		for (int i=0; i < words.size(); i++) {
			for (int j=0; j < i; j++) {
				if (isPred(words[j], words[i]))
					dp[i] = max(dp[i], 1+dp[j]);
			}
			ans = max(ans, dp[i]);
		}
		
		return ans;
	}

	bool isPred(string w1, string w2) {
		if (w1.size()+1 != w2.size()) return false;
		int i=0, j=0, mismatch=0;
		while (i < w1.size() && j < w2.size()) {
			if (w1[i] == w2[j]) i++;
			else if (++mismatch == 2) break;
			j++;
		}
		return (i == w1.size() && mismatch == 1)
			or (i == w1.size() && j+1 == w2.size());
	}
};

