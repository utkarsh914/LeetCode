/*
https://leetcode.com/problems/word-break/

Given a non-empty string s and a dictionary wordDict containing a list of non-empty words,
determine if s can be segmented into a space-separated sequence of one or more dictionary words.

Note: The same word in the dictionary may be reused multiple times in the segmentation.
You may assume the dictionary does not contain duplicate words.

Example 1:
Input: s = "leetcode", wordDict = ["leet", "code"]
Output: true
Explanation: Return true because "leetcode" can be segmented as "leet code".
*/

// *************** DP (BOTTOM-UP) **************
class Solution {
public:
	bool wordBreak(string& s, vector<string>& wordDict) {
		vector<bool> dp(s.length()+1, false);
		dp[s.length()] = true;
		unordered_set<string> dict(wordDict.begin(), wordDict.end());
		for (int i=s.length()-1; i>=0; i--) {
			string temp;
			for (int j=i; j<s.length(); j++) {
				temp.push_back(s[j]);
				if (!dict.count(temp)) continue;
				if (dp[j+1]) dp[i]=true;
			}
		}
		return dp[0];
	}
};


// *************** RECURSIVE **************
class Solution {
public:
	bool wordBreak(string& s, vector<string>& wordDict, int start=0) {
		if (start == s.length()) return true;
		string temp;
		for (int i=start; i<s.length(); i++) {
			temp.push_back(s[i]);
			if (find(wordDict.begin(), wordDict.end(), temp) == wordDict.end()) continue;
			if (wordBreak(s, wordDict, i+1)) return true;
		}
		return false;
	}
};