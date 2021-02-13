// https://leetcode.com/problems/burst-balloons/

// https://leetcode.com/problems/burst-balloons/discuss/76228/Share-some-analysis-and-explanations

// ********* divide and conquer with memorization *******
class Solution {
	vector<vector<int>> dp;
public:
	int maxCoins(vector<int>& nums) {
		vector<int> n = {1};
		for (int i:nums) if (i>0) n.push_back(i);
		n.push_back(1);
		dp.resize(n.size()+1, vector<int>(n.size()+1, -1));
		return burst(n, 0, n.size()-1);
	}

	int burst(vector<int>& n, int start, int end) {
		if (start+1 == end) return 0;
		if (dp[start][end] != -1) return dp[start][end];
		int ans = 0;
		for (int i=start+1; i<end; i++) {
			int burstLeft = burst(n, start, i);
			int burstRight = burst(n, i, end);
			ans = max(ans, n[start]*n[i]*n[end] + burstLeft + burstRight);
		}
		return dp[start][end] = ans;
	}
};


// ******* divide & conquer with backtrack O(n!) ********
class Solution {
public:
	int maxCoins(vector<int>& n, int start=0) {
		if (start == n.size()-1) return n[start];
		int sum=INT_MIN;
		for (int i=0; i<n.size(); i++) {
			int left = (i>0) ? n[i-1] : 1, right = (i+1<n.size()) ? n[i+1] : 1;
			int curSum = left*right*n[i];
			int temp=n[i]; n[i]=left;
			sum = max(sum, curSum+maxCoins(temp,i+1));
			n[i] = temp;
		}
		return sum;
	}
};