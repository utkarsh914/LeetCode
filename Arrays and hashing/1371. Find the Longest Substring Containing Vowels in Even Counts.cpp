// https://leetcode.com/problems/find-the-longest-substring-containing-vowels-in-even-counts/

/*
Given the string s, return the size of the longest substring containing each vowel an even number of times. That is, 'a', 'e', 'i', 'o', and 'u' must appear an even number of times.

 

Example 1:

Input: s = "eleetminicoworoep"
Output: 13
Explanation: The longest substring is "leetminicowor" which contains two each of the vowels: e, i and o and zero of the vowels: a and u.
Example 2:

Input: s = "leetcodeisgreat"
Output: 5
Explanation: The longest substring is "leetc" which contains two e's.
Example 3:

Input: s = "bcbcbc"
Output: 6
Explanation: In this case, the given string "bcbcbc" is the longest because all vowels: a, e, i, o and u appear zero times.
 

Constraints:

1 <= s.length <= 5 x 10^5
s contains only lowercase English letters.
*/





/*
similar to: 


Represent the counts (odd or even) of vowels with a bitmask.
Precompute the prefix xor for the bitmask of vowels
and then get the longest valid substring.
*/
class Solution {
public:
	int findTheLongestSubstring(string s) {
		unordered_map<char, int> ind {
			{'a', 0}, {'e', 1}, {'i', 2}, {'o', 3}, {'u', 4}
		};
		unordered_map<int, int> prevPos;
		prevPos[0] = -1;
		int cur = 0, ans = 0;
		
		for (int i = 0; i < s.size(); i++) {
			char c = s[i];
			if (ind.count(c))
				cur = cur ^ (1 << ind[c]);
			if (prevPos.count(cur))
				ans = max(ans, i - prevPos[cur]);
			else prevPos[cur] = i;
		}
		
		return ans;
	}
};