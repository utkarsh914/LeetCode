// https://leetcode.com/problems/find-and-replace-pattern/

/*
Given a list of strings words and a string pattern, return a list of words[i] that match pattern. You may return the answer in any order.

A word matches the pattern if there exists a permutation of letters p so that after replacing every letter x in the pattern with p(x), we get the desired word.

Recall that a permutation of letters is a bijection from letters to letters: every letter maps to another letter, and no two letters map to the same letter.

 

Example 1:

Input: words = ["abc","deq","mee","aqq","dkd","ccc"], pattern = "abb"
Output: ["mee","aqq"]
Explanation: "mee" matches the pattern because there is a permutation {a -> m, b -> e, ...}. 
"ccc" does not match the pattern because {a -> c, b -> c, ...} is not a permutation, since a and b map to the same letter.
*/






class Solution {
public:
	vector<string> findAndReplacePattern(vector<string>& words, string& pattern) {
		vector<string> ans;
		for (auto& w : words) {
			if (matches(w, pattern))
				ans.push_back(w);
		}
		return ans;
	}

	bool matches(string& s, string& p) {
		unordered_map<char, char> m;
		for (int i = 0; i < p.size(); i++) {
			bool exists = m.count(p[i]);
			if (exists and m[p[i]] != s[i])
				return false;
			m[p[i]] = s[i];
		}
		return true;
	}
};



// Normalise a string to a standard pattern.

class Solution {
public:
	vector<string> findAndReplacePattern(vector<string>& words, string& p) {
		vector<string> ans;
		p = normalize(p);
		for (string& w : words)
			if (normalize(w) == p)
				ans.push_back(w);
		return ans;
	}

	string normalize(string w) {
		unordered_map<char, int> m;

		for (char& c : w)
			if (!m.count(c)) m[c] = m.size();

		for (int i = 0; i < w.length(); ++i)
			w[i] = 'a' + m[w[i]];

		return w;
	}
};