// https://leetcode.com/problems/stone-game-ii/

/*
Input: piles = [2,7,9,4,4]
Output: 10
Explanation:  If Alice takes one pile at the beginning, Bob takes two piles, then Alice takes 2 piles again.
Alice can get 2 + 4 + 4 = 10 piles in total. If Alice takes two piles at beginning, then Bob can take all three piles left.
In this case, Alice get 2 + 7 = 9 piles in total. So we return 10 since it's larger. 
*/

class Solution {

	int collect(vector<int>& p, int start, int M) {
		if (start >= p.size()) return 0;
		if (dp[start][M] != -1) return dp[start][M];
		
		int ans = INT_MIN, end = p.size()-1;
		
		// if remaining piles are less than or equal to 2*M, take all of them
		if (end-start+1 <= 2*M)
			return dp[start][M] = getRangeSum(p, start, end);

		for (int i=start, X=1; i<p.size() && X<=2*M; i++, X++) {
			ans = max(ans, getRangeSum(p, start, end) - collect(p, i+1, max(M, X)));
		}

		return dp[start][M] = ans;
	}

public:
	int stoneGameII(vector<int>& p) {
		calculatePresum(p);
		dp.resize(p.size(), vector<int> (p.size()+1, -1));
		return collect(p, 0, 1);
	}

private:

	vector<int> presum;
	vector<vector<int>> dp;

	void calculatePresum(vector<int>& p) {
		presum = vector<int> (p.begin(), p.end());
		for (int i=1; i<presum.size(); i++)
			presum[i] += presum[i-1];
	}

	int getRangeSum(vector<int>& p, int i, int j) {
		return presum[j] - presum[i] + p[i];
	}
};








//*********** DP (BOTTOM UP) ************
/*
dp[i][j] is the maximum number of stones Alex can get when starting at index i with M = j
sufsum[i] is the total number of stones from index i to the end
The dp matrix for Lee is the same. And the stragegy for Alex is to choose an optimal X to minimize the number of stones Lee can get when starting at index (i + X) with M = max(X,j). Here we have the recurrence formula

dp[i][j] = max(sufsum[i] - dp[i + X][max(j, X)]) where 1<= X <= 2j;
*/

class Solution {
public:
	int stoneGameII(vector<int>& piles) {
		int length = piles.size();
		vector<vector<int>>dp(length + 1, vector<int>(length + 1,0));
		vector<int> sufsum (length + 1, 0);
		for (int i = length - 1; i >= 0; i--) {
			sufsum[i] = sufsum[i + 1] + piles[i];
		}
		for (int i = 0; i <= length; i++) {
			dp[i][length] = sufsum[i];
		}
		for (int i = length - 1; i >= 0; i--) {
			for (int j = length - 1; j >= 1; j--) {
				for (int X = 1; X <= 2 * j && i + X <= length; X++) {
					dp[i][j] = max(dp[i][j], sufsum[i] - dp[i + X][max(j, X)]);
				}
			}
		}
		return dp[0][1];
	}
};