// https://leetcode.com/problems/maximum-product-of-word-lengths/

/*
Given a string array words, return the maximum value of
length(word[i]) * length(word[j]) where the two words do not share common letters.
If no such two words exist, return 0.

Example 1:

Input: words = ["abcw","baz","foo","bar","xtfn","abcdef"]
Output: 16
Explanation: The two words can be "abcw", "xtfn".
*/



class Solution {
public:
	int maxProduct(vector<string>& words) {
		int size = words.size();
		vector<int> chars(size, 0);

		/*
		store in bits whether a character exists in the ith word
		chars[i] = 00000000000000000000000000001101
		means that word[i] contains 'a', 'c', and 'd' only
		*/
		for (int i = 0; i < size; i++)
			for (char& c : words[i])
				chars[i] |= (1 << (c-'a'));
		/*
		if two words have no character in common, then
		AND of their chars should be zero
		*/
		int ans = 0;
		for (int i = 0; i < size; i++)
			for (int j = 0; j < size; j++)
				if ((chars[i] & chars[j]) == 0)
					ans = max(ans, words[i].size() * words[j].size());

		return ans;
	}
	
	int max(int x, int y) {return x>y ? x : y;}
};