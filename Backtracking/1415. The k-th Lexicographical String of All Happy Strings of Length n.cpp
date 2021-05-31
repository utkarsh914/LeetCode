// https://leetcode.com/problems/the-k-th-lexicographical-string-of-all-happy-strings-of-length-n/

class Solution {
public:
	string getHappyString(int n, int k) {
		vector<string> ans;
		string s;
		backtrack(n, ans, s);
		nth_element(ans.begin(), ans.begin()+k-1, ans.end());
		return k <= ans.size() ? ans[k-1] : "";
	}

	void backtrack(int n, vector<string>& ans, string& s) {
		if (s.length() == n) {
			ans.push_back(s);
			return;
		}
		for (char& ch : string("abc")) {
			if (s.empty() or s.back() != ch) {
				s.push_back(ch);
				backtrack(n, ans, s);
				s.pop_back();
			}
		}
	}
};