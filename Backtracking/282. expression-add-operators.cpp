// https://leetcode.com/problems/expression-add-operators/

/*
Given a string that contains only digits 0-9 and a target value,
return all possibilities to add binary operators (not unary) +, -, or * between the digits
so they evaluate to the target value.

Example 1:

Input: num = "123", target = 6
Output: ["1+2+3", "1*2*3"] 
Example 2:

Input: num = "232", target = 8
Output: ["2*3+2", "2+3*2"]
*/

class Solution {
	vector<string> ans;
public:
	vector<string> addOperators(string& n, int target) {
		dfs(n, "", 0, target, 0, 0);
		return ans;
	}
	// cv = current val, pv = prev value
	void dfs(string& n, string cur, int start, int target, long cv, long pv) {
		if (start == n.size())
			if (cv == target) ans.push_back(cur);

		for (int i=1; start+i <= n.size(); i++) {
			string temp = n.substr(start, i); // pick a substr of i length from start
			if (i>1 && temp[0]=='0') continue;// to deal extra zeroes. ex: "005" should be just "5"
			long num = stol(temp);

			if (start == 0) {
				dfs(n, temp, i, target, num, num);
				continue;
			}
			dfs(n, cur + "+" + temp, start+i, target, cv+num, num);
			dfs(n, cur + "-" + temp, start+i, target, cv-num, -num);
			dfs(n, cur + "*" + temp, start+i, target, cv-pv+pv*num, pv*num);
		}
	}
};

/*
Now we have 4 different recursion paths in our algorithm and we have to try out all of them to see which ones lead to a potential solution.

This try out everything hints at a backtracking solution and that is exactly what we are going to look at here.

Algorithm

Let's quickly look at the steps involved in our backtracking algorithm before looking at the pseudo-code.

As discussed above, we have multiple choices of what operators to use and what the operands can be and hence, we have to look at all the possibilities to find all valid expressions.
Our recursive call will have an index which represents the current digit we're looking at in the original nums string and also the expression string built till now.
At every step, we have exactly 4 different recursive calls. The NO OP call simply extends the current_operand by the current digit and moves ahead. Rest of the recursive calls correspond to +, -, and *.
We keep on building our expression like this and eventually, the entire nums string would be processed. At that time we check if the expression we built till now is a valid expression or not and we record it if it is a valid one.

1. procedure recurse(digits, index, expression):
2.     if we have reached the end of the string:
3.         if the expression evaluates to the target:
4.             Valid Expression found!
5.     else:
6.         try out operator 'NO OP' and recurse
7.         try out operator * and recurse
8.         try out operator + and recurse
9.         try out operator - and recurse

The algorithm now looks pretty straightforward. However, the implementation is something that needs more thought and there are some things that we need to address before actually looking at the implementation.
*/






/*
class Solution {
	string cur;
	vector<string> ans;
public:
	vector<string> addOperators(string& n, int target) {
		backtrack(n, 0, target);
		return ans;
	}
	
	void backtrack(string& n, int start, int target) {
		if (start == n.size()) {
			if (countDigits(cur) == n.size() and evaluate(cur) == target)
				ans.push_back(cur);
			// cout << cur << "=" << evaluate(cur) << " ";
		}
		// cout << cur << " ";
		
		for (int i=start; i < n.size(); i++) {
			// if (cur.size()==1 && cur[0]=='0')
			//	 cur.pop_back();
			cur.push_back(n[i]);
			backtrack(n, i+1, target);
			
			if (i != n.size()-1) {
				cur.push_back('+');
				backtrack(n, i+1, target);
				cur.pop_back();

				cur.push_back('-');
				backtrack(n, i+1, target);
				cur.pop_back();

				cur.push_back('*');
				backtrack(n, i+1, target);
				cur.pop_back();
			}
			
			cur.pop_back();
		}
	}
	
	int evaluate(string& s) {
		stringstream ss("+" + s);
		char op;
		long long n, last, ans = 0;
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
	
	int countDigits(string& cur) {
		int count = 0;
		for (char c : cur) count += isdigit(c);
		return count;
	}
};

*/