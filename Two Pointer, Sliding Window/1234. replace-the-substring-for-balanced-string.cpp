// https://leetcode.com/problems/replace-the-substring-for-balanced-string/

/*
You are given a string containing only 4 kinds of characters 'Q', 'W', 'E' and 'R'.

A string is said to be balanced if each of its characters appears n/4 times where n is the length of the string.

Return the minimum length of the substring that can be replaced with any other string
of the same length to make the original string s balanced.
Return 0 if the string is already balanced.

Example 1:

Input: s = "QWER"
Output: 0
Explanation: s is already balanced.
Example 2:

Input: s = "QQWE"
Output: 1
Explanation: We need to replace a 'Q' to 'R', so that "RQWE" (or "QRWE") is balanced.
*/

class Solution {
public:
	int balancedString(string& s) {
		int f[128] = {};
		for (char c : s) f[c]++;

		int start = 0, end = 0, size = s.size(), k = size/4, ans = size;
		while (end < size) {
			// add start char to window(reduce its freq), and increment start
			f[s[end]]--, end++;
			// shrink the window while all outside chars have freq <= k
			while (start <= end && f['Q']<=k && f['W']<=k && f['E']<=k && f['R']<=k) {
				ans = min( ans, end - start); // update min length
				f[s[start++]] += 1; // remove the char from window (inc its freq for outside)
			}
		}

		return ans;
	}
};