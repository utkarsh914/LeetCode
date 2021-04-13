// https://leetcode.com/problems/best-team-with-no-conflicts/

/*
You are the manager of a basketball team. For the upcoming tournament, you want to choose the team with the highest overall score. The score of the team is the sum of scores of all the players in the team.

However, the basketball team is not allowed to have conflicts. A conflict exists if a younger player has a strictly higher score than an older player. A conflict does not occur between players of the same age.

Given two lists, scores and ages, where each scores[i] and ages[i] represents the score and age of the ith player, respectively, return the highest overall score of all possible basketball teams.

 

Example 1:

Input: scores = [1,3,5,10,15], ages = [1,2,3,4,5]
Output: 34
Explanation: You can choose all the players.
Example 2:

Input: scores = [4,5,6,5], ages = [2,1,2,1]
Output: 16
Explanation: It is best to choose the last 3 players. Notice that you are allowed to choose multiple people of the same age.
*/




// ================ LIS =============
class Solution {
public:
	int bestTeamScore(vector<int>& scores, vector<int>& ages) {
		int size = scores.size(), ans = INT_MIN;
		vector<array<int,2>> arr(size);
		for (int i=0; i < size; i++)
			arr[i] = {ages[i], scores[i]};
		sort(arr.begin(), arr.end());
		
		vector<int> dp(size);

		for (int i=0; i < size; i++) {
			dp[i] = arr[i][1];
			for (int j=0; j < i; j++) {
				if (arr[i][0] == arr[j][0] or arr[i][1] >= arr[j][1])
					dp[i] = max(dp[i], arr[i][1] + dp[j]);
			}
			ans = max(ans, dp[i]);
		}
		
		return ans;
	}
	
};




class Solution {
	int dp[1002][1002];
public:
	int bestTeamScore(vector<int>& scores, vector<int>& ages) {
		memset(dp, -1, sizeof(dp));
		vector<array<int,2>> arr(scores.size()+1);
		arr[0] = {0,0};
		for (int i=1; i < arr.size(); i++) {
			arr[i] = {ages[i-1], scores[i-1]};
		}
		sort(arr.begin(), arr.end());
		return recur(arr, 1, 0);
	}
	
	int recur(vector<array<int,2>>& arr, int start, int prev) {
		if (start == arr.size()) return 0;
		if (dp[start][prev] != -1) return dp[start][prev];
		int take = 0, notTake = 0;
		if (arr[start][0] == arr[prev][0] or arr[start][1] >= arr[prev][1])
			take = arr[start][1] + recur(arr, start+1, start);
		notTake = recur(arr, start+1, prev);
		return dp[start][prev] = max(take, notTake);
	}
};







// ================ BOTTOM UP =============
class Solution {
public:
	int bestTeamScore(vector<int>& scores, vector<int>& ages) {
		vector<array<int,2>> arr(scores.size()+1);
		arr[0] = {0,0};
		for (int i=1; i < arr.size(); i++) {
			arr[i] = {ages[i-1], scores[i-1]};
		}
		sort(arr.begin(), arr.end());
		
		int size = arr.size();
		vector<vector<int>> dp(size+1, vector<int>(size+1, 0));

		for (int start=size-1; start >= 1; start--) {
			for (int prev=0; prev < start; prev++) {
				int take = 0, notTake = 0;
				if (arr[start][0] == arr[prev][0] or arr[start][1] >= arr[prev][1])
					take = arr[start][1] + dp[start+1][start];
				notTake = dp[start+1][prev];
				dp[start][prev] = max(take, notTake);
			}
		}

		return dp[1][0];
	}
	
};




// ================ BOTTOM UP, O(N) space =============
class Solution {
public:
	int bestTeamScore(vector<int>& scores, vector<int>& ages) {
		vector<array<int,2>> arr(scores.size()+1);
		arr[0] = {0,0};
		for (int i=1; i < arr.size(); i++) {
			arr[i] = {ages[i-1], scores[i-1]};
		}
		sort(arr.begin(), arr.end());
		
		int size = arr.size();
		vector<vector<int>> dp(2, vector<int>(size+1, 0));

		for (int start=size-1; start >= 1; start--) {
			for (int prev=0; prev < start; prev++) {
				int take = 0, notTake = 0;
				if (arr[start][0] == arr[prev][0] or arr[start][1] >= arr[prev][1])
					take = arr[start][1] + dp[(start+1) % 2][start];
				notTake = dp[(start+1) % 2][prev];
				dp[start % 2][prev] = max(take, notTake);
			}
		}
		
		return dp[1][0];
	}
	
};