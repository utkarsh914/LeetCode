// https://leetcode.com/problems/minimum-number-of-flips-to-make-the-binary-string-alternating/

/*
You are given a binary string s. You are allowed to perform two types of operations on the string in any sequence:

Type-1: Remove the character at the start of the string s and append it to the end of the string.
Type-2: Pick any character in s and flip its value, i.e., if its value is '0' it becomes '1' and vice-versa.
Return the minimum number of type-2 operations you need to perform such that s becomes alternating.

The string is called alternating if no two adjacent characters are equal.

For example, the strings "010" and "1010" are alternating, while the string "0100" is not.
 

Example 1:

Input: s = "111000"
Output: 2
Explanation: Use the first operation two times to make s = "100011".
Then, use the second operation on the third and sixth elements to make s = "101010".
*/







/*
For the 1st operation, we can simply do s += s to append the whole string to the end.
and slide a window of size k = s.size(),
and in each window, find the number of flips to keep it like 0101...
and the number of flips to keep it like 1010...

evaluate these 2 cases for each window, and return minimum answer
*/
class Solution {
public:
	int minFlips(string& s) {
		int k = s.size();
		s += s;

		// if we keep '0' at even indices, '1' at odd
		int zeroFirst = 0, minZeroFirst = k;
		// first window
		for (int i = 0; i < k; i++) {
			if (i%2 == 0) zeroFirst += s[i]!='0';
			else zeroFirst += s[i]!='1';
		}
		// slide the window further
		for (int i = k; i <= s.size(); i++) {
			minZeroFirst = min(minZeroFirst, zeroFirst);
			if (i == s.size()) break;
			// add ith ele
			if (i%2 == 0) zeroFirst += s[i]!='0';
			else zeroFirst += s[i]!='1';
			// remove i-kth ele
			if ((i-k) % 2 == 0) zeroFirst -= s[i]!='0';
			else zeroFirst -= s[i]!='1';
		}
		

		// if we keep '1' at even indices, '0' at odd
		int oneFirst = 0, minOneFirst = k;
		// first window
		for (int i = 0; i < k; i++) {
			if (i%2 == 0) oneFirst += s[i]!='1';
			else oneFirst += s[i]!='0';
		}
		// slide the window further
		for (int i = k; i <= s.size(); i++) {
			minOneFirst = min(minOneFirst, oneFirst);
			if (i == s.size()) break;
			// add ith ele
			if (i%2 == 0) oneFirst += s[i]!='1';
			else oneFirst += s[i]!='0';
			// remove i-kth ele
			if ((i-k) % 2 == 0) oneFirst -= s[i]!='1';
			else oneFirst -= s[i]!='0';
		}
		
		return min(minZeroFirst, minOneFirst);
	}
};

/*
"01001001101"
01001001101 01001001101
*/






/*
----------- more cleaner (using helper fn) --- O(N) space ----------

this solution can be optimized to O(1) space too.
just mod and rotate the index to access the cur, and prev elements
*/
class Solution {
public:
	int minFlips(string& s) {
		int k = s.size();
		s += s;
		return min(getMinFlips(s, '0', '1'), getMinFlips(s, '1', '0'));
	}

	int getMinFlips(string& s, char charAtEven, char charAtOdd) {
		// if we keep charAtEven at even indices, charAtOdd at odd
		int k = s.size() / 2;
		int flips = 0, minflips = k;
		// first window
		for (int i = 0; i < k; i++) {
			if (i%2 == 0) flips += s[i] != charAtEven;
			else flips += s[i] != charAtOdd;
		}
		// slide the window further
		for (int i = k; i <= s.size(); i++) {
			minflips = min(minflips, flips);
			if (i == s.size()) break;
			// add ith ele
			if (i%2 == 0) flips += s[i] != charAtEven;
			else flips += s[i] != charAtOdd;
			// remove i-kth ele
			if ((i-k) % 2 == 0) flips -= s[i] != charAtEven;
			else flips -= s[i] != charAtOdd;
		}

		return minflips;
	}
};

/*
"01001001101"
01001001101 01001001101
*/







/*
The alternating string can start with '0' or '1'.
We count how many replancements we need for these two cases in s0 and s1.

But do not stop there. Since we can rotate our string, keep going and counting.
However, this time we need to discard (subtract) missmatches
that occurred before the rotated string.
This can be done using the sliding window approach.
*/
int minFlips(string& s) {
	int res = INT_MAX, s0 = 0, s1 = 0, sz = s.size();

	for (int i = 0; i < 2 * sz; ++i) {
		s0 += s[i % sz] != '0' + i % 2;
		s1 += s[i % sz] != '0' + (1 - i % 2);
		// if first window completed
		if (i >= sz - 1) {
			// if we exceeded the first window (i.e. it is 2nd,3rd,4th...window)
			// we need to remove i-kth char
			if (i >= sz) {
				s0 -= s[i - sz] != '0' + (i - sz) % 2;
				s1 -= s[i - sz] != '0' + (1 - (i - sz) % 2);
			}
			res = min(res, min(s0, s1));
		}
	}

	return res;
}