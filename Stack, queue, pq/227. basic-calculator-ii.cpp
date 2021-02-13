// https://leetcode.com/problems/basic-calculator-ii/


int calculate(string& s) {
	stringstream ss("+" + s);
	char op;
	int n, last, ans = 0;
	while (ss >> op >> n) {
		if (op == '+' || op == '-') {
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