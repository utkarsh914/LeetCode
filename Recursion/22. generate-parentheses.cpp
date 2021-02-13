/*
https://leetcode.com/problems/generate-parentheses/

Given n pairs of parentheses, write a function to generate all combinations of well-formed parentheses.

 

Example 1:

Input: n = 3
Output: ["((()))","(()())","(())()","()(())","()()()"]
Example 2:

Input: n = 1
Output: ["()"]
 

Constraints:

1 <= n <= 8
*/

class Solution {
public:
	vector<string> generateParenthesis(int n) {
		vector<string> result;
		helper(result, "", n, n);
		return result;
	}
	void helper(vector<string>& result, string str, int left, int right) {
		if (left==0 and right==0) {
			result.push_back(str);
			return;
		}
		if (left > 0) helper(result, str+"(", left-1, right);
		if (right > left) helper(result, str+")", left, right-1);
	}
};