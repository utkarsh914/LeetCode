// https://leetcode.com/problems/wildcard-matching/

class Solution {
	vector<vector<short>> dp;
public:
	bool isMatch(string& s, string& p) {
		dp.resize(s.size()+1, vector<short> (p.size()+1, -1));
		dp[s.size()][p.size()] = 1;
		// if end of text is reached, only * can be allowed in pattern
		for (int i = p.size()-1; i >= 0; i--)
			dp[s.size()][i] = p[i] == '*' ? dp[s.size()][i+1] : 0;
		// if end of pattern is reached, then not possible
		for (int i = 0; i < s.size(); i++)
			dp[i][p.size()] = 0;
		
		return match(s, p, 0, 0);
	}

	bool match(string& s, string& p, int x, int y) {
		if (dp[x][y] != -1) return dp[x][y];

		bool ans = false;
		if (p[y] == '?') {
			ans = match(s, p, x+1, y+1);
		}
		else if (p[y] != '*') {
			ans = s[x] == p[y] and match(s, p, x+1, y+1);
		}
		// p[y] == '*'
		else {
			ans = match(s, p, x, y+1) // match none
				or match(s, p, x+1, y) // match one char (current)
				or match(s, p, x+1, y+1); // match cur char (end the matching)
		}

		return dp[x][y] = ans;
	}
};
/*
--- can combine last 2 conditions to 1 -----

else if (p[y] == '*') {
	ans = match(s, p, x, y+1) // match none
		or match(s, p, x+1, y); // match one or more char
}
*/










class Solution {
public:
	bool isMatch(string& s, string& p) {
		// whether s.substr of length i match with p.substr of len j
		int ls = s.size(), lp = p.size();
		bool dp[ls+1][lp+1];
		dp[0][0] = true;
		// if end of text is reached, only * can be allowed in pattern
		for (int j = 1; j <= lp; j++) {
			dp[0][j] = p[j-1]=='*' ? dp[0][j-1] : false;
		}
		// if end of pattern is reached, then not possible
		for (int i = 1; i <= ls; i++) {
			dp[i][0] = false;
		}

		for (int i = 1; i <= ls; i++) {
			for (int j = 1; j <= lp; j++) {
				if (p[j-1] == '?') dp[i][j] = dp[i-1][j-1];
				else if (p[j-1] != '*') dp[i][j] = s[i-1] == p[j-1] and dp[i-1][j-1];
				else if (p[j-1] == '*') dp[i][j] = dp[i-1][j] or dp[i][j-1];
			}
		}
		
		return dp[ls][lp];
	}
};
/*
adceb
*a*b
*/






// https://leetcode.com/problems/wildcard-matching/

class Solution {
public:
	bool isMatch(string& s, string& p) {
		// whether s.substr of length i match with p.substr of len j
		int ls = s.size(), lp = p.size();
		bool dp[2][lp+1];
		dp[0][0] = true;
		// if end of text is reached, only * can be allowed in pattern
		for (int j = 1; j <= lp; j++) {
			dp[0][j] = p[j-1]=='*' ? dp[0][j-1] : false;
		}

		for (int i = 1; i <= ls; i++) {
			for (int j = 0; j <= lp; j++) {
				// if end of pattern is reached, then not possible
				if (j == 0) dp[i%2][j] = false;
				else if (p[j-1] == '?') dp[i%2][j] = dp[(i+1)%2][j-1];
				else if (p[j-1] != '*') dp[i%2][j] = s[i-1] == p[j-1] and dp[(i+1)%2][j-1];
				else if (p[j-1] == '*') dp[i%2][j] = dp[(i+1)%2][j] or dp[i%2][j-1];
			}
		}
		
		return dp[ls%2][lp];
	}
};