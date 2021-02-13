// https://leetcode.com/problems/reverse-substrings-between-each-pair-of-parentheses/

// similar to: 856. score-of-parentheses


/*
You are given a string s that consists of lower case English letters and brackets. 
Reverse the strings in each pair of matching parentheses, starting from the innermost one.
Your result should not contain any brackets.

Example 1:

Input: s = "(abcd)"
Output: "dcba"
Example 2:

Input: s = "(u(love)i)"
Output: "iloveu"
Explanation: The substring "love" is reversed first, then the whole string is reversed.
Example 3:

Input: s = "(ed(et(oc))el)"
Output: "leetcode"
Explanation: First, we reverse the substring "oc", then "etco", and finally, the whole string.
Example 4:

Input: s = "a(bcdefghijkl(mno)p)q"
Output: "apmnolkjihgfedcbq"
*/






class Solution {
public:
	string reverseParentheses(string& str) {
		vector<string> s = {""};

		for (char c:str) {
			if (c == '(') {
				s.push_back("");
			}
			else if (isalpha(c)) {
				(*s.rbegin()).push_back(c);
			}
			else if (c == ')') {
				string curr = s.back();
				s.pop_back();
				reverse(curr.begin(), curr.end());
				*s.rbegin() += curr;
			}
		}

		return s[0];
	}
};


// **** more efficient ******
// store positions in stack, and keep reversing the result string according to stack's values
// stack stores the index of opening bracket
	string reverseParentheses(string s) {
		vector<int> opened;
		string res;
		for (int i = 0; i < s.length(); ++i) {
			if (s[i] == '(')
				opened.push_back(res.length());
			else if (s[i] == ')') {
				int j = opened.back();
				opened.pop_back();
				reverse(res.begin() + j, res.end());
			} else {
				res += s[i];
			}
		}
		return res;
	}





// ******** O(N) time ********
/*
Solution 2: Wormholes

Explanation
In the first pass,
use a stack to find all paired parentheses,
I assume you can do this.

Now just imgine that all parentheses are wormholes.
As you can see in the diagram,
the paired parentheses are connected to each other.

image: https://assets.leetcode.com/users/lee215/image_1571315420.png

First it follows the left green arrrow,
go into the left wormhole and get out from the right wormhole.
Then it iterates the whole content between parentheses.
Finally it follows the right arrow,
go into the left wormhole,
get out from the right wormhole and finish the whole trip.

So in the second pass of our solution,
it traverses through the paired parentheses
and generate the result string res.

i is the index of current position.
d is the direction of traversing.
*/

	string reverseParentheses(string s) {
		int n = s.length();
		vector<int> opened, pair(n);
		for (int i = 0; i < n; ++i) {
			if (s[i] == '(')
				opened.push_back(i);
			if (s[i] == ')') {
				int j = opened.back();
				opened.pop_back();
				pair[i] = j;
				pair[j] = i;
			}
		}
		string res;
		for (int i = 0, d = 1; i < n; i += d) {
			if (s[i] == '(' || s[i] == ')')
				i = pair[i], d = -d;
			else
				res += s[i];
		}
		return res;
	}