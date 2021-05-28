// https://leetcode.com/problems/split-array-into-fibonacci-sequence/

/*
You are given a string of digits num, such as "123456579".
We can split it into a Fibonacci-like sequence [123, 456, 579].

Formally, a Fibonacci-like sequence is a list f of non-negative integers such that:

0 <= f[i] < 231, (that is, each integer fits in a 32-bit signed integer type),
f.length >= 3, and
f[i] + f[i + 1] == f[i + 2] for all 0 <= i < f.length - 2.
Note that when splitting the string into pieces,
each piece must not have extra leading zeroes, except if the piece is the number 0 itself.

Return any Fibonacci-like sequence split from num, or return [] if it cannot be done.


Example 1:

Input: num = "123456579"
Output: [123,456,579]
*/







class Solution {
public:
	vector<int> splitIntoFibonacci(string& s) {
		vector<int> ans;
		backtrack(ans, s, 0);
		return ans;
	}

	bool backtrack(vector<int>& ans, string& s, int start) {
		
		if (start == s.size() and ans.size() >= 3) {
			return true;
		}

		for (int i = start; i < s.size(); i++) {
			// generate a number from given seq
			long num = stol(s.substr(start, i-start+1));
			int l = ans.size();
			
			if (s[start] == '0' and i > start) break; // deal with leading zero
			if (num >= INT_MAX) break;
			if (l >= 2 and num > long(ans[l-1]) + long(ans[l-2])) break;

			// add cur num to array if there are less than 3 ele in array
			// or the fibonacci condition satisfies
			if (l <= 1 or num == long(ans[l-1]) + long(ans[l-2])) {
				ans.push_back(int(num));
				// branch pruning. if one branch has found fib seq, return true to upper call
				if (backtrack(ans, s, i+1))
					return true;
				ans.pop_back();
			}
		}

		return false;
	}
};
