// https://leetcode.com/problems/number-of-sub-arrays-of-size-k-and-average-greater-than-or-equal-to-threshold/

class Solution {
public:
	int numOfSubarrays(vector<int>& A, int k, int threshold) {
		int sum = accumulate(A.begin(), A.begin()+k, 0);
		int count = (sum / k) >= threshold;

		for (int i = k; i < A.size(); i++) {
			sum += A[i] - A[i-k];
			if ((sum / k) >= threshold) count++;
		}

		return count;
	}
};