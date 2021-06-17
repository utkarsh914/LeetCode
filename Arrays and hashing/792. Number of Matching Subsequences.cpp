// https://leetcode.com/problems/number-of-matching-subsequences/

/*
Given a string s and an array of strings words,
return the number of words[i] that is a subsequence of s.

A subsequence of a string is a new string generated from the original string
with some characters (can be none) deleted without changing the relative
order of the remaining characters.

For example, "ace" is a subsequence of "abcde".
 

Example 1:

Input: s = "abcde", words = ["a","bb","acd","ace"]
Output: 3
Explanation: There are three strings in words
that are a subsequence of s: "a", "acd", "ace".

Example 2:

Input: s = "dsahjpjauf", words = ["ahjpjau","ja","ahbwzgqnuk","tnmlanowax"]
Output: 2
 

Constraints:

1 <= s.length <= 5 * 104
1 <= words.length <= 5000
1 <= words[i].length <= 50
s and words[i] consist of only lowercase English letters.
*/








// ------ NAIVE ------
// time complexity: O( sigma(words[i].size * s.size) )

class Solution {
public:
	int numMatchingSubseq(string& s, vector<string>& words) {
		int c = 0;
		for (auto& w : words)
			c += isSubseq(s, w);
		return c;
	}
	
	bool isSubseq(string& s1, string& s2) {
		int i = 0, j = 0;
		while (i < s1.size() and j < s2.size()) {
			if (s1[i] == s2[j]) i++, j++;
			else i++;
		}
		return j == s2.size();
	}
};







/*
---- ACCEPTED -----

time complexity: O( sigma(words[i].size) * log2 (s.size) )


 INTUITION:
traversing s for every word is very costly, as s can be 10^4 size
but word is very small <= 50 in size.

so, why not traverse through each word
and for each letter of word, find the next index in s
that has this letter.

for this, we can pre-store the indices of each letter in s,
in an map, in increasing order.
so, we can just do binary search to get the required index
*/
class Solution {
	unordered_map<char, vector<int>> map;
public:
	int numMatchingSubseq(string& s, vector<string>& words) {
		for (int i = 0; i < s.size(); i++) {
			map[s[i]].push_back(i);
		}
		
		int c = 0;
		for (auto& w : words)
			c += isSubseq(s, w);
		return c;
	}
	
	bool isSubseq(string& s1, string& s2) {
		int i = 0, j = 0;
		while (i < s1.size() and j < s2.size()) {
			vector<int>& v = map[s2[j]];
			auto ub = upper_bound(v.begin(), v.end(), i-1);
			if (ub == v.end()) return false;
			i = 1 + *ub;
			j++;
		}
		return j == s2.size();
	}
};






/*
*********** POCHMAN'S IDEA ************

I go through S once, and while I'm doing that, I move through all words accordingly.
That is, I keep track of how much of each word I've already seen,
and with each letter of S, I advance the words waiting for that letter.
To quickly find the words waiting for a certain letter,
I store each word (and its progress) in a list of words waiting for that letter.
Then for each of the lucky words whose current letter just occurred in S,
I update their progress and store them in the list for their next letter.

Let's go through the given example:

S = "abcde"
words = ["a", "bb", "acd", "ace"]
I store that "a", "acd" and "ace" are waiting for an 'a' and "bb"
is waiting for a 'b' (using parentheses to show how far I am in each word):

'a':  ["(a)", "(a)cd", "(a)ce"]
'b':  ["(b)b"]
Then I go through S. First I see 'a', so I take the list of words waiting for 'a'
and store them as waiting under their next letter:

'b':  ["(b)b"]
'c':  ["a(c)d", "a(c)e"]
None: ["a"]
You see "a" is already waiting for nothing anymore, while "acd" and "ace"
are now waiting for 'c'. Next I see 'b' and update accordingly:

'b':  ["b(b)"]
'c':  ["a(c)d", "a(c)e"]
None: ["a"]
Then 'c':

'b':  ["b(b)"]
'd':  ["ac(d)"]
'e':  ["ac(e)"]
None: ["a"]
Then 'd':

'b':  ["b(b)"]
'e':  ["ac(e)"]
None: ["a", "acd"]
Then 'e':

'b':  ["b(b)"]
None: ["a", "acd", "ace"]
And now I just return how many words aren't waiting for anything anymore.
*/