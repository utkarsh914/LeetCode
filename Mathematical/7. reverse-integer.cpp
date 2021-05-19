// https://leetcode.com/problems/reverse-integer/

/*
Given a signed 32-bit integer x, return x with its digits reversed.
If reversing x causes the value to go outside the
signed 32-bit integer range [-231, 231 - 1],then return 0.
Assume the environment does not allow you to store 64-bit integers (signed or unsigned).


Example 1:

Input: x = 123
Output: 321
Example 2:

Input: x = -123
Output: -321
*/

class Solution {
public:
	int reverse(int n) {
		int sign = n < 0 ? -1 : 1;
		unsigned int x = abs(n);
		unsigned int ans = 0;
		
		while (x) {
			if (ans > INT_MAX/10 or INT_MAX - ans*10 < x % 10)
				return 0;
			ans = ans * 10 + x % 10;
			x /= 10;
		}
		
		return sign * ans;
	}
};