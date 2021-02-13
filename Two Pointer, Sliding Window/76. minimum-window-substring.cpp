// https://leetcode.com/problems/minimum-window-substring/

/*
Given two strings s and t, return the minimum window in s which will contain all the characters in t.
If there is no such window in s that covers all characters in t, return the empty string "".
Note that If there is such a window, it is guaranteed that there will always be only one unique minimum window in s.

Example 1:

Input: s = "ADOBECODEBANC", t = "ABC"
Output: "BANC"
*/


class Solution {
public:
	string minWindow(string& s, string& t) {

		vector<int> fTotal(128, 0), fCur(128, 0);
		int i = 0, j = 0, start = 0, minLen = INT_MAX;
		int found = 0, nChars = 0;

		for (char c:t) fTotal[c]++; // count freq of all chars of text
		for (int n:fTotal) nChars += n>0; // count number of unique chars in text

		while (j < s.size()) {

			if (found != nChars) {
				char c = s[j++];
				if (++fCur[c] == fTotal[c]) found++;
			}
			
			// if minimum len window is found
			// record min, and keep decreasing window size
			while (found == nChars) {
				if (j-i < minLen) {
					minLen = j-i;
					start = i;
				}
				char c = s[i++];
				if (--fCur[c] == fTotal[c]-1) found--;
			}
		}

		return minLen==INT_MAX ? "" : s.substr(start, minLen);
	}
};







/*
1. Use two pointers: start and end to represent a window.
2. Move end to find a valid window.
3. When a valid window is found, move start to find a smaller window.

To check if a window is valid, we use a map to store (char, count) for chars in t.
And use counter for the number of chars of t to be found in s. The key part is m[s[end]]--;.
We decrease count for each char in s. If it does not exist in t, the count will be negative.
*/

// ******** using ONE MAP *********
string minWindow(string s, string t) {
	unordered_map<char, int> m;
	// Statistic for count of char in t
	for (char c : t) m[c]++;
	// counter represents the number of chars of t to be found in s.
	int start = 0, end = 0, counter = t.size(), minStart = 0, minLen = INT_MAX;
	
	while (end < s.size()) {
		// Move end to find a valid window.
		if (counter != 0) {
			char c = s[end++];
			if (m[c] > 0)	counter--; // If char in s exists in t, decrease counter
			m[c]--;                  // Decrease m[s[end]]. If char does not exist in t, m[s[end]] will be negative.
		}

		// When we found a valid window, move start to find smaller window.
		while (counter == 0) {
			if (end - start < minLen) {
				minStart = start;
				minLen = end - start;
			}
			char c = s[start++];
			if (m[c] > 0)	counter++; // When char exists in t, increase counter.
			m[c]++;                  // as we've removed starting char, increase ts freq in map
		}
	}
	
	return (minLen != INT_MAX) ? s.substr(minStart, minLen) : "";
}
