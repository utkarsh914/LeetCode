// https://leetcode.com/problems/remove-outermost-parentheses/

/*
A valid parentheses string is either empty (""), "(" + A + ")", or A + B, where A and B are valid parentheses strings, and + represents string concatenation.  For example, "", "()", "(())()", and "(()(()))" are all valid parentheses strings.
A valid parentheses string S is primitive if it is nonempty, and there does not exist a way to split it into S = A+B, with A and B nonempty valid parentheses strings.
Given a valid parentheses string S, consider its primitive decomposition: S = P_1 + P_2 + ... + P_k, where P_i are primitive valid parentheses strings.
Return S after removing the outermost parentheses of every primitive string in the primitive decomposition of S.

Example 1:

Input: "(()())(())"
Output: "()()()"
Explanation: 
The input string is "(()())(())", with primitive decomposition "(()())" + "(())".
After removing outer parentheses of each part, this is "()()" + "()" = "()()()".
*/

/*
count open and closed parentheses. when they equal, we found a primitive sub-string
use two pointers to point to start and end of substring
*/
class Solution {
public:
	string removeOuterParentheses(string& s) {
		string ans;
		int open=0, closed=0, start=0;

		for (int i=0; i<s.size(); i++) {
			if (s[i] == '(') open++;
			else closed++;
			if (open == closed) {
				ans += s.substr(start+1, i-start-1);
				start = i+1;
			}
		}

		return ans;
	}
};



class Solution {
public:
	string removeOuterParentheses(string& s) {
		stack<int> stk;
		for (int i=0; i<s.size(); i++) {
			if (s[i]=='(') {
				if (stk.empty()) s[i]='#';
				stk.push(i);
			} else {
				int top = stk.top(); stk.pop();
				if (s[top]=='#') s[i]='#';
			}
		}
		string ans;
		for (char c:s) if (c!='#') ans.push_back(c);
		return ans;
	}
};