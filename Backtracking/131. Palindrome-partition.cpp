/*
https://leetcode.com/problems/palindrome-partitioning/
*/

class Solution {
public:
	vector<vector<string>> result;
	vector<string> currVec;
	vector<vector<string>> partition(string s) {
		backtrack(s, 0);
		return result;
	}

	void backtrack(string& s, int start) {
		if (start==s.length())
			result.push_back(currVec);
		for (int i=start; i<s.length(); i++) {
			// check if curr substring is palindrome
			// if palindrome, push it and backtrack on remaining part
			// then pop after backtrack done
			if (!ispalindrome(s, start, i)) continue;
			string temp = s.substr(start, i-start+1);
			currVec.push_back(temp);
			backtrack(s, i+1);
			currVec.pop_back();
		}
	}

	bool ispalindrome(string& s, int start, int end) {
		while (start < end) {
			if (s[start] != s[end]) return false;
			start++, end--;
		}
		return true;
	}
};
