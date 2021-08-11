// https://leetcode.com/problems/basic-calculator/


/*
Keep a global running total and a stack of signs (+1 or -1), one for each open scope.
The "global" outermost sign is +1.

Each number consumes a sign.
Each + and - causes a new sign.
Each ( duplicates the current sign so it can be used for the first term inside the new scope.
That's also why I start with [1, 1] - the global sign 1 and a duplicate to be used for the first term,
since expressions start like 3... or (..., not like +3... or +(....
Each ) closes the current scope and thus drops the current sign.
*/
int calculate(string s) {
	int total = 0;
	vector<int> signs(2, 1);
	for (int i=0; i<s.size(); i++) {
		char c = s[i];
		if (c >= '0') {
			int number = 0;
			while (i < s.size()  &&  s[i] >= '0')
				number = 10 * number + (s[i++] - '0');
			total += signs.back() * number;
			signs.pop_back();
			i--;
		}
		else if (c == ')')
			signs.pop_back();
		else if (c != ' ')
			signs.push_back(signs.back() * (c == '-' ? -1 : 1));
	}
	return total;
}
/*
Here's an example trace for input 3-(2+(9-4)).

  remaining   sign stack      total
3-(2+(9-4))   [1, 1]            0
 -(2+(9-4))   [1]               3
  (2+(9-4))   [1, -1]           3
   2+(9-4))   [1, -1, -1]       3
    +(9-4))   [1, -1]           1
     (9-4))   [1, -1, -1]       1
      9-4))   [1, -1, -1, -1]   1
       -4))   [1, -1, -1]      -8
        4))   [1, -1, -1, 1]   -8
         ))   [1, -1, -1]      -4
          )   [1, -1]          -4
              [1]              -4
*/







class Solution {
public:
	int calculate(string s) {
		stack<int> operandStack;
		int operand = 0;
		int result = 0;
		int sign = 1;
		
		for (auto ch: s) {
			/* Form operand since it can have multiple digits */
			if (isdigit(ch)) {
				operand = 10 * operand + (int) (ch - '0');
			}
			else if (ch == '+' || ch == '-') {
				result += sign * operand;
				sign = ch == '+' ? 1 : -1;
				operand = 0;
			}
			else if (ch == '(') {
				operandStack.push(result);
				operandStack.push(sign);
				
				sign = 1;
				result = 0;
			}
			else if (ch == ')') {
				result += sign * operand;
				result *= operandStack.top();
				operandStack.pop();
				result += operandStack.top();
				operandStack.pop();
				operand = 0;
			}
		}
		
		return result + (sign * operand);
	}
};








// calculate postfix, then evaluate it
class Solution {
public:
	int calculate(string& str) {
		vector<string> post = postfix(str);
		int ans = evaluatePostfix(post);
		return ans;
	}

	vector<string> postfix(string& str) {
		vector<string> post;
		stack<string> s;

		// convert to postfix
		for (int i=0; i < str.size(); ) {
			char c = str[i++];
			if (isspace(c)) continue;

			if (isdigit(c)) {
				string n(1, c);
				while (i < str.size() && isdigit(str[i]))
					n.push_back(str[i++]);
				post.push_back(n);
			}
			else if (c == '(') {
				s.push(string(1, c));
				// to handle cases like (-3 + 4)
				// consider - sign with 3 in this case. i.e. "-3"
				// if - comes after any number, it is treated as an operator
				if (i < str.size() && str[i] == '-') {
					string n(1, str[i++]);
					while (i < str.size() && isdigit(str[i]))
						n.push_back(str[i++]);
					post.push_back(n);
				}
			}
			else if (c == '+' or c == '-') {
				while (!s.empty() && s.top() == "-") {
					post.push_back(s.top());
					s.pop();
				}
				s.push(string(1, c));
			}
			else {
				while (!s.empty() && s.top() != "(") {
					post.push_back(s.top());
					s.pop();
				}
				s.pop();
			}
		}

		while (!s.empty()) {
			post.push_back(s.top());
			s.pop();
		}

		// for (auto p : post) cout << p << ", ";
		return post;
	}

	int evaluatePostfix(vector<string>& post) {
		stack<int> s;
		for (string& p : post) {
			if (p == "+" || p == "-") {
				int x = 0, y = 0;
				if (!s.empty()) x = s.top(), s.pop();
				if (!s.empty()) y = s.top(), s.pop();
				int z = p == "+" ? y+x : y-x;
				s.push(z);
			}
			else {
				s.push(stoi(p));
			}
		}
		return s.top();
	}
};