// https://leetcode.com/problems/ugly-number-iii/

/*
Given four integers n, a, b, and c, return the nth ugly number.
Ugly numbers are positive integers that are divisible by a, b, or c.


Example 1:

Input: n = 3, a = 2, b = 3, c = 5
Output: 4
Explanation: The ugly numbers are 2, 3, 4, 5, 6, 8, 9, 10... The 3rd is 4.
Example 2:

Input: n = 4, a = 2, b = 3, c = 4
Output: 6
Explanation: The ugly numbers are 2, 3, 4, 6, 8, 9, 10, 12... The 4th is 6.
Example 3:

Input: n = 5, a = 2, b = 11, c = 13
Output: 10
Explanation: The ugly numbers are 2, 4, 6, 8, 10, 11, 12, 13... The 5th is 10.
Example 4:

Input: n = 1000000000, a = 2, b = 217983653, c = 336916467
Output: 1999999984
 

Constraints:

1 <= n, a, b, c <= 109
1 <= a * b * c <= 1018
It is guaranteed that the result will be in range [1, 2 * 109].
*/

class Solution {
public:
	int nthUglyNumber(int n, int a, int b, int c) {
		int start = 1, end = 2e9;
		while (start < end) {
			int mid = start + (end-start)/2;
			if (count(mid, a, b, c) >= n)
				end = mid;
			else start = mid+1;
		}
		return start;
	}
	
	int count(long long n, long long a, long long b, long long c) {
		long long x = 0;
		// inclusion/exclusion principle
		x += (n / a) + (n / b) + (n / c);
		x -= n / lcm(a,b);
		x -= n / lcm(a,c);
		x -= n / lcm(b,c);
		x += n / lcm(a, lcm(b,c));
		return (int)x;
	}
	
	long long lcm(long long a, long long b) {
		return (a*b) / __gcd(a,b);
	}
};