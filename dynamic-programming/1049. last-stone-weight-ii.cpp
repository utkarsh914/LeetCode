// https://leetcode.com/problems/last-stone-weight-ii/

/*
You are given an array of integers stones
where stones[i] is the weight of the ith stone.

We are playing a game with the stones.
On each turn, we choose any two stones and smash them together.
Suppose the stones have weights x and y with x <= y.
The result of this smash is:

If x == y, both stones are destroyed, and
If x != y, the stone of weight x is destroyed,
and the stone of weight y has new weight y - x.
At the end of the game, there is at most one stone left.

Return the smallest possible weight of the left stone.
If there are no stones left, return 0.

Example 1:

Input: stones = [2,7,4,1,8,1]
Output: 1
Explanation:
We can combine 2 and 4 to get 2, so the array converts to [2,7,1,8,1] then,
we can combine 7 and 8 to get 1, so the array converts to [2,1,1,1] then,
we can combine 2 and 1 to get 1, so the array converts to [1,1,1] then,
we can combine 1 and 1 to get 0, so the array converts to [1], then that's the optimal value.
*/






/**
This question eaquals to partition an array into 2 subsets whose difference is minimal
(1) S1 + S2  = S
(2) S1 - S2 = diff  

==> -> diff = S - 2 * S2  ==> minimize diff equals to  maximize S2 

Now we should find the maximum of S2 , range from 0 to S / 2, using dp can solve this

dp[i][j] = {true if some subset from 1st to j'th has a sum equal to sum i, false otherwise}
    i ranges from (sum of all elements) {1..n}
    j ranges from  {1..n}

same as 494. Target Sum

*/
class Solution {
public:
	int lastStoneWeightII(vector<int>& stones) {
		int sum = accumulate(stones.begin(), stones.end(), 0);
		int halfSum = sum / 2;
		bitset<1501> bits(1);
		for (auto& s : stones) bits |= (bits << s);
		int S2 = -1;
		for (int i=halfSum; i>=0 && S2==-1; i--)
			if (bits[i]) S2 = i;
		return sum - 2 * S2;
	}
};


// using array
class Solution {
public:
	int lastStoneWeightII(vector<int>& stones) {
		int sum = accumulate(stones.begin(), stones.end(), 0);
		int halfSum = sum / 2;
		vector<bool> dp(halfSum+1, false);
		dp[0] = true;

		for (auto& s : stones) {
			for (int weight = halfSum; weight >= s; weight--)
				dp[weight] |= dp[weight - s];
		}

		int S2 = -1;
		for (int i=halfSum; i>=0 && S2==-1; i--)
			if (dp[i]) S2 = i;

		return sum - 2 * S2;
	}
};






// ============= BACKTRACK (TLE) =============
class Solution {
	string vis;
public:
	int lastStoneWeightII(vector<int>& stones) {
		vis = string(stones.size(), '0');
		return recur(stones);
	}

	int recur(vector<int>& s) {
		int last = isLast(s), ans = INT_MAX;
		if (last != -1) return last;

		for (int i=0; i < s.size(); i++) {
			if (vis[i] == '1') continue;
			for (int j=i+1; j < s.size(); j++) {
				if (vis[j] == '1') continue;
				int s_j = s[j], diff = abs(s[i]-s[j]);
				vis[i] = '1';
				if (diff == 0) vis[j] = '1';
				else s[j] = diff;
				ans = min(ans, recur(s));
				// backtrack
				vis[i] = vis[j] = '0';
				s[j] = s_j;
			}
		}
		
		return ans;
	}

	int isLast(vector<int>& stones) {
		int c = 0, ans = -1;
		for (int i=0; i < stones.size(); i++) {
			if (vis[i]  == '0') ans = stones[i], c++;
		}
		if (c == 0) return 0;
		else return c == 1 ? ans : -1;
	}
};