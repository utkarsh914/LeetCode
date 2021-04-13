// https://leetcode.com/problems/can-i-win/

/*
In the "100 game" two players take turns adding, to a running total, any integer from 1 to 10. The player who first causes the running total to reach or exceed 100 wins.

What if we change the game so that players cannot re-use integers?

For example, two players might take turns drawing from a common pool of numbers from 1 to 15 without replacement until they reach a total >= 100.

Given two integers maxChoosableInteger and desiredTotal, return true if the first player to move can force a win, otherwise return false. Assume both players play optimally.


Example 1:

Input: maxChoosableInteger = 10, desiredTotal = 11
Output: false
Explanation:
No matter which integer the first player choose, the first player will lose.
The first player can choose an integer from 1 up to 10.
If the first player choose 1, the second player can only choose integers from 2 up to 10.
The second player will win by choosing 10 and get a total = 11, which is >= desiredTotal.
Same with other integers chosen by the first player, the second player will always win.
*/


class Solution {
	short dp[1<<21];
public:
	bool canIWin(int M, int T) {
		// sum of entire choosable pool should be chosable combinely
		if (2*T > M*(1+M)) return false;
		memset(dp, -1, sizeof(dp));
		return canWin(M, 0, T);
	}

	bool canWin(int M, int vis, int T) {
		if (dp[vis] != -1) return dp[vis];
		// try all currently available numbers
		for (int i=1; i <= M; i++) {
			// if i is available to pick and
			// my opponent can't win after I picked, or required total is <= 0 after picking i,
			// I win!
			if (!(vis & (1 << i))) {
				if (i >= T or !canWin(M, vis | (1 << i), T - i))
					return dp[vis] = true;
			}
		}
		return dp[vis] = false;
	}
};


class Solution {
	vector<unordered_map<string, bool>> dp;
public:
	bool canIWin(int maxChoosableInteger, int desiredTotal) {
		if (!canPlay(maxChoosableInteger, desiredTotal))
			return false;
		dp.clear();
		dp.resize(desiredTotal+1);
		string vis(maxChoosableInteger+1, '0');
		return canWin(vis, desiredTotal);
	}

	bool canWin(string vis, int desiredTotal) {
		if (dp[desiredTotal].count(vis)) return dp[desiredTotal][vis];
		for (int i=1; i < vis.size(); i++) {
			if (vis[i] == '0') {
				vis[i] = '1';
				if (i >= desiredTotal or !canWin(vis, desiredTotal - i))
					return dp[desiredTotal][vis] = true;
				vis[i] = '0';
			}
		}
		return dp[desiredTotal][vis] = false;
	}

	bool canPlay(int m, int d) {
		return 2*d <= m*(1+m);
	}
};
