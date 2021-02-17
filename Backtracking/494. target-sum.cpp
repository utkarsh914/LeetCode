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



class Solution {
	// A hash function used to hash a pair of any kind 
	struct hash_pair { 
		template <class T1, class T2> 
		size_t operator()(const pair<T1, T2>& p) const { 
			auto hash1 = hash<T1>{}(p.first); 
			auto hash2 = hash<T2>{}(p.second); 
			return hash1 ^ hash2; 
		}
	};
	
	unordered_map<pair<int,int>, int, hash_pair> dp;

public:
	int findTargetSumWays(vector<int>& nums, int S) {
		if (S > 1000) return 0;
		return dfs(nums, 0, S);
	}

	int dfs(vector<int>& nums, int start, int S) {
		if (start == nums.size()-1)
			return (int)(nums[start] == S) + (int)(-nums[start] == S);
		if (dp.count({start, S}))
			return dp[{start, S}];

		int ans = 0;
		ans += dfs(nums, start+1, S-nums[start]); // take +
		ans += dfs(nums, start+1, S+nums[start]); // take -
		return dp[{start, S}] = ans;
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