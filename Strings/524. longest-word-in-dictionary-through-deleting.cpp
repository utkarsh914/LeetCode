// https://leetcode.com/problems/longest-word-in-dictionary-through-deleting/

class Solution {
public:
	string findLongestWord(string& s, vector<string>& d) {
		string longest = "";
		for (string& word : d) {
			if (isSubsequence(word, s)) {
				if (word.size() < longest.size())
					continue;
				if (word.size() > longest.size() or word < longest)
					longest = word;
			}
		}
		return longest;
	}

	bool isSubsequence(string& w, string& s) {
		int len = 0;
		for (int i = 0; i < s.size(); i++)
			if (s[i] == w[len]) len++;
		return len == w.size();
	}
};