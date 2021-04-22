// https://leetcode.com/problems/number-of-substrings-with-only-1s/

/*
Given a binary string s (a string consisting only of '0' and '1's).
Return the number of substrings with all characters 1's.
Since the answer may be too large, return it modulo 10^9 + 7.

Example 1:

Input: s = "0110111"
Output: 9
Explanation: There are 9 substring in total with only 1's characters.
"1" -> 5 times.
"11" -> 3 times.
"111" -> 1 time.
*/




// count groups of 1's
// group of length g has (g*(g+1))/2 substrings
class Solution {
public:
	int numSub(string& s) {
		long count = 0, m = 1e9+7, g = 0;
		for (char& c : s) {
			if (c == '0') {
				count = (count + (g*(g+1))/2) % m;
				g = 0;
			}
			else g++;
		}
		count = (count + (g*(g+1))/2) % m;
		return count;
	}
};



	int numSub(string s) {
		int res = 0, count = 0, mod = 1e9 + 7;
		for (char c: s) {
			count = c == '1' ? count + 1 : 0;
			res = (res + count) % mod;
		}
		return res;
	}