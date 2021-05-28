// https://leetcode.com/problems/perfect-number/

/*
if N = x * y, then both x and y are factors

so, if N % i == 0, then i, N/i, both are factors, and taken

so, we need to check for i in range [2, sqrt(N)] only
*/

class Solution {
public:
	bool checkPerfectNumber(int N) {
		if (N == 1) return false;

		int sum = 1;
		for (int i = 2; i*i <= N; i++) {
			if (N % i == 0)
				sum += N/i + i;
		}
		return sum == N;
	}
};