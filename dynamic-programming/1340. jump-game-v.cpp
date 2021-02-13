// https://leetcode.com/problems/jump-game-v/

class Solution {
	int dp[1001];
public:
	int maxJumps(vector<int>& arr, int d) {
		memset(dp, -1, sizeof(dp));
		int ans = 1;
		for (int i=0; i<arr.size(); i++) {
			ans = max(ans, jump(arr, i, d));
		}
		return ans;
	}
	
	int jump(vector<int>& arr,  int start, int d) {
		if (dp[start] != -1) return dp[start];
		
		int ans = 0;
		for (int i=start+1; i<arr.size() && i-start<=d && arr[i]<arr[start]; i++)
			ans = max(ans, jump(arr, i, d));
		for (int i=start-1; i>=0 && start-i<=d && arr[i]<arr[start]; i--)
			ans = max(ans, jump(arr, i, d));
		return dp[start] = 1 + ans;
	}
};