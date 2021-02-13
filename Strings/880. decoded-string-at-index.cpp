// https://leetcode.com/problems/decoded-string-at-index/

/*
An encoded string S is given.  To find and write the decoded string to a tape, the encoded string is read one character at a time and the following steps are taken:

If the character read is a letter, that letter is written onto the tape.
If the character read is a digit (say d), the entire current tape is repeatedly written d-1 more times in total.
Now for some encoded string S, and an index K, find and return the K-th letter (1 indexed) in the decoded string.

Example 1:

Input: S = "leet2code3", K = 10
Output: "o"
Explanation: 
The decoded string is "leetleetcodeleetleetcodeleetleetcode".
The 10th letter in the string is "o".
*/

class Solution {
public:
	string decodeAtIndex(string s, int k) {
		
		long long curSize = 0;
		// count the size
		for (char c:s) {
			if (isdigit(c)) {
				curSize *= (c-'0');
			} else {
				curSize++;
			}
		}
		
		// adjust k now
		for (int i=s.size()-1; i>=0; i--) {
			char c = s[i];
			if (isdigit(c)) {
				curSize /= (c-'0');
				k = k % curSize;
			} else {
				if (k % curSize == 0)
					return string(1,c);
				curSize--;
			}
		}

		return "utkarsh";
	}
};


/*
Intuition

If we have a decoded string like appleappleappleappleappleapple and an index like K = 24, the answer is the same if K = 4.
In general, when a decoded string is equal to some word with size length repeated some number of times
(such as apple with size = 5 repeated 6 times), the answer is the same for the index K as it is for the index K % size.

We can use this insight by working backwards, keeping track of the size of the decoded string. Whenever the decoded string would equal some word repeated d times, we can reduce K to K % (word.length).

Algorithm

First, find the length of the decoded string. After, we'll work backwards, keeping track of size:
the length of the decoded string after parsing symbols S[0], S[1], ..., S[i].

If we see a digit S[i], it means the size of the decoded string after parsing
S[0], S[1], ..., S[i-1] will be size / Integer(S[i]). Otherwise, it will be size - 1.
*/