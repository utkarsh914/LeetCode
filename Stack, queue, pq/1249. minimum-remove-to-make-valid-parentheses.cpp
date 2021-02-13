// https://leetcode.com/problems/minimum-remove-to-make-valid-parentheses/

class Solution {
public:
	string minRemoveToMakeValid(string& s) {
		vector<int> stk;
		for (int i=0; i<s.length(); i++) {
			if (isalpha(s[i])) continue;
			if (s[i]=='(') stk.push_back(i);
			else {
				if (!stk.empty()) stk.pop_back();
				else s[i]='#';
			}
		}
		for (int i:stk) s[i]='#';
		
		string ans; ans.reserve(s.length());
		for (int i=0; i<s.length(); i++) {
			if (s[i]!='#') ans.push_back(s[i]);
		}
		return ans;
	}
};