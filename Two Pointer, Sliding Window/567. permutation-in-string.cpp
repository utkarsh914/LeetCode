// https://leetcode.com/problems/permutation-in-string/


/*
take a window of s1 length, slide it and check if all the chars inside window are contained in s1
*/
class Solution {
public:
	bool checkInclusion(string& s1, string& s2) {
		if (s1.size() > s2.size()) return false;
		
		vector<int> fTotal(128, 0), fCur(128, 0);
		int k = s1.size(), found = 0, nChars = 0;

		for (char c : s1) fTotal[c]++; // count freq of all chars of text
		for (int n : fTotal) nChars += n>0; // count number of unique chars in text
		
		for (int i=0; i < k; i++) {
			char c = s2[i];
			if (++fCur[c] == fTotal[c]) found++;
		}
		
		for (int i=k; i <= s2.size(); i++) {
			//check for prev window
			if (found == nChars) return true;
			if (i == s2.size()) break;
			
			char c = s2[i];
			if (--fCur[s2[i-k]] == fTotal[s2[i-k]]-1) found--; // remove last char
			if (++fCur[c] == fTotal[c]) found++;
		}

		return false;
	}
};




/*
much more cleaner than above

How do we know string s2 contains a permutation of s1?
We just need to create a sliding window with length of s1, move from beginning to the end of s2.
When a character moves in from right of the window, we subtract 1 to that character count from the map.
When a character moves out from left of the window, we add 1 to that character count.
So once we see all zeros in the map, meaning equal numbers of every characters
between s1 and the substring in the sliding window, we know the answer is true.
*/
class Solution {
public:
	bool checkInclusion(string s1, string s2) {
		int len1 = s1.length(), len2 = s2.length();
		if (len1 > len2) return false;
		
		vector<int> count(128, 0);
		for (int i = 0; i < len1; i++) {
			count[s1[i]]++;
			count[s2[i]]--;
		}
		
		for (int i = len1; i < len2; i++) {
			// check prev window
			if (allZero(count)) return true;
			if (i == len2) break;

			count[s2[i]]--;
			count[s2[i - len1]]++;
		}
		
		return false;
	}
	
	bool allZero(vector<int>& count) {
		for (int i = 0; i < 128; i++)
			if (count[i] != 0) return false;
		return true;
	}
}




/*
*********** FIND MIN WINDOW SUBSTRING ***********
length of minimum window substring should be equal to s1.length()
*/
class Solution {
public:
	bool checkInclusion(string& s1, string& s2) {
		
		vector<int> fTotal(128, 0), fCur(128, 0);
		int i = 0, j = 0, minLen = INT_MAX;
		int found = 0, nChars = 0;

		for (char c : s1) fTotal[c]++; // count freq of all chars of text
		for (int n : fTotal) nChars += n>0; // count number of unique chars in text

		while (j < s2.size()) {
			if (found != nChars) {
				char c = s2[j++];
				if (++fCur[c] == fTotal[c]) found++;
			}
			// if minimum len window is found
			// record min, and keep decreasing window size
			while (found == nChars) {
				minLen = min(minLen, j-i);
				char c = s2[i++];
				if (--fCur[c] == fTotal[c]-1) found--;
			}
		}

		return minLen == s1.size();
	}
};