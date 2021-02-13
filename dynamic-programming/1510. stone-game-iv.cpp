// https://leetcode.com/problems/stone-game-iv/

// ********** O(n*sqrt(n)) time **********
class Solution {
public:
	bool winnerSquareGame(int n) {

		vector<int> squares;
		vector<bool> dp(n+1, false);

		for (int i=1; i*i <= n; i++) {
			squares.push_back(i*i);
		}

		for (int i=1; i<=n ; i++) {
			for (int sq:squares) {
				if (sq > i) break;
				if (dp[i-sq] == false) {
					dp[i] = true;
					break;
				}
			}
		}
		
		return dp[n];
	}
};