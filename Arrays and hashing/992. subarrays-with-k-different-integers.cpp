// https://leetcode.com/problems/subarrays-with-k-different-integers/

/*
find the number of subarrays with k different unique integers
*/

class Solution {
public:
	int subarraysWithKDistinct(vector<int>& A, int K) {
		return atMostDistinct(A, K) - atMostDistinct(A, K-1);
	}

	int atMostDistinct(vector<int>& A, int K) {
		if (K <= 0) return 0;
		unordered_map<int, int> freq;
		int count = 0;

		for (int r = 0, l = 0; r < A.size(); r++) {
			freq[A[r]]++;
			while (freq.size() > K) {
				if (--freq[A[l]] == 0)
					freq.erase(A[l]);
				l++;
			}
			count += r - l + 1;
		}

		return count;
	}
};
