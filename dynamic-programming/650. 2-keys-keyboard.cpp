// https://leetcode.com/problems/2-keys-keyboard/

/*

*/

// ******* math *******
// find sum of all prime factors
class Solution {
public:
	int minSteps(int n) {
		int ans = 0;
		for (int i=2; i <= n; i++) {
			while (n % i == 0) {
				ans += i;
				n /= i;
			}
		}
		return ans;
	}
};



// https://leetcode.com/problems/2-keys-keyboard/discuss/105932/Java-solutions-from-naive-DP-to-optimized-DP-to-non-DP
// ***** bottom up DP *****
class Solution {
public:
	int minSteps(int n) {
		int dp[n+1];
		dp[1] = 0;
		for (int i=2; i <= n; i++) {
			dp[i] = i;
			for (int j=1; j < i; j++) {
				if (i % j == 0)
					dp[i] = min(dp[i], dp[j] + (i/j) );
			}
		}
		return dp[n];
	}
};




// ***** bottom up DP *****
class Solution {
public:
	int minSteps(int n) {
		int dp[n+1];
		dp[1] = 0;
		for (int i=2; i <= n; i++) {
			dp[i] = i;
			for (int j=2; j*j <= i; j++) {
				if (i % j == 0)
					dp[i] = min(dp[i], dp[j]+dp[i/j]);
			}
		}
		return dp[n];
	}
};



// ***** bottom up DP *****
class Solution {
public:
	int minSteps(int n) {
		int dp[n+1]; dp[1] = 0;
		
		for (int i=2; i <= n; i++) {
			for (int j=i/2; j >= 1; j--) {
				if (i % j == 0) {
					dp[i] = dp[j] + (i/j);
					break;
				}
			}
		}

		return dp[n];
	}
};



// ***** bottom up DP *****
class Solution {
public:
	int minSteps(int n) {
		int dp[n+1]; dp[1] = 0;

		for (int k = 2, i = 0; k <= n; k++) {
			for (i = k >> 1; i>=1 && k%i != 0; i--);
			dp[k] = dp[i] + k / i;
		}

		return dp[n];
	}
};
