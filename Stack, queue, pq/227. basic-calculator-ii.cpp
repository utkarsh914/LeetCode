// https://leetcode.com/problems/basic-calculator-ii/

/*
Given a string s which represents an expression, evaluate this expression and return its value. 

The integer division should truncate toward zero.

Note: You are not allowed to use any built-in function which evaluates strings as mathematical expressions, such as eval().

 

Example 1:

Input: s = "3+2*2"
Output: 7
Example 2:

Input: s = " 3/2 "
Output: 1
Example 3:

Input: s = " 3+5 / 2 "
Output: 5
 

Constraints:

1 <= s.length <= 3 * 105
s consists of integers and operators ('+', '-', '*', '/') separated by some number of spaces.
s represents a valid expression.
All the integers in the expression are non-negative integers in the range [0, 231 - 1].
The answer is guaranteed to fit in a 32-bit integer.
*/






int calculate(string& s) {
	stringstream ss("+" + s);
	char op;
	int n, last, ans = 0;
	while (ss >> op >> n) {
		if (op == '+' or op == '-') {
			n = op == '+' ? n : -n;
			ans += n;
		} else {
			n = op == '*' ? last * n : last / n;
			ans = ans - last + n; // simulate a stack by recovering last values
		}
		last = n;
	}

	return ans;
}


/*
	def calculate(self, s):
		s += '+0'
		stack, num, preOp = [], 0, "+"
		for i in range(len(s)):
			if s[i].isdigit(): num = num * 10 + int(s[i])
			elif not s[i].isspace():
				if   preOp == "-":  stack.append(-num)
				elif preOp == "+":  stack.append(num)
				elif preOp == "*":  stack.append(stack.pop() * num)
				else:			   stack.append(int(stack.pop() / num))
				preOp, num = s[i], 0
		return sum(stack)
*/




class Solution {
public:
	int calculate(string& s) {

		int size = s.size();
		int val = 0; char sym = '+';
		s += '+';

		for (int i = 0; i < size; ) {
			skipSpaces(s, i); // skip spaces
			int n = extractNumber(s, i);
			skipSpaces(s, i); // skip spaces
			// deal with '/' and '*'
			while (i < size and (s[i] == '*' or s[i] == '/')) {
				char curSym = s[i++];
				skipSpaces(s, i); // skip spaces
				int curN = extractNumber(s, i);
				if (curSym == '/') n /= curN;
				else n *= curN;
			}
			skipSpaces(s, i); // skip spaces
			if (sym == '+') val += n;
			else if (sym == '-') val -= n;
			sym = s[i++];
		}

		return val;
	}
	
	inline void skipSpaces(string& s, int& i) {
		while (i < s.size() and isspace(s[i])) i++;
	}
	
	inline int extractNumber(string& s, int& i) {
		int n = 0;
		while (i < s.size() and isdigit(s[i]))
			n = n * 10 + (s[i++] - '0');
		return n;
	}
};








class Solution {
public:
	int calculate(string s) {
		vector<string> stk;
		string prev;
		
		for (int i=0; i<s.length(); i++) {
			if (s[i]==' ')
				continue;
			if (isdigit(s[i])) {
				prev.push_back(s[i]);
			}
			else if (s[i]=='+' or s[i]=='-'){
				stk.push_back(prev);
				stk.push_back(string(1, s[i]));
				prev = "";
			}
			else { // * or / came
				int a = stoi(prev);
				int b = 0;
				char op = s[i];
				int j=i+1;
				while (isspace(s[j])) j++;
				while (j<s.length() && isdigit(s[j]))
					b = b*10 + s[j] - '0', j++;
				i=j-1;
				prev = to_string(op=='*' ? a*b : a/b);
			}
		}
		
		stk.push_back(prev);
		
		if (!prev.size())
			return 0;
		
		int ans = stoi(stk[0]);
		for (int i=2; i<stk.size(); i+=2) {
			int n = stoi(stk[i]);
			if (stk[i-1] == "-") n = -n;
			ans += n;
		}
		return ans;
	}
};