// https://leetcode.com/problems/evaluate-reverse-polish-notation/

class Solution {
public:
	int evalRPN(vector<string>& tokens) {
		vector<int> s{0};
		string ops = "+-*/";
		
		for (string& t : tokens) {
			if (ops.find(t) == string::npos) {
				s.push_back(stoi(t));
				continue;
			}

			int l = s.size();
			int x = s[l-2], y = s[l-1];
			s.resize(l-2);
			
			if (t == "+") s.push_back(x + y);
			else if (t == "-") s.push_back(x - y);
			else if (t == "*") s.push_back(x * y);
			else if (t == "/") s.push_back(x / y);
		}

		return s.back();
	}
};




class Solution {
public:
	int evalRPN(vector<string>& tokens) {
		unordered_map<string, function<int (int, int) > > map = {
			{ "+" , [] (int a, int b) { return a + b; } },
			{ "-" , [] (int a, int b) { return a - b; } },
			{ "*" , [] (int a, int b) { return a * b; } },
			{ "/" , [] (int a, int b) { return a / b; } }
		};

		std::stack<int> stack;

		for (string& s : tokens) {
			if (!map.count(s)) {
				stack.push(stoi(s));
			} else {
				int op1 = stack.top(); stack.pop();
				int op2 = stack.top(); stack.pop();
				stack.push(map[s](op2, op1));
			}
		}

		return stack.top();
	}
};