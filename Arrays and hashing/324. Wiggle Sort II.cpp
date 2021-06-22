// https://leetcode.com/problems/wiggle-sort-ii/









/*
first get the median.
now we have 3 types of elements in the array
smaller than median, equal to median, greater than it

(1) elements smaller than the 'median' are put into the last even slots
	put into indices 6, 4, 2, ... starting from the last

(2) elements larger than the 'median' are put into the first odd slots
	put into indices 1, 3, 5, ... starting from beginning(i.e. 1)

(3) the medians are put into the remaining slots.

*/
class Solution {
public:
	void wiggleSort(vector<int>& A) {
		int N = A.size();
		int mid = N/2;
		nth_element(A.begin(), A.begin() + mid, A.end());
		int median = A[mid];

		vector<int> B(N, INT_MAX);
		// elements smaller than the 'median' are put into the last even slots
		int i = N % 2 == 0 ? N-2 : N-1;
		for (int j = 0; j < N/2; j++) {
			if (A[j] < median) B[i] = A[j], i-=2;
		}
		// elements larger than the 'median' are put into the first odd slots
		i = 1;
		for (int j = N/2+1; j < N; j++) {
			if (A[j] > median) B[i] = A[j], i += 2;
		}
		// the medians are put into the remaining slots.
		for (int i = 0; i < N; i++) {
			if (B[i] == INT_MAX) B[i] = median;
		}

		A.swap(B);
	}
};
