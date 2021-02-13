// https://leetcode.com/problems/split-two-strings-to-make-palindrome/

/*
You are given two strings a and b of the same length.
Choose an index and split both strings at the same index, splitting a into two strings:
aprefix and asuffix where a = aprefix + asuffix, and splitting b into two strings:
bprefix and bsuffix where b = bprefix + bsuffix. Check if aprefix + bsuffix or bprefix + asuffix forms a palindrome.

When you split a string s into sprefix and ssuffix, either ssuffix or sprefix is allowed to be empty.
For example, if s = "abc", then "" + "abc", "a" + "bc", "ab" + "c" , and "abc" + "" are valid splits.
Return true if it is possible to form a palindrome string, otherwise return false.
Notice that x + y denotes the concatenation of strings x and y.

Example 1:

Input: a = "x", b = "y"
Output: true
Explaination: If either a or b are palindromes the answer is true since you can split in the following way:
aprefix = "", asuffix = "x"
bprefix = "", bsuffix = "y"
Then, aprefix + bsuffix = "" + "y" = "y", which is a palindrome.
Example 2:

Input: a = "abdef", b = "fecab"
Output: true
Example 3:

Input: a = "ulacfd", b = "jizalu"
Output: true
Explaination: Split them at index 3:
aprefix = "ula", asuffix = "cfd"
bprefix = "jiz", bsuffix = "alu"
Then, aprefix + bsuffix = "ula" + "alu" = "ulaalu", which is a palindrome.
Example 4:

Input: a = "xbdef", b = "xecab"
Output: false
*/




/*
Intution says find out a prefix string that matches with postfix part of the second string.
But thats not enough, after that we check for a palindrome within a string.




Greedily use all matching letters from suffix and prefix.
Then check if the middle of either string is a palindrome.
This logic can be easily proven by a contradiction.

Another way to think about this:
using more characters from the both strings "shrinks" the middle part,
so it increases the chance that the middle part is a palindrome.

Note that we do this twice - once for a] + [b, and once for b] + [a.
*/



class Solution {
public:
	bool checkPalindromeFormation(string& a, string& b) {
		return check(a,b) or check(b,a);
	}
	
	bool check(string& a, string& b) {
		int i = 0, j = a.size()-1, s = a.size();
		while (i < s && j >= 0) {
			if (a[i] == b[j])
				i++, j--;
			else break;
		}
		return ispal(a, i, j) or ispal(b, i, j);
	}
	
	
	bool ispal(string& s, int i, int j) {
		while (i < j) {
			if (s[i] != s[j])
				return false;
			else i++, j--;
		}
		return true;
	}
};

