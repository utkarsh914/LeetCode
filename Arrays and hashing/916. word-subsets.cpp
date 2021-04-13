// https://leetcode.com/problems/word-subsets/

/*
We are given two arrays A and B of words.  Each word is a string of lowercase letters.

Now, say that word b is a subset of word a if every letter in b occurs in a, including multiplicity.  For example, "wrr" is a subset of "warrior", but is not a subset of "world".

Now say a word a from A is universal if for every b in B, b is a subset of a. 

Return a list of all universal words in A.  You can return the words in any order.

Example 1:

Input: A = ["amazon","apple","facebook","google","leetcode"], B = ["e","o"]
Output: ["facebook","google","leetcode"]
*/

class Solution {
public:
	vector<string> wordSubsets(vector<string>& A, vector<string>& B) {
		int fB[26] = {};
		for (string& w : B) {
			int f[26] = {};
			for (char c : w) f[c-'a']++;
			// merge curr freq counts to overall B's freq count
			for (int i=0; i < 26; i++)
				fB[i] = max(fB[i], f[i]);
		}
		
		vector<string> ans;
		for (string& w : A) {
			int f[26] = {};
			for (char c : w) f[c-'a']++;
			// compare if it satisfies fB
			bool universal = true;
			for (int i=0; i < 26; i++) {
				if (f[i] < fB[i]) {
					universal = false;
					break;
				}
			}
			if (universal) ans.push_back(w);
		}
		
		return ans;
	}
};