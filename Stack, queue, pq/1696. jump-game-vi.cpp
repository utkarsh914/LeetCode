// https://leetcode.com/problems/jump-game-vi/

/*
You are given a 0-indexed integer array nums and an integer k.
You are initially standing at index 0. In one move, you can jump at most k steps forward
without going outside the boundaries of the array. That is, you can jump from index i to any index
in the range [i + 1, min(n - 1, i + k)] inclusive.
You want to reach the last index of the array (index n - 1).
Your score is the sum of all nums[j] for each index j you visited in the array.
Return the maximum score you can get.

Example 1:

Input: nums = [1,-1,-2,4,-7,3], k = 2
Output: 7
Explanation: You can choose your jumps forming the subsequence [1,-1,4,3] (underlined above). The sum is 7.
*/



// similar to: 239. Sliding window maximum


/*
 ********** USING MONOQUE **********
Let's try to solve this from the end for better visualization.
At every index i we want to pick the maximum result from i+1 to i+k and add nums[i] to it
A maxium from i+1 to i+k can be found in O(1) time using a monoqueue when we start from the end.

Now all we need to do is use this monoqueue to get the maximum result for the next k indices and store it somewhere,
we can use the input array itself as an auxillary array.
Let's store only the indices in the monoqueue so that we can limit the monoqueue
to have results only for the next k indices at max.
*/
class Solution {
public:
	int maxResult(vector<int>& n, int k) {
		deque<array<int,2>> dq; // {value, index}
		
		for (int i=n.size()-1; i>=0; i--) {
			// remove out of range ele from front
			while (!dq.empty() && dq.front()[1] > i+k )
				dq.pop_front();

			int curScore = n[i] + ( !dq.empty() ? dq.front()[0] : 0 );

			// push curScore to dq keeping it monotonous decreasing
			while (!dq.empty() && curScore > dq.back()[0])
				dq.pop_back();
			dq.push_back({ curScore, i });

			// return
			if (i == 0) return curScore;
		}
		
		return -1;
	}
};



/*
 ************ USING PRIORITY QUEUE ***************

Let dp[i] be "the maximum score to reach the end starting at index i".
The answer for dp[i] is nums[i] + min{dp[i+j]} for 1 <= j <= k. That gives an O(n*k) solution.

Instead of checking every j for every i, keep track of the smallest dp[i] values in a heap
and calculate dp[i] from right to left.
When the smallest value in the heap is out of bounds of the current index, remove it and keep checking.
*/
class Solution {
public:
	int maxResult(vector<int>& n, int k) {
		priority_queue<array<int,2>> pq;
		
		for (int i=n.size()-1; i>=0; i--) {
			// remove out of range ele from front
			while (!pq.empty() && pq.top()[1] > i+k )
				pq.pop();
			int curScore = n[i] + ( !pq.empty() ? pq.top()[0] : 0 );
			pq.push({ curScore, i });
			// return
			if (i == 0) return curScore;
		}
		
		return -1;
	}
};





//********** DP (gives TLE) **********
class Solution {
public:
	int dfs(vector<int> &nums, vector<int> &memo, int indx, int k) {
		if (indx >= nums.size()) return 0;
		if (indx == nums.size() - 1) return nums[indx];
		if (memo[indx] > INT_MIN) return memo[indx];
		for (int i = indx + 1; i < nums.size() && i <= indx + k; i++) {
			memo[indx] = max(memo[indx], dfs(nums, memo, i, k));
			if (nums[i] >= 0) break;
		}
		return memo[indx] += nums[indx];
	}
	int maxResult(vector<int>& nums, int k) {
		vector<int> memo(nums.size(), INT_MIN);
		return dfs(nums, memo, 0, k);
	}
};