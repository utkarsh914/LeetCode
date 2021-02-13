// https://leetcode.com/problems/longest-valid-parentheses/
/*
Input: s = "(()"
Output: 2
Explanation: The longest valid parentheses substring is "()".
Example 2:

Input: s = ")()())"
Output: 4
Explanation: The longest valid parentheses substring is "()()".
Example 3:

Input: s = ""
Output: 0
*/

class Solution {
public:
	int longestValidParentheses(string s);
};

int Solution::longestValidParentheses(string s) {
	stack<int> stk;
	int left=-1, len=0;
	for (int i=0; i<s.length(); i++) {
		if (s[i]=='(') stk.push(i);
		else if (stk.empty()) left = i;
		else {
			stk.pop();
			if (stk.empty()) len = max(len, i-left);
			else len = max(len, i-stk.top());
		}
	}
	return len;
}