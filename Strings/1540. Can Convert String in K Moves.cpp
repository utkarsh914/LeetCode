// https://leetcode.com/problems/can-convert-string-in-k-moves/

/*
Given two strings s and t, your goal is to convert s into t in k moves or less.

During the ith (1 <= i <= k) move you can:

Choose any index j (1-indexed) from s, such that 1 <= j <= s.length
and j has not been chosen in any previous move, and shift the character at that index i times.
Do nothing.
Shifting a character means replacing it by the next letter in the alphabet
(wrapping around so that 'z' becomes 'a'). Shifting a character by i means
applying the shift operations i times.

Remember that any index j can be picked at most once.

Return true if it's possible to convert s into t in no more than k moves,
otherwise return false.

 

Example 1:

Input: s = "input", t = "ouput", k = 9
Output: true
Explanation: In the 6th move, we shift 'i' 6 times to get 'o'.
And in the 7th move we shift 'n' to get 'u'.

Example 2:

Input: s = "abc", t = "bcd", k = 10
Output: false
Explanation: We need to shift each character in s one time to convert it into t.
We can shift 'a' to 'b' during the 1st move. However,
there is no way to shift the other characters in the remaining moves to obtain t from s.

Example 3:

Input: s = "aab", t = "bbb", k = 27
Output: true
Explanation: In the 1st move, we shift the first 'a' 1 time to get 'b'.
In the 27th move, we shift the second 'a' 27 times to get 'b'.
 

Constraints:

1 <= s.length, t.length <= 10^5
0 <= k <= 10^9
s, t contain only lowercase English letters.
*/













/*
------- MORE CLEARER --------

Check if the 2 strings s and t have same length, if not, return false;

Loop through the input strings and count the shift displacement,
in case negative, plus 26 to make it positive;

If same displacement appears multiple times,
the 1st time use the displacement itself,
the 2nd time add 26to it, the 3rd time add 26 * (3 - 1) = 52,
the 4th time add 26 * (4 - 1) = 78, etc.;

if after adding the result is greater than k, return false;

If never encounter false in the above 3, return true.
*/

bool canConvertString(string& s, string& t, int k) {
	if (s.length() != t.length()) return false;

	int count[26] = {};
	for (int i = 0; i < s.length(); ++i) {
		int diff = (t[i] - s[i] + 26) % 26;
		if (diff > 0 and diff + count[diff] * 26 > k) {
			return false;
		}
		++count[diff];
	}
	return true;
}






/*
first keep a map of
	# of shifts to be done -> count

then verify for each shift if count shifts are allowed or not
at most one shift can be performed (1 + (k - shifts) / 26) times.

e.g. if k = 27
we can perform shift 'a' -> 'b' 2 times
i.e. once by shifting by 1, again by shifting by 27
*/
class Solution {
public:
	bool canConvertString(string& s, string& t, int k) {
		if (s.size() != t.size()) return false;
		int map[26] = {};

		for (int i = 0; i < s.size(); i++) {
			if (s[i] == t[i]) continue;
			int shifts = t[i] - s[i];
			if (shifts < 0) shifts += + 26;
			map[shifts]++;
		}

		for (int shifts = 0; shifts < 26; shifts++) {
			if (map[shifts] == 0) continue;
			if (shifts > k or map[shifts] > 1 + (k-shifts)/26)
				return false;
		}

		return true;
	}
};
