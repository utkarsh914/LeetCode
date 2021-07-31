// https://leetcode.com/problems/construct-k-palindrome-strings/

/*
Given a string s and an integer k. You should construct k non-empty palindrome strings using all the characters in s.

Return True if you can use all the characters in s to construct k palindrome strings or False otherwise.

 

Example 1:

Input: s = "annabelle", k = 2
Output: true
Explanation: You can construct two palindromes using all characters in s.
Some possible constructions "anna" + "elble", "anbna" + "elle", "anellena" + "b"
Example 2:

Input: s = "leetcode", k = 3
Output: false
Explanation: It is impossible to construct 3 palindromes using all the characters of s.
Example 3:

Input: s = "true", k = 4
Output: true
Explanation: The only possible solution is to put each character in a separate string.
Example 4:

Input: s = "yzyzyzyzyzyzyzy", k = 2
Output: true
Explanation: Simply you can put all z's in one string and all y's in the other string. Both strings will be palindrome.
Example 5:

Input: s = "cr", k = 7
Output: false
Explanation: We don't have enough characters in s to construct 7 palindromes.
 

Constraints:

1 <= s.length <= 10^5
All characters in s are lower-case English letters.
1 <= k <= 10^5
*/








/*
to make a palindrome having different chars,
we need to have an even number of all chars except at most one.
like 'ABCBA' has 'A', 'B' occuring even times, while 'C' odd.

I record frequencies of every char, and split f[i] into 2 groups.
first -> only 1's
second -> only 2's

e.g.
f[i] = 5 can be split into [1, 2, 2]
f[i] = 7 can be split into [1, 2, 2, 2]
f[i] = 6 can be split into [2, 2, 2]

and we keep a total sum of group1 and group2
that we have made for every f[i].

Maximum number of palindromes we can make :-
	group1 + 2 * group2
	bcz, suppose there are 2 chars that contributed to group1,
	so they will be taken separately.
	and every char of group 2 can be taken separately as well.

Minimum number of palindromes :-
	we can merge some(or all) group1 into group2's
	every member of group1 can be fitted with one member of group2.
	and the left group1 members will be taken as alone.
	which concludes, minimum can be equal to count of group1 only.

if k lies in [min, max], then ans is true
else false

Note: it can be proven that if the size of group2 is x,
then we can make any number of palindromes from them
in the range [1, x].
*/
class Solution {
public:
	bool canConstruct(string& s, int k) {
		vector<int> f(26, 0);
		for (char c : s) {
			f[c-'a']++;
		}

		int sizeOne = 0, sizeTwo = 0;
		for (int n : f) {
			sizeTwo += n / 2;
			sizeOne += n % 2;
		}

		int minK = sizeOne, maxK = sizeOne + 2 * sizeTwo;
		return k >= minK and k <= maxK;
	}
};





/*
If the s.length < k we cannot construct k strings from s
and answer is false.

If the number of characters that have odd counts is > k,
then the minimum number of palindrome strings we can construct is > k
and answer is false.

Otherwise you can construct exactly k palindrome strings
and answer is true (why ?).
*/


	bool canConstruct(string s, int k) {
		bitset<26> odd;
		for (char& c : s)
			odd.flip(c - 'a');
		return k <= s.size() and k >= odd.count();
	}