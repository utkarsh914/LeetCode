// https://leetcode.com/problems/longest-substring-without-repeating-characters/

/*
Given a string s, find the length of the longest substring without repeating characters.

Example 1:

Input: s = "abcabcbb"
Output: 3
Explanation: The answer is "abc", with the length of 3.
*/

class Solution {
public:
	int lengthOfLongestSubstring(string& s) {
		int maxL = 0, unique = 0;
		vector<int> f(128, 0);

		for (int r = 0, l = 0; r < s.size(); r++) {
			// add cur character to window
			if (++f[s[r]] == 1) unique++;
			// remove characters from back until all chars are unique
			while (r-l+1 > unique) {
				if (--f[s[l]] == 0) unique--;
				l++;
			}
			// update max length
			maxL = max(maxL, r-l+1);
		}

		return maxL;
	}
};







class Solution {
public:
	int lengthOfLongestSubstring(string s) {
		unordered_set<char> st;
		int l = 0, i = 0, j = 0;
		
		while (j < s.length()) {
			while (st.count(s[j])) {
				st.erase(s[i++]);
			}
			st.insert(s[j++]);
			l = max(l, st.size());
		}

		return l;
	}
};