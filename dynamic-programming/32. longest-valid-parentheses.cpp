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




/*
A less tricky and straight forward version. Just mark the positions where the braces are valid and then calculate the longest valid...
*/

public int longestValidParentheses(String s) {
	boolean valid[] = new boolean[s.length()];

	Stack<Integer> stack = new Stack<>();
	for (int i = 0; i < s.length(); i++) {
		if (s.charAt(i) == '(') stack.push(i);
		else if (!stack.isEmpty()) {
			valid[stack.pop()] = valid[i] = true;
		}
	}

	return longest(valid);
}

private int longest(boolean[] valid) {
	int max = 0;
	int len = 0;

	for (boolean v : valid) {
		max = max(max, len = v ? len + 1 : 0);
	}

	return max;
}