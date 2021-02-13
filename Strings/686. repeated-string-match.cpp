
// https://leetcode.com/problems/repeated-string-match/

class Solution {

	int rotatingRabinCarp(string& txt, string& pat, int maxRepeats) {

		int N = txt.length(), M = pat.length();
		int i=0, j=0;
		int base = 256; // we assume string can contain any of 256 chars, so base 256
		int Q = 70001; // prime num to take modulo
		int ht = 0; // hash of window
		int hp = 0; // hash of pattern
		int a = 1; // (base^(pat.length-1)) % Q

		// compute 'a'
		for (i=0; i<M-1; i++)
			a = (a * base) % Q;

		// compute hash of pattern, and first window of text at once
		for (i=0; i<M; i++) {
			hp = (hp*base + pat[i]) % Q;
			ht = (ht*base + txt[i%N]) % Q;
		}

		// slide the window and keep checking window hash to pattern hash(hp)
		for (i=0; i < N*maxRepeats; i++) {
			// compare hash, if equal, compare window to pattern
			if (ht == hp) {
				for (j=0; j<M; j++)
					if (txt[(j+i)%N] != pat[j])
						break;
				if (j==M) // matched fully
					return 1+((i+M-1)/N);
			}
			// recompute next window hash
			if ((i+1)%N < N*maxRepeats) {
				ht = ((ht - txt[i%N]*a)*base + txt[(i+M)%N]) % Q;
				if (ht < 0) ht += Q; // if negative, convert to +ve
			}
		}

		return -1;
	}

public:
	int repeatedStringMatch(string& txt, string& pat) {
		int N = txt.length(), M = pat.length();
		int maxRepeats = (M-1)/N + 2; // max number of times txt string should repeat to contain pattern (in worst case)
		return rotatingRabinCarp(txt, pat, maxRepeats);
	}
};