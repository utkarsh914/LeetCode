// https://leetcode.com/problems/longest-repeating-character-replacement/

/*

*/



/*
======== SAME AS - 3. longest-substring-without-repeating-characters =======
======== or more like - 1004: max-consecutive-ones-iii ========

just try building the string of every character possible (26 total)

or for more optimization - 
try with only the characters that are present in the string
*/
class Solution {
public:
	int characterReplacement(string& s, int k) {
		int ans = 0, freq[26] = {};
		for (char& c : s) freq[c-'A']++;

		for (int i=0; i < 26; i++) {
			if (freq[i] > 0)
				ans = max(ans, replaceIt(s, k, i+'A'));
		}
		return ans;
	}

	int replaceIt(string& s, int k, char c) {
		int ans = 0, different = 0;
		for (int l = 0, r = 0; r < s.size(); r++) {
			different += s[r] != c;
			while (different > k) {
				different -= s[l++] != c;
			}
			ans = max(ans, r-l+1);
		}
		return ans;
	}
};






/*
This question is pretty much similar to Max Consecutive Ones III

We take two variables, start and end, indicating the starting and ending indices of our required longest substring.
At first, keeping the start variable fixed, we keep moving end variable, one at a time towards the end of the string s.
While moving end, we keep a frequency check of the number of times a particular alphabet is occuring using freq vector.
We then find out the frequency of the maximum occuring alphabet (max_char)
Now we have a substring whose starting position is indicated by start and ending by end. The length of which is end-start+1.
In this substring, we have to replace end-start+1-max_char characters, to make all of them equal.
(Why end-start+1-max_char ??....see figure below).
Only if this end-start+1-max_char is lesser or equal than k, then we can replace,
else we keep moving start, until condition is fulfilled.
*/
class Solution {
public:
	int characterReplacement(string& s, int k) {
		int max_char = 0, length = 0;
		vector<int> freq(128, 0);
		
		for(int l = 0, r = 0; r < s.size(); r++) {
			max_char = max(max_char, ++freq[s[r]]);
			
			while(r-l+1 - max_char > k)
				freq[s[l++]]--;
			
			length = max(length, r-l+1);
		}
		
		return length;
	}
};

/*
end-start+1 = size of the current window
maxCount = largest count of a single, unique character in the current window

The main equation is: end-start+1-maxCount

When end-start+1-maxCount == 0, then then the window is filled with only one character
When end-start+1-maxCount > 0, then we have characters in the window that are NOT the character
that occurs the most. end-start+1-maxCount is equal to exactly the # of characters
that are NOT the character that occurs the most in that window.
Example: For a window "xxxyz", end-start+1-maxCount would equal 2.
(maxCount is 3 and there are 2 characters here, "y" and "z" that are not "x" in the window.)

We are allowed to have at most k replacements in the window,
so when end-start+1-maxCount > k,
then there are more characters in the window than we can replace,
and we need to shrink the window.

If we have window with "xxxy" and k = 1,
that's fine because end-start+1-maxCount = 1,
which is not > k. maxLength gets updated to 4.

But if we then find a "z" after, like "xxxyz",
then we need to shrink the window because now end-start+1-maxCount = 2, and 2 > 1.
The window becomes "xxyz".

maxCount may be invalid at some points, but this doesn't matter,
because it was valid earlier in the string, and all that matters is
finding the max window that occurred anywhere in the string.
Additionally, it will expand if and only if enough repeating characters
appear in the window to make it expand.
So whenever it expands, it's a valid expansion.
*/