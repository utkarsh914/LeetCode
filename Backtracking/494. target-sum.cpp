// https://leetcode.com/problems/target-sum/

/*
You are given a list of non-negative integers, a1, a2, ..., an, and a target, S.
Now you have 2 symbols + and -.
For each integer, you should choose one from + and - as its new symbol.
Find out how many ways to assign symbols to make sum of integers equal to target S.

Example 1:

Input: nums is [1, 1, 1, 1, 1], S is 3. 
Output: 5
Explanation: 

-1+1+1+1+1 = 3
+1-1+1+1+1 = 3
+1+1-1+1+1 = 3
+1+1+1-1+1 = 3
+1+1+1+1-1 = 3

There are 5 ways to assign symbols to make the sum of nums be target 3.
*/









/*
******* 0/1 Knapsack *******

some numbers have to be given + sign, and some -
let all no's having + sign sum up to A,
and all no's having - sign sum up to B

so, A + B = sum of array
and A - B = target (S)

which means, A = (sum + target) / 2;

now, if sum + target is even, any combination is not possible,
so return 0

else, find the number of ways you can pick some items
so that they sum up to A
*/
class Solution {
public:
	int findTargetSumWays(vector<int>& arr, int target) {
		int sum = accumulate(arr.begin(), arr.end(), 0);
		if ((sum + target) % 2 == 1) return 0;
		int A = (sum + target) / 2;

		/*
		we use 'size+1' rather than 'size', to make it easier to tackle the boundary.
		dp[i][sum] means how many ways we choose from first i elements,
		and not upto i index
		*/
		vector<vector<int>> dp(arr.size()+1, vector<int>(A+1, 0));
		dp[0][0] = 1;

		for (int i = 1; i <= arr.size(); i++) {
			for (int j = 0; j <= A; j++) {
				dp[i][j] = dp[i-1][j]; // don't pick cur ele
				if (arr[i-1] <= j) // 
					dp[i][j] += dp[i-1][j - arr[i-1]];
			}
		}

		return dp[arr.size()][A];
	}
};




class Solution {
public:
	int findTargetSumWays(vector<int>& arr, int target) {
		int sum = accumulate(arr.begin(), arr.end(), 0);
		if ((sum + target) % 2 == 1) return 0;
		int A = (sum + target) / 2;

		vector<int> dp(A+1);
		dp[0] = 1;

		for (int i = 0; i < arr.size(); i++) {
			for (int sum = A; sum >= arr[i]; sum--)
				dp[sum] += dp[sum - arr[i]];
		}

		return dp[A];
	}
};









// ******* better Backtracking + DP *******
class Solution {
	vector<unordered_map<int,int>> dp;
public:
	int findTargetSumWays(vector<int>& A, int S) {
		dp.resize(A.size());
		return dfs(A, 0, S);
	}

	int dfs(vector<int>& A, int start, int S) {
		if (start >= A.size()) return int(S == 0);
		if (dp[start].count(S)) return dp[start][S];

		int minus = dfs(A, start+1, S + A[start]); // take -
		int plus  = dfs(A, start+1, S - A[start]); // take +
		return dp[start][S] = minus + plus;
	}
};







// ******* recursion *******
class Solution {
	int count = 0;
public:
	int findTargetSumWays(vector<int>& nums, int S) {
		if (S > 1000) return 0;
		dfs(nums, 0, 0, S);
		return count;
	}

	void dfs(vector<int>& nums, int start, int curVal, int S) {
		if (start == nums.size()) {
			count += curVal==S;
			return;
		}
		dfs(nums, start+1, curVal+nums[start], S);
		dfs(nums, start+1, curVal-nums[start], S);
	}
};

