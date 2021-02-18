// https://leetcode.com/problems/reverse-words-in-a-string/

/*
Given an input string s, reverse the order of the words.

A word is defined as a sequence of non-space characters.
The words in s will be separated by at least one space.

Return a string of the words in reverse order concatenated by a single space.

Note that s may contain leading or trailing spaces or multiple spaces between two words.
The returned string should only have a single space separating the words. Do not include any extra spaces.

Example 1:

Input: s = "the sky is blue"
Output: "blue is sky the"
Example 2:

Input: s = "  hello world  "
Output: "world hello"
Explanation: Your reversed string should not contain leading or trailing spaces.
*/


class Solution {
public:
	string reverseWords(string& t) {
		// trim spaces while copying original string
		string s;
		for (char c : t) {
			if (isspace(c)) {
				if (!s.empty() && !isspace(s.back()))
					s.push_back(c);
			}
			else s.push_back(c);
		}
		if (isspace(s.back())) s.pop_back();
		
		reverse(s.begin(), s.end());
		for (int i=0, j=0; j < s.size(); ) {
			while (j<s.size() && !isspace(s[j])) j++;
			reverse(s.begin()+i, s.begin()+j);
			i = j = j+1;
		}
		return s;
	}
};
