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





/*
Instead of adding '(' or ')' every time as in Approach 1,
let's only add them when we know it will remain a valid sequence.
We can do this by keeping track of the number of opening and closing brackets we have placed so far.

We can start an opening bracket if we still have one (of n) left to place.
And we can start a closing bracket if it would not exceed the number of opening brackets.
*/
class Solution {
	vector<string> ans;
public:
	vector<string> generateParenthesis(int n) {
		generate("", 0, 0, n);
		return ans;
	}
	
	void generate(string s, int open, int close, int max) {
		if (s.size() == 2 * max) ans.push_back(s);
		
		if (open < max) generate(s+"(", open+1, close, max);
		if (close < open) generate(s+")", open, close+1, max);
	}
};