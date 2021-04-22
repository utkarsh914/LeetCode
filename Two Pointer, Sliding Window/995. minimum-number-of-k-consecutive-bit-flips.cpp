// https://leetcode.com/problems/minimum-number-of-k-consecutive-bit-flips/

/*
In an array A containing only 0s and 1s, a K-bit flip consists of choosing a (contiguous)
subarray of length K and simultaneously changing every 0 in the subarray to 1,
and every 1 in the subarray to 0.

Return the minimum number of K-bit flips required so that there is no 0 in the array.
If it is not possible, return -1.


Example 1:

Input: A = [0,1,0], K = 1
Output: 2
Explanation: Flip A[0], then flip A[2].
Example 2:

Input: A = [1,1,0], K = 2
Output: -1
Explanation: No matter how we flip subarrays of size 2, we can't make the array become [1,1,1].
Example 3:

Input: A = [0,0,0,1,0,1,1,0], K = 3
Output: 3
Explanation:
Flip A[0],A[1],A[2]: A becomes [1,1,1,1,0,1,1,0]
Flip A[4],A[5],A[6]: A becomes [1,1,1,1,1,0,0,0]
Flip A[5],A[6],A[7]: A becomes [1,1,1,1,1,1,1,1]

*/


class Solution {
public:
	int minKBitFlips(vector<int>& A, int K) {
		vector<int> flips(A.size() + 1, 0);
		int ans = 0;

		for (int i = 0; i <= A.size()-K; i++) {
			// take cumulative sum
			flips[i] += i>0 ? flips[i-1] : 0;
			if (val(A[i], flips[i]) == 1)
				continue;
			// need to flip a window of K length (starting here)
			flips[i]++;
			flips[i+K]--;
			ans++;
		}

		// verify if last K-1 elements (remaining ele of last window) are 1
		for (int i = A.size()-K+1; i < A.size(); i++) {
			flips[i] += i>0 ? flips[i-1] : 0;
			if (val(A[i], flips[i]) == 0)
				return -1;
		}

		return ans;
	}

	int val(int n, int flip) {
		if (flip % 2 == 0) return n;
		return n == 0 ? 1 : 0;
	}
};







// use bool array for flips

class Solution {
public:
	int minKBitFlips(vector<int>& A, int K) {
		vector<bool> flips(A.size() + 1, false);
		int ans = 0;

		for (int i = 0; i <= A.size()-K; i++) {
			// take cumulative sum
			flips[i] = i>0 ? flips[i] ^ flips[i-1] : flips[i];
			if (val(A[i], flips[i]) == 1)
				continue;
			// need to flip a window of K length (starting here)
			flips[i] = !flips[i];
			flips[i+K] = !flips[i+K];
			ans++;
		}

		// verify if last K-1 elements are 1 or not
		for (int i = A.size()-K+1; i < A.size(); i++) {
			flips[i] = i>0 ? flips[i] ^ flips[i-1] : flips[i];
			if (val(A[i], flips[i]) == 0)
				return -1;
		}

		return ans;
	}

	int val(int n, bool flip) {
		if (flip == false) return n;
		return n == 0 ? 1 : 0;
	}
};







// use second bit to store flips
