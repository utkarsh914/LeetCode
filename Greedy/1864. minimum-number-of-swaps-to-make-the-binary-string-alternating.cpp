// https://leetcode.com/problems/minimum-number-of-swaps-to-make-the-binary-string-alternating/

/*
Given a binary string s, return the minimum number of character
swaps to make it alternating, or -1 if it is impossible.

The string is called alternating if no two adjacent characters are equal.
For example, the strings "010" and "1010" are alternating,
while the string "0100" is not.

Any two characters may be swapped, even if they are not adjacent.

Example 1:

Input: s = "111000"
Output: 1
Explanation: Swap positions 1 and 4: "111000" -> "101010"
The string is now alternating.
*/


class Solution {
public:
	int minSwaps(string& s) {
		int c0 = count(s.begin(), s.end(), '0');
		int c1 = count(s.begin(), s.end(), '1');
		if (abs(c0-c1) > 1) return -1;
		
		int ans1 = 0, ans2 = 0;

		for (int i = 0; i < s.size(); i++) {
			if (i%2 == 0) {
				if (s[i] != '1') ans1++;
			} else {
				if (s[i] != '0') ans1++;
			}
		}
		
		for (int i = 0; i < s.size(); i++) {
			if (i%2 == 0) {
				if (s[i] != '0') ans2++;
			} else {
				if (s[i] != '1') ans2++;
			}
		}
		
		ans1 = ans1 % 2 != 0 ? INT_MAX : ans1 / 2;
		ans2 = ans2 % 2 != 0 ? INT_MAX : ans2 / 2;
		int ans = min(ans1, ans2);
		return ans == INT_MAX ? -1 : ans;
	}
};




/*
The key to solve this problem is to count number of indexes which contain wrong character.
So for string s = 11001, count will be 2 as characters at s[1] and s[2] are wrong.
And number of swaps will be count / 2.
For example, we can just swap character at index 1 and index 2 to obtain s = 10101.

Things to notice

Solving this problem will be impossible if difference between
number of ones and number of zeros will be greater than 1.

If number of ones is greater than number of zeroes
then 1 should be the first character of resulting string.
Similarly if number of zeroes is greater than number of ones
then 0 should be the first character of resulting string.

If number of ones is equal to number of zeroes,
we will find minimum number of swaps of both cases:

Case 1 : 1 is the first character.
Case 2 : 0 is the first character.

*/

class Solution {
public:
	int minSwaps(string& s) {

		int n = s.length();
		int ones = 0, zero = 0;
		for(char c : s){
			if(c == '1') ++ones;
			else ++zero;
		}
		
		if(abs(ones-zero) > 1)
			return -1;
		
		if(ones > zero)
			return helper(s, '1');
		else if(zero > ones)
			return helper(s, '0');
		
		return min(helper(s, '1'), helper(s, '0'));
	}
	
	int helper(string& s, char c){
		int swaps = 0;
		for(char ch : s){
			if(ch != c) ++swaps;
			c ^= 1;
		}
		return swaps/2;
	}
};