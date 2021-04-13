// https://leetcode.com/problems/verifying-an-alien-dictionary/

/*
In an alien language, surprisingly they also use english lowercase letters, but possibly in a different order.
The order of the alphabet is some permutation of lowercase letters.
Given a sequence of words written in the alien language, and the order of the alphabet,
return true if and only if the given words are sorted lexicographicaly in this alien language.

Example 1:

Input: words = ["hello","leetcode"], order = "hlabcdefgijkmnopqrstuvwxyz"
Output: true
Explanation: As 'h' comes before 'l' in this language, then the sequence is sorted.
*/

class Solution {
	int min(int a, int b) {
		return a<b ? a : b;
	}
public:
	bool isAlienSorted(vector<string>& words, string o) {
		int order[128] = {};
		for (int i=0; i<26; i++)
			order[o[i]] = i;

		for (int i=1; i < words.size(); i++) {
			auto& w1 = words[i-1]; auto& w2 = words[i];
			bool correct = true; int j=0;
			for (; j < min(w1.size(), w2.size()); j++) {
				if (order[w1[j]] == order[w2[j]]) continue;
				if (order[w1[j]] > order[w2[j]]) correct = false;
				break;
			}
			if (j == w2.size() && w2.size() < w1.size()) correct = false;
			if (!correct) return false;
		}

		return true;
	}
};