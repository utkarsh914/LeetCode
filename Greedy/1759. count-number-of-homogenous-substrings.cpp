// https://leetcode.com/problems/count-number-of-homogenous-substrings/

/*
Given a string s, return the number of homogenous substrings of s.
Since the answer may be too large, return it modulo 1e9 + 7.
A string is homogenous if all the characters of the string are the same.
A substring is a contiguous sequence of characters within a string.

Example 1:

Input: s = "abbcccaa"
Output: 13
Explanation: The homogenous substrings are listed as below:
"a"   appears 3 times.
"aa"  appears 1 time.
"b"   appears 2 times.
"bb"  appears 1 time.
"c"   appears 3 times.
"cc"  appears 2 times.
"ccc" appears 1 time.
3 + 1 + 2 + 1 + 3 + 2 + 1 = 13.
*/


class Solution {
public:
	int countHomogenous(string& s) {
		// g -> contiguous group size of same characters
		// no. of substrings possible fom group of size g = (g*(g+1))/2
		long long c = 0, g = 1, m = 1e9+7;
		for (int i=1; i < s.size(); i++) {
			if (s[i]==s[i-1]) g++;
			// if a mismatch is found, reset grp to 1, and calculate no. of
			// substrings for previous group size
			else {
				c = (c + (g*(g+1))/2) % m;
				g = 1;
			}
		}
		// for last group size
		c = (c + (g*(g+1))/2) % m;
		return c;
	}
};