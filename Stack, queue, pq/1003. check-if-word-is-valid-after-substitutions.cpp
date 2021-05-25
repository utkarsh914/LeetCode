// https://leetcode.com/problems/check-if-word-is-valid-after-substitutions/

/*
Given a string s, determine if it is valid.

A string s is valid if, starting with an empty string t = "",
you can transform t into s after performing the following operation any number of times:

Insert string "abc" into any position in t.
More formally, t becomes tleft + "abc" + tright, where t == tleft + tright.
Note that tleft and tright may be empty.
Return true if s is a valid string, otherwise, return false.

Example 1:

Input: s = "aabcbc"
Output: true
Explanation:
"" -> "abc" -> "aabcbc"
Thus, "aabcbc" is valid.
*/





/*
Solution 1.

j is read pointer and i is write pointer.
We always write s[j] to s[i].

If the last 3 characters in front of i is abc, we clean them by i -= 3.

In the end, return i == 0.

Time: O(N)
Space: O(1)
*/
class Solution {
public:
	bool isValid(string s) {
		int i = 0, N = s.size();
		for (int j = 0; j < N; ++j) {
			s[i++] = s[j];
			if (i >= 3 and s[i-3] == 'a' and s[i-2] == 'b' and s[i-1] == 'c') i -= 3;
		}
		return i == 0;
	}
};






class Solution {
public:
	bool isValid(string& s) {
		string stk;
		for (char& c : s) {
			int l = stk.length();
			if (l>=2 and stk[l-2]=='a' and stk[l-1]=='b' and c=='c')
				stk.pop_back(), stk.pop_back();
			else stk.push_back(c);
		}
		return stk.empty();
	}
};




class Solution {
public:
	bool isValid(string& s) {
		for (int i = 0 ; i < s.length(); i++) {
			if (i>=2 and s[i-2]=='a' and s[i-1]=='b' and s[i]=='c') {
				s.erase(s.begin()+i-2, s.begin()+i+1), i -= 2;
			}
		}
		return s.empty();
	}
};
