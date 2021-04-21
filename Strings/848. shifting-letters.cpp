// https://leetcode.com/problems/shifting-letters/

/*
We have a string S of lowercase letters, and an integer array shifts.

Call the shift of a letter, the next letter in the alphabet, (wrapping around so that 'z' becomes 'a'). 

For example, shift('a') = 'b', shift('t') = 'u', and shift('z') = 'a'.

Now for each shifts[i] = x, we want to shift the first i+1 letters of S, x times.

Return the final string after all such shifts to S are applied.

Example 1:

Input: S = "abc", shifts = [3,5,9]
Output: "rpl"
Explanation: 
We start with "abc".
After shifting the first 1 letters of S by 3, we have "dbc".
After shifting the first 2 letters of S by 5, we have "igc".
After shifting the first 3 letters of S by 9, we have "rpl", the answer.
*/


class Solution {
public:
	string shiftingLetters(string& s, vector<int>& shifts) {
		vector<char> v(s.size()+1, 0);
		for (int i=0; i < shifts.size(); i++) {
			v[0] = (v[0] + shifts[i]) % 26;
			v[i+1] = (v[i+1] - shifts[i]) % 26;
			if (v[i+1] < 0) v[i+1] += 26;
		}
		for (int i=1; i < v.size(); i++) {
			v[i] = (v[i-1] + v[i]) % 26;
		}
		for (int i=0; i < s.size(); i++) {
			s[i] = (s[i]-'a'+v[i]) % 26 + 'a';
		}
		return s;
	}
};



// Going right to left, and accumulating shifts. Note that we only need to carry over shifts % 26.
class Solution {
public:
	string shiftingLetters(string S, vector<int> sh) {
		for (int i = sh.size()-1, m = 0; i >= 0; --i, m %= 26) {
			m += sh[i];
			S[i] = (S[i] - 'a' + sh[i]) % 26 + 'a';
		}
		return S;
	}
};

/*
One pass to count suffix sum of shifts.
One pass to shift letters in string S
*/
class Solution {
public:
	string shiftingLetters2(string S, vector<int> shifts) {
		for (int i = shifts.size() - 2; i >= 0; i--)
			shifts[i] = (shifts[i] + shifts[i + 1]) % 26;

		for (int i = 0; i < shifts.size(); i++)
			S[i] = (S[i] - 'a' + shifts[i]) % 26 + 'a';
		
		return S;
	}
};