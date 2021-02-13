
class Solution {
public:
	int countPalindromicSubsequences(string s);
};

int Solution::countPalindromicSubsequences(string s) {
	
	int dp[s.length()][s.length()];
	int prev[s.length()];
	int next[s.length()];
	memset(dp, 0, sizeof(dp));
	unordered_map<char,int> mp;
	// calculate prev occurence of all characters
	for (int i=0; i<s.length(); i++) {
		prev[i] = (mp.count(s[i])) ? mp[s[i]] : -1;
		mp[s[i]]=i;
	}
	// calculate next occurence of all characters
	mp.clear();
	for (int i=s.length()-1; i>=0; i--) {
		next[i] = (mp.count(s[i])) ? mp[s[i]] : -1;
		mp[s[i]]=i;
	}
	mp.clear();
	
	// for all lengths
	int M = 1000000007;
	for (int len=1; len<=s.length(); len++) {
		for (int i=0, j=len-1; j<=s.length()-1; i++, j++) {
			if (len==1 or len==2){
				dp[i][j]=len;
				continue;
			}
			if (s[i]!=s[j]) dp[i][j] = (dp[i][j-1] + dp[i+1][j] - dp[i+1][j-1])%M;
			else {
				int n=next[i], p=prev[j];
				// no 'a' in mid
				if (n > p) dp[i][j] = (2*(dp[i+1][j-1])%M + 2)%M;
				// only one 'a' in mid
				else if (n == p) dp[i][j] = ((2*dp[i+1][j-1])%M + 1)%M;
				// more than one 'a' in mid
				else if (n < p) dp[i][j] = ((2*dp[i+1][j-1])%M - dp[n+1][p-1])%M;
			}
			dp[i][j] = (dp[i][j] < 0) ? dp[i][j]+M : dp[i][j];
		}
	}
	
	return dp[0][s.length()-1];
}

static auto _______ = [](){
	std::ios::sync_with_stdio(false);
	std::cin.tie(NULL);
	std::cout.tie(NULL);
	return 0;
}();