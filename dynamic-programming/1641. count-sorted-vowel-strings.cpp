
// https://leetcode.com/problems/count-sorted-vowel-strings/

/*
Given an integer n, return the number of strings of length n that consist only of vowels (a, e, i, o, u)
and are lexicographically sorted.
A string s is lexicographically sorted if for all valid i, s[i] is the same as or comes before s[i+1] in the alphabet.

Example 1:
Input: n = 1
Output: 5
Explanation: The 5 sorted strings that consist of vowels only are ["a","e","i","o","u"].
Example 2:

Input: n = 2
Output: 15
Explanation: The 15 sorted strings that consist of vowels only are
["aa","ae","ai","ao","au","ee","ei","eo","eu","ii","io","iu","oo","ou","uu"].
Note that "ea" is not a valid string since 'e' comes after 'a' in the alphabet.
*/


/*
just think about the mathematical induction
if we know all the string of len k, so the string of len k + 1 will be
1 add a before all string of len k
2 add e before the string of len k, which is starts with or after e
3 add i before the string of len k, which starts with or after i
4 add o before the string of len k, which starts with or after o
5 add u before the string of len k, which starts with or after u
*/
class Solution {
public:
	int countVowelStrings(int n) {
		int a=1, e=1, i=1, o=1, u=1;
		while (n-- > 1) {
			a = a+e+i+o+u;
			e = e+i+o+u;
			i = i+o+u;
			o = o+u;
			u = u;
		}
		return a+e+i+o+u;
	}
};