// https://leetcode.com/problems/repeated-substring-pattern/

/*
The explanation for why that works is pretty straight forward.
Consider a string S="helloworld". Now, given another string T="lloworldhe", can we figure out if T is a rotated version of S?
Yes, we can! We check if S is a substring of T+T.
Fine. How do we apply that to this problem? We consider every rotation of string S such that
it's rotated by k units [k < len(S)] to the left. Specifically, we're looking at strings
"elloworldh", "lloworldhe", "loworldhel", etc...
If we have a string that is periodic (i.e. is made up of strings that are the same and repeat R times),
then we can check if the string is equal to some rotation of itself, and if it is, then we know that the string is periodic.
Checking if S is a sub-string of (S+S)[1:-1] basically checks if the string is present in a rotation of itself
for all values of R such that 0 < R < len(S)

*/
class Solution {
public:
	bool repeatedSubstringPattern(string s) {
		if (!s.length()) return false;
		string str = s.substr(1,s.length()-1) + s.substr(0,s.length()-1);
		return str.find(s) != string::npos;
	}
};



/*
https://leetcode.com/problems/repeated-substring-pattern/discuss/94397/C%2B%2B-O(n)-using-KMP-32ms-8-lines-of-code-with-brief-explanation.

To Clarify Let's take an example of "abc" repeated 5 times. String : "abcabcabcabcabc"
The the table below

first row is the index
second row is the character corresponding to each index
third row is the value that the KMP prefix array would have at that position. (with slight variation on the index, you can build KMP in different ways)
0	1	2	3	4	5	6	7	8	9	10	11	12	13	14	15
a	b	c	a	b	c	a	b	c	a	b	c	a	b	c	
0	0	0	0	1	2	3	4	5	6	7	8	9	10	11	12
Here dp[n] = 12
n - dp[n] = 3 which is the length of the repeated substring. Ans is : (12 && (12 % 3) == 0) ===> 1

dp[n] && dp[n] % (n - dp[n]) == 0 means that the string should have some repetition (dp[n] > 0) , and the string should be divisible by the repeated substring.
*/

class Solution {
	vector<int> computeLPS(string& pat) {
		vector<int> lps(pat.length(), 0);
		for (int i=0, j=1; j<pat.length();) {
			if (pat[i] == pat[j])
				lps[j]=i+1, i++,j++;
			else if (i==0)
				lps[j]=0, j++;
			else
				i=lps[i-1];
		}
		return lps;
	}

public:
	bool repeatedSubstringPattern(string s) {
		if (!s.length()) return false;
		vector<int> lps = computeLPS(s);
		int l = s.length();
		return lps[l-1] and (l % (l-lps[l-1]) == 0);
	}
};