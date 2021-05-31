// https://leetcode.com/problems/additive-number/

// same as: 842. Split Array into Fibonacci Sequence

class Solution {
	vector<string> cur;

public:
	bool isAdditiveNumber(string& s, int start = 0) {
		if (start == s.size() and cur.size() >= 3)
			return true;

		for (int i = start; i < s.size(); i++) {
			if (s[start] == '0' and i > start) break;
			string N = s.substr(start, i - start + 1);
			int l = cur.size();
			
			if (l <= 1 or addition(cur[l-1], cur[l-2]) == N) {
				cur.push_back(N);
				if (isAdditiveNumber(s, i+1))
					return true;
				cur.pop_back();
			}
		}

		return false;
	}

	string addition(string a, string b) {
		string ans;
		reverse(a.begin(), a.end());
		reverse(b.begin(), b.end());
		int carry = 0;
		for (int i = 0; i < a.size() or i < b.size(); i++) {
			int n1 = i < a.size() ? a[i] - '0' : 0;
			int n2 = i < b.size() ? b[i] - '0' : 0;
			ans.push_back('0' + (n1 + n2 + carry) % 10);
			carry = (n1 + n2 + carry) / 10 ;
		}
		if (carry > 0) ans.push_back('0' + carry);
		return string(ans.rbegin(), ans.rend());
	}
};