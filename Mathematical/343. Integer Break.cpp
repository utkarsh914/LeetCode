// https://leetcode.com/problems/integer-break/

class Solution {
public:
	int integerBreak(int n) {
		int ans = 1;
		// break in k parts k -> [2, 1+n/2]
		for (int k = 2; k <= 1 + n/2; k++)
			ans = max(ans, getBrokenSum(n, k));
		return ans;
	}

	int getBrokenSum(long n, long k, long ans = 1) {
		int rem = n % k, rest = k - rem;
		while (rem--) ans *= (1 + n/k);
		while (rest--) ans *= (n / k);
		return ans;
	}
	/*
	int getBrokenSum(long n, long k) {
		vector<long> nums;
		int rem = n % k;
		for (int i = 0; i < rem; i++)
			nums.push_back(1 + n/k);
		for (int i = 0; i < k - n%k; i++)
			nums.push_back(n/k);

		long ans = 1;
		for (auto& x : nums)
			ans *= x;
		return ans;
	}
	*/
};