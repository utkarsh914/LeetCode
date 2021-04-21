// https://leetcode.com/problems/find-kth-bit-in-nth-binary-string/

/*
Given two positive integers n and k, the binary string  Sn is formed as follows:

S1 = "0"
Si = Si-1 + "1" + reverse(invert(Si-1)) for i > 1
Where + denotes the concatenation operation, reverse(x) returns the reversed string x,
and invert(x) inverts all the bits in x (0 changes to 1 and 1 changes to 0).

For example, the first 4 strings in the above sequence are:

S1 = "0"
S2 = "011"
S3 = "0111001"
S4 = "011100110110001"
Return the kth bit in Sn. It is guaranteed that k is valid for the given n.

Example 1:

Input: n = 3, k = 1
Output: "0"
Explanation: S3 is "0111001". The first bit is "0".
*/

class Solution {
public:
	char findKthBit(int n, int k) {
		if (n == 1) return '0';
		if (k == (1 << (n-1))) return '1';
		if (k <= (1 << (n-1))) return findKthBit(n-1, k);
		char bit = findKthBit(n-1, (1 << n) - k);
		return bit == '1' ? '0' : '1';
	}
};


/*
If k is on the left part of the string, we do nothing.

If K is right in the middle, and the middle is 1.
We flip count times, we return count % 2 == 0 ? '1' : '0'

If k is on the right part of the string,
find it's symeric postion k = l + 1 - k.
Also we increment count++.

*/
char findKthBit(int n, int k) {
	int flip = 0, l = (1 << n) - 1;
	while (k > 1) {
		if (k == l / 2 + 1)
			return '0' + (flip ^ 1);
		if (k > l / 2) {
			k = l + 1 - k;
			flip ^= 1;
		}
		l /= 2;
	}
	return '0' + flip;
}