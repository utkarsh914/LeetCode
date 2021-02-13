// https://leetcode.com/problems/concatenation-of-consecutive-binary-numbers/


class Solution {
public:
	int concatenatedBinary(int n) {
		long long int M = 1000000007;
		long long int ans = 0;
		for (int i=1; i<=n; i++) {
			int bits = (int)log2(i)+1;
			ans = (ans << bits) | i;
			ans %= M;
		}
		return (int)ans;
	}
};



class Solution {
public:
	int concatenatedBinary(int n) {
		long ans = 0, mod = 1e9+7, len = 0;
		for (int i = 1; i <= n; ++i) {
			if ((i & (i - 1)) == 0) ++len; // length is increased only when the curr num is power of 2
			ans = ((ans << len) % mod + i) % mod;
		}
		return ans;
	}
};