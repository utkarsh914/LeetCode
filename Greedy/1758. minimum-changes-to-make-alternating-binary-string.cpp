// https://leetcode.com/problems/minimum-changes-to-make-alternating-binary-string/

/*
You are given a string s consisting only of the characters '0' and '1'. In one operation, you can change any '0' to '1' or vice versa.

The string is called alternating if no two adjacent characters are equal. For example, the string "010" is alternating, while the string "0100" is not.

Return the minimum number of operations needed to make s alternating.

Example 1:
Input: s = "0100"
Output: 1
Explanation: If you change the last character to '1', s will be "0101", which is alternating.
*/


/*
* Think about how the final string will look like.
* It will either start with a '0' and be like '010101010..' or with a '1' and be like '10101010..'
* Try both ways, and check for each way, the number of changes needed to reach it from the given string.
  The answer is the minimum of both ways.
*/

class Solution {
public:
	int minOperations(string& s) {
		int c1 = 0, c2 = 0, size = s.size();

		for (int i=0; i < size; ) {
			c1 += s[i++]=='0';
			if (i < size) c1 += s[i++]=='1';
		}

		for (int i=0; i < size; ) {
			c2 += s[i++]=='1';
			if (i < size) c2 += s[i++]=='0';
		}

		return min(c1, c2);
	}
};