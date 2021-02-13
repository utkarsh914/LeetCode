/*
https://leetcode.com/problems/word-break-ii/

Given a non-empty string s and a dictionary wordDict containing a list of non-empty words,
add spaces in s to construct a sentence where each word is a valid dictionary word.
Return all such possible sentences.

Note:
The same word in the dictionary may be reused multiple times in the segmentation.
You may assume the dictionary does not contain duplicate words.

Example 1:
Input:
s = "catsanddog"
wordDict = ["cat", "cats", "and", "sand", "dog"]
Output:
[
  "cats and dog",
  "cat sand dog"
]
*/


// *********** BACKTRACKING W DP **************
// *************** (FASTER) *******************
class Solution {
public:
	unordered_map<int, vector<string>> dp;

	vector<string> wordBreak(string s, vector<string>& wordDict) {
		unordered_set<string> dict(wordDict.begin(), wordDict.end());
		return backtrack(s, dict, 0);
		return dp[0];
	}

	vector<string> backtrack(string& s, unordered_set<string>& dict, int start) {
		if (dp.count(start)) return dp[start];
		vector<string> result;
		if (start == s.length()) {
			result.push_back(" ");
			return result;
		}
		string temp = "";
		for (int i=start; i<s.length(); i++) {
			temp.push_back(s[i]);
			if (!dict.count(temp)) continue;
			vector<string> furtherResult = backtrack(s, dict, i+1);
			for (auto j:furtherResult)
				result.push_back((j==" ") ? temp : temp + " " + j);
		}
		return dp[start]=result;
	}
};



// *********** BACKTRACKING W/O DP ************
// **************** (SLOWER) ******************
class Solution {
public:
	vector<string> result;
	string curr;

	vector<string> wordBreak(string s, vector<string>& wordDict) {
		unordered_set<string> dict(wordDict.begin(), wordDict.end());
		backtrack(s, dict, 0);
		return result;
	}

	void backtrack(string& s, unordered_set<string>& dict, int start) {
		if (start == s.length())
			result.push_back(curr.substr(1));
		for (int i=start; i<s.length(); i++) {
			string temp = s.substr(start, i-start+1);
			if (!dict.count(temp))
				continue;
			curr += " " + temp;
			backtrack(s, dict, i+1);
			for (int j=0; j<temp.length()+1; j++)
				curr.pop_back();
		}
	}
};