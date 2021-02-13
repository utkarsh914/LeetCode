// https://leetcode.com/problems/stone-game-vii/

// dp[i][j] stores the lead(diff in curr move and next move by opponent)

class Solution {
	vector<int> presum;
	void calculatePresum(vector<int>& piles) {
		presum = vector<int> (piles.begin(), piles.end());
		for (int i=1; i<presum.size(); i++)
			presum[i] += presum[i-1];
	}
	int sum(vector<int>& piles, int i, int j) {
		return presum[j]-presum[i]+piles[i];
	}

public:
	int stoneGameVII(vector<int>& stones) {
		calculatePresum(stones);
		int size = stones.size();
		vector<vector<int>> dp(size, vector<int>(size, 0));

		for (int len=2; len<=size; len++) {
			for (int i=0, j=len-1; j<size; i++, j++) {
				int bobOnRight = dp[i+1][j], bobOnLeft = dp[i][j-1];
				int leftSum  = sum(stones, i, j-1);
				int rightSum = sum(stones, i+1, j);
				dp[i][j] = max( leftSum - bobOnLeft, rightSum - bobOnRight );
			}
		}

		return dp[0][size-1];
	}
};