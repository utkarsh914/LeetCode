// https://leetcode.com/problems/parsing-a-boolean-expression/



// this idea came to my mind by thinking of Polish notation
class Solution {
public:
	bool parseBoolExpr(string& exp) {

		reverse(exp.begin(), exp.end());
		vector<vector<bool>> s;
		s.push_back(vector<bool> ());

		for (char c : exp) {

			vector<bool>& v = s[s.size()-1];

			if (c == ')') // ')' is treated as '(' since the string is reversed
				s.push_back(vector<bool> ());

			else if (c == 't' || c == 'f')
				v.push_back(c == 't');

			else if (c == '|' || c == '!' || c == '&') {
				bool ans = false;
				if (c == '!')
					ans = evaluate_not(v);
				else if (c == '|')
					ans = evaluate_or(v);
				else if (c == '&')
					ans = evaluate_and(v);

				s[s.size()-2].push_back(ans);
				s.pop_back();
			}

		}
		
		return s[0][0];
	}

	bool evaluate_or(vector<bool>& v) {
		bool ans = false;
		for (auto b : v)
			if (b == true) ans = true;
		return ans;
	}

	bool evaluate_and(vector<bool>& v) {
		bool ans = true;
		for (auto b : v)
			if (b == false) ans = false;
		return ans;
	}

	bool evaluate_not(vector<bool>& v) {
		return !v[0];
	}

};






/*
We can parse parentheses and recursivelly evaluate the expression. Or, since the expression is in Poslih notation, we can use a simple stack approach.

Recursive Solution
Logical AND and OR expressions are a bit tricky as they have multiple parameters, and a parameter can be an inner expression.

So, to extract parameters, we need to track the number of non-closed parentheses; when we see a comma (",") and the number of parentheses is zero, we found an entire parameter.
*/

bool parseBoolExpr(string e) {
  if (e.size() == 1) return e == "t" ? true : false;
  if (e[0] == '!') return !parseBoolExpr(e.substr(2, e.size() - 3));
  bool isAnd = e[0] == '&' ? true : false, res = isAnd;
  for (auto i = 2, j = 2, cnt = 0; res == isAnd && i < e.size(); ++i) {
    if (e[i] == '(') ++cnt;
    if (e[i] == ')') --cnt;      
    if (i == e.size() - 1 || (e[i] == ',' && cnt == 0)) {
      if (isAnd) res &= parseBoolExpr(e.substr(j, i - j));
      else res |= parseBoolExpr(e.substr(j, i - j));
      j = i + 1;
    }
  }
  return res;
}

/*
Polish Notation
Polish notation is very easy to evaluate: push everything to the stack until you get the closing group marker (')'). Then, pop values from the stack (should be just 't' and 'f' at this point) until you reach an operator ('!', '|' or '&'). Apply the operator to the values and push the result back to the stack.

Additional observations:
• We can ignore commas and open parentheses.
• We do not need to apply the operator to all parameters; we just need to know whether we have one or more 't', or one or more 'f'.
*/

bool parseBoolExpr(string e) {
  stack<char> s;
  for (auto ch : e) {
    if (ch == ')') {
      auto hasT = false, hasF = false;
      while (s.top() == 't' || s.top() == 'f') {
        hasT |= s.top() == 't';
        hasF |= s.top() == 'f';
        s.pop();
      }
      auto op = s.top();
      s.pop();
      s.push(op == '!' ? hasF ? 't' : 'f' : op == '&' ? !hasF ? 't' : 'f' : hasT ? 't' : 'f');
    }
    else if (ch != ',' && ch != '(') s.push(ch);
  }
  return s.top() == 't' ? true : false;
}