// https://leetcode.com/problems/stone-game-iii/

class Solution {
/*
dp[i] means the biggest number of stones you can get more than opponent picking stones
*/
public:
	string stoneGameIII(vector<int>& stoneValue) {
		int size = stoneValue.size();
		vector<int> dp(size+1, 0);

		for (int i=size-1; i>=0; i--) {
			int maxLead = INT_MIN, take = 0;
			for (int j=i; j<i+3 && j<size; j++) {
				take += stoneValue[j];
				maxLead = max(maxLead, take - dp[j+1]);
			}
			dp[i] = maxLead;
		}

		return dp[0]==0 ? "Tie" : dp[0]>0 ? "Alice" : "Bob";
	}
};




// *********** O(1) space dp *************
// as we need only last 3 results, we can use %4
// we need 1 place to store curr result, 3 other places to access previous results
class Solution {
public:
	string stoneGameIII(vector<int>& stoneValue) {

		int size = stoneValue.size();
		vector<int> dp(4, 0);

		for (int i=size-1; i>=0; i--) {
			int maxLead = INT_MIN, take = 0;
			for (int j=i; j<i+3 && j<size; j++) { 
				take += stoneValue[j];
				maxLead = max(maxLead, take - dp[(j+1) % 4]);
			}
			dp[i % 4] = maxLead;
		}

		return dp[0]==0 ? "Tie" : dp[0]>0 ? "Alice" : "Bob";
	}
};