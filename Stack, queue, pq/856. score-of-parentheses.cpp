// https://leetcode.com/problems/score-of-parentheses/

// similar: LC-1190 reverse-substrings-between-each-pair-of-parentheses

/*
Given a balanced parentheses string S, compute the score of the string based on the following rule:

() has score 1
AB has score A + B, where A and B are balanced parentheses strings.
(A) has score 2 * A, where A is a balanced parentheses string.
 

Example 1:

Input: "()"
Output: 1
Example 2:

Input: "(())"
Output: 2
Example 3:

Input: "()()"
Output: 2
Example 4:

Input: "(()(()))"
Output: 6
*/



/*
because here you only have positive integers, so -1 or even 0 could be marked as '('
so the stack contains either 0, which is '(' or a positive number which represents a valid balanced pair
(()()) -> 0 1 1 before we visit last )
The final sum is for situations like ()() -> 1 1 in stack
*/
class Solution {
public:
	int scoreOfParentheses(string& str) {
		stack<int> s;

		for (char c: str) {
			if (c == '(') {
				s.push(-1);
			} else {
				int curr = 0;
				while (s.top() != -1) {
					curr += s.top(); s.pop();
				}
				s.pop();
				s.push(curr==0 ? 1 : 2*curr);
			}
		}

		int score = 0;
		while (!s.empty()) {
			score += s.top(); s.pop();
		}
		return score;
	}
};



// same concept as above, shorter
class Solution {
public:
	int scoreOfParentheses(string& str) {
		vector<int> s = {0};

		for (char c: str) {
			if (c == '(') {
				s.push_back(0);
			} else {
				int curr = s.back(); s.pop_back();
				*s.rbegin() += (curr==0) ? 1 : 2*curr;
			}
		}

		return s[0];
	}
};

/*
When we see "(" character, we are entering new valid paranthesis cluster, so we append initalized value 0 to stack.
When we see ")" character, we should process currently open valid paranthesis cluster(Stack.pop()).
If valid paranthesis cluster is still valued 0, it is a valid empty paranthesis cluster, so value is 1.
Otherwise multiply inside value by 2. Add processed value to outer valid paranthesis cluster(Stack[-1])
*/







/*
********* Approach 2: O(1) Space *********
We count the number of layers.
If we meet '(' layers number l++
else we meet ')' layers number l--

If we meet "()", we know the number of layer outside,
so we can calculate the score res += 1 << l

in a nutshell, only () makes up the score depending on how deep it is
*/
class Solution {
public:
	int scoreOfParentheses(string& s) {
		int score = 0, depth = 0;

		for (int i=0; i<s.length(); i++) {
			if (s[i] == '(') depth++;
			else depth--;
			if (i>0 && s[i-1]=='(' && s[i]==')')
				score += 1<<depth; // met a '()'
		}

		return score;
	}
};


/*
A deeper understanding of the idea above. (also for people who found approach 2 hard to get)

It just occurs to me the input can be treated as a tree. Every () is a tree node. ()() can be treated as two sibling nodes while (()) can be treated as a parent and a child node. Each leaf node has value 1 while non-leaf node has double the value of all of its direct children's value. All we have to do is to calculate the root node value via post-order traverse. And this is exactly what the approach 1 did as it always get the value of deeper layers before gets its' own value! For example, the S = '(()(()()))' can be treated as the tree below.

                            (10)            layer 0
                            ／ \
                          (1)  (4)          layer 1
                               /  \
                             (1)  (1)       layer 2
Basically, the approach 2 is using the same idea. As you can see, the value of the root node is the sum of each leaf node value to the power of it's depth.
There are three leaf nodes in the tree. One leaf in layer 1 and two leafs in layer 2. So the final answer is 2^1 + 2^2 + 2^2 = 10.
By the way, approach 2 runs faster than approach 1 theoretically as it dose not calculate the intermediate nodes value.
*/