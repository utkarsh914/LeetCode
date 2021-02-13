// https://leetcode.com/problems/stone-game/


/*
Approach 1: Just return true

Alex is first to pick pile.
piles.length is even, and this lead to an interesting fact:
Alex can always pick odd piles or always pick even piles!

For example,
If Alex wants to pick even indexed piles piles[0], piles[2], ....., piles[n-2],
he picks first piles[0], then Lee can pick either piles[1] or piles[n - 1].
Every turn, Alex can always pick even indexed piles and Lee can only pick odd indexed piles.

In the description, we know that sum(piles) is odd.
If sum(piles[even]) > sum(piles[odd]), Alex just picks all evens and wins.
If sum(piles[even]) < sum(piles[odd]), Alex just picks all odds and wins.

So, Alex always defeats Lee in this game.
*/
class Solution {
public:
	bool stoneGame(vector<int>& piles) {
		return true;
	}
};



/*
Approach 2: 2D DP
It's tricky when we have even number of piles of stones. You may not have this condition in an interview.

Follow-up:

What if piles.length can be odd?
What if we want to know exactly the diffenerce of score?
Then we need to solve it with DP.

here dp[i][j] is the max sum that can be collected from i to j index
at every step, we select a stone from front or back, which leads to minimum sum for the next step
(bcz next step will be for the opponent, and we need to minimize his sum to win)

// used presum array to get sum of subarray in range i to j
*/
class Solution {
	vector<int> presum;

	void calculatePresum(vector<int>& piles) {
		presum = vector<int> (piles.begin(), piles.end());
		for (int i=1; i<presum.size(); i++)
			presum[i] += presum[i-1];
	}

	int getRangeSum(vector<int>& piles, int i, int j) {
		return presum[j]-presum[i]+piles[i];
	}

public:
	bool stoneGame(vector<int>& piles) {
		// make cumulative sum of piles array
		calculatePresum(piles);

		int size = piles.size();
		vector<vector<int>> dp(size, vector<int>(size));

		for (int len=1; len<=size; len++) {
			for (int i=0, j=len-1; j<size; i++, j++) {
				if (len == 1) {
					dp[i][j] = getRangeSum(piles, i, j);
				}	else {
					int currRange = getRangeSum(piles, i, j);
					dp[i][j] = max(currRange-dp[i][j-1], currRange-dp[i+1][j]);
				}
			}
		}

		int alex = dp[0][size-1];
		int lee = getRangeSum(piles, 0, size-1) - alex;
		return alex > lee;
	}
};








/* ********** DP (no presum, more optimized) ***********

dp[i][j] means the biggest number of stones you can get more than opponent picking piles in piles[i] ~ piles[j].
You can first pick piles[i] or piles[j].

If you pick piles[i], your result will be piles[i] - dp[i + 1][j]
If you pick piles[j], your result will be piles[j] - dp[i][j - 1]
So we get:
dp[i][j] = max(piles[i] - dp[i + 1][j], piles[j] - dp[i][j - 1])
*/

class Solution {
public:
	bool stoneGame(vector<int>& piles) {
	
		int size = piles.size();
		vector<vector<int>> dp(size, vector<int>(size));

		for (int len=1; len<=size; len++) {
			for (int i=0, j=len-1; j<size; i++, j++) {
				if (len == 1) {
					dp[i][j] = piles[i];
				}	else {
					dp[i][j] = max(piles[i]-dp[i+1][j], piles[j]-dp[i][j-1]);
				}
			}
		}

		return dp[0][size-1] > 0;
	}
};







// ************ 1D DP, O(N) space ************
class Solution {
public:
	bool stoneGame(vector<int>& piles) {
		int size = piles.size();
		vector<int> dp = piles;

		for (int len=2; len<=size; len++)
			for (int i=0, j=len-1; j<size; i++, j++)
				dp[i] = max(piles[i]-dp[i+1], piles[j]-dp[i]);

		return dp[0] > 0;
	}
};
/*
dp[i] is the biggest number of stones you can get more than opponent, picking piles in range piles[i] ~ piles[i + d - 1].
Key insight required to understand this approach is that d is increasing by 1 every time the outer loop finishes
and before the return, it is equal to n (that is why when we return,dp[0] is equivalent of dp[0][n - 1] from 2D version.
Loop:

for d = 1 - after inner loop finishes dp[i] contains the best score for for range p[i, i + 1], we filled dp[i:n - 1]
for d = 2 - after inner loop finishes dp[i] contains the best score for for rangep[i, i + 2], we filled dp[i:n - 2]
for d = 3 - after inner loop finishes dp[i] contains the best score for for range p[i, i + 3], we filled dp[i:n - 3]
...
for d - after inner loop finishes dp[i] contains the best score for for range p[i, i + d], we filled dp[i:n - d] (we fill one less element of dp every time we increase the window d by 1)
Where does dp[i] = max(p[i] - dp[i + 1], p[i + d] - dp[i]) come from? Let's split the cases:

1. p[i] - dp[i + 1]
p[i] is the stone at the left side of the window, if we pick it up, the opponent will take the best from dp[i + 1]
which represents best score for piles p[i + 1] ~ p[i + d ]
why? Because in previous run of the outer loop we calculated this for d - 1 and it is currently stored in dp[i + 1].

2. p[i + d] - dp[i]
p[i + d] is the stone at the right side of the window, if we pick it up, the opponent will take the best from dp[i]
which represents best score for piles p[i] ~ p[i + d - 1]
why? Because in previous run of the outer loop we calculated this for d - 1 and it is currently stored in dp[i].
*/