/*
https://leetcode.com/problems/remove-duplicate-letters/

Given a string s, remove duplicate letters so that every letter appears once and only once. You must make sure your result is the smallest in lexicographical order among all possible results.

Example 1:

Input: s = "bcabc"
Output: "abc"
Example 2:

Input: s = "cbacdcbc"
Output: "acdb"
*/

class Solution {
public:
	string removeDuplicateLetters(string s) {
		int freq[256] = {0};
		bool vis[256] = {false};
		for (auto c: s)
			freq[c]++;

		string ans = "0";
		for (auto c: s) {
			freq[c]--;
			if (vis[c]) continue;
			while (c<ans.back() and freq[ans.back()]>0) {
				vis[ans.back()] = false;
				ans.pop_back();
			}
			ans.push_back(c);
			vis[c] = true;
		}

		return ans.substr(1);
	}
};