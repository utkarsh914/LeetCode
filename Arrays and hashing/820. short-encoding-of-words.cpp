// https://leetcode.com/problems/short-encoding-of-words/

/*
A valid encoding of an array of words is any reference string s and array of indices indices such that:

words.length == indices.length
The reference string s ends with the '#' character.
For each index indices[i], the substring of s starting from indices[i] and up to (but not including) the next '#' character is equal to words[i].
Given an array of words, return the length of the shortest reference string s possible of any valid encoding of words.

Example 1:

Input: words = ["time", "me", "bell"]
Output: 10
Explanation: A valid encoding would be s = "time#bell#" and indices = [0, 2, 5].
words[0] = "time", the substring of s starting from indices[0] = 0 to the next '#' is underlined in "time#bell#"
words[1] = "me", the substring of s starting from indices[1] = 2 to the next '#' is underlined in "time#bell#"
words[2] = "bell", the substring of s starting from indices[2] = 5 to the next '#' is underlined in "time#bell#"
*/

/*
the main idea is to sort words in dec size
loop throuth all words,
and if the current word is a suffix of some prev encountered word, we can skip it
otherwise count it (i.e. word.size()+1)
*/

/* using HashSet to store all suffixes of prev words*/
class Solution {
public:
	int minimumLengthEncoding(vector<string>& words) {
		sort(words.begin(), words.end(), [&](auto& w1, auto& w2) {
			return w1.size() > w2.size();
		});
		
		unordered_set<string> set;
		int c = 0;
		
		for (auto& w : words) {
			if (set.count(w)) continue;
			c += w.size() + 1;
			for (int i = 0; i < w.size(); ++i)
				set.insert(w.substr(i));
		}
		
		return c;
	}
};




/* using Trie to store all suffixes of prev words*/
class Solution {

class Trie {
	vector<Trie*> child;
public:
	Trie() { child.resize(26, NULL); }

	// returns if curr word is a suffix of any prev word
	// also inserts the cur word in trie
	bool insert(string word) {
		bool isSuffix = true;
		Trie* cur = this;
		for (char c : word) {
			if (cur->child[c-'a'] == NULL) {
				cur->child[c-'a'] = new Trie();
				isSuffix = false;
			}
			cur = cur->child[c-'a'];
		}
		return isSuffix;
	}
};

public:
	int minimumLengthEncoding(vector<string>& words) {
		sort(words.begin(), words.end(), [&](auto& w1, auto& w2) {
			return w1.size() > w2.size();
		});
		
		Trie t;
		int c = 0;
		
		for (auto& w : words) {
			reverse(w.begin(), w.end());
			if (t.insert(w) == false)
				c += w.size() + 1;
		}
		
		return c;
	}
};