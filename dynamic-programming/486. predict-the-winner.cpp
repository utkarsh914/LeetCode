// https://leetcode.com/problems/predict-the-winner/

/*
You are given an integer array nums.
Two players are playing a game with this array: player 1 and player 2.

Player 1 and player 2 take turns, with player 1 starting first.
Both players start the game with a score of 0.
At each turn, the player takes one of the numbers from either end of the array
(i.e., nums[0] or nums[nums.length - 1]) which reduces the size of the array by 1.
The player adds the chosen number to their score.
The game ends when there are no more elements in the array.
Return true if Player 1 can win the game.
If the scores of both players are equal, then player 1 is still the winner,
and you should also return true.
You may assume that both players are playing optimally.

Example 1:

Input: nums = [1,5,2]
Output: false
Explanation: Initially, player 1 can choose between 1 and 2. 
If he chooses 2 (or 1), then player 2 can choose from 1 (or 2) and 5.
If player 2 chooses 5, then player 1 will be left with 1 (or 2).
So, final score of player 1 is 1 + 2 = 3, and player 2 is 5. 
Hence, player 1 will never be the winner and you need to return false.
*/

class Solution {
public:
	bool PredictTheWinner(vector<int>& n) {
		// we store the diff cur player can obtain at the end,
		// if we are considering the subarray from i to j
		int dp[21][21] = {};

		for (int len=1; len <= n.size(); len++) {
			for (int i=0, j=len-1; j < n.size(); i++, j++) {
				if (len == 1) dp[i][j] = n[i];
				else if (len == 2) dp[i][j] = abs(n[i]-n[j]);
				else dp[i][j] = max(n[i]-dp[i+1][j], n[j]-dp[i][j-1]);
			}
		}
		// if diff for whole array is >= 0, then first player can win
		return dp[0][n.size()-1] >= 0;
	}
};