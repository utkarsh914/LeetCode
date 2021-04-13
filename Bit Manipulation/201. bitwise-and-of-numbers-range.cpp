// https://leetcode.com/problems/bitwise-and-of-numbers-range/

/*
Given two integers left and right that represent the range [left, right],
return the bitwise AND of all numbers in this range, inclusive.

Example 1:

Input: left = 5, right = 7
Output: 4
*/

class Solution {
public:
	int rangeBitwiseAnd(int left, int right) {
		int n = 0, i = 0;
		while (left && right) {
			/*
			cur bit can never be 1 if both nums are different. In this case,
			one of them has to be even. And if any even num is in the range,
			AND bit will be 0.

			cur bit can only be one when left==right and left/right is odd
			*/
			int bit = (left == right && left&1 != 0) ? 1 : 0;
			n |= (bit << i);
			left = left >> 1;
			right = right >> 1;
			i++;
		}
		
		return n;
	}
};