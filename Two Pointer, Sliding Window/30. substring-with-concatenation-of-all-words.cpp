// https://leetcode.com/problems/substring-with-concatenation-of-all-words/

/*
You are given a string s and an array of strings words of the same length.
Return all starting indices of substring(s) in s that is a concatenation of each word in words
exactly once, in any order, and without any intervening characters.

You can return the answer in any order.

 

Example 1:

Input: s = "barfoothefoobarman", words = ["foo","bar"]
Output: [0,9]
Explanation: Substrings starting at index 0 and 9 are "barfoo" and "foobar" respectively.
The output order does not matter, returning [9,0] is fine too.
*/



/*
We use an unordered_map<string, int> counts to record the expected times of each word
and another unordered_map<string, int> seen to record the times we have seen.
Then we check for every possible position of i.
Once we meet an unexpected word or the times of some word is larger than its expected times,
we stop the check. If we finish the check successfully, push i to the result indexes.
*/
class Solution {
public:
	vector<int> findSubstring(string s, vector<string>& words) {
		vector<int> indices;
		int n = s.length(), num = words.size();
		if (n == 0 || num == 0) return indices;
		int len = words[0].length();

		unordered_map<string, int> dict;
		for (string word : words)	dict[word]++;

		for (int i = 0; i < n - num * len + 1; i++) {

			unordered_map<string, int> seen;
			int j = 0;

			for (; j < num; j++) {
				string word = s.substr(i + j * len, len);
				if (dict.count(word)) {
					seen[word]++;
					if (seen[word] > dict[word])
						break;
				}
				else break;
			}

			if (j == num) indices.push_back(i);
		}

		return indices;
	}
};
