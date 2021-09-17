// https://leetcode.com/problems/reverse-pairs/




/*
----- INTEGER OVERFLOW OCCURES bcz limit is INT_MIN <= A[i] <= INT_MAX
*/
class Solution {
	vector<int> temp;
public:
	int reversePairs(vector<int>& A) {
		int N = A.size();
		temp.resize(N);
		return mergeSort(A, 0, N-1);
	}

	int mergeSort(vector<int>& A, int lo, int hi) {
		if (lo == hi) return 0;
		int m = lo + (hi-lo) / 2;
		int reversedPairs = mergeSort(A, lo, m)
			+ mergeSort(A, m+1, hi)
			+ merge(A, lo, m, m+1, hi);
		return reversedPairs;
	}

	int merge(vector<int>& A, int lo1, int hi1, int lo2, int hi2) {
		int i = lo1, j = lo2, k = 0;
		int reversedPairs = 0;

		while (i <= hi1 and j <= hi2) {
			if (A[i] <= A[j]) temp[k++] = A[i++];
			else {
				temp[k++] = A[j];
				int lb = upper_bound(
					A.begin()+lo1, A.begin()+hi1+1, 2 * A[j])
					- A.begin();
				reversedPairs += hi1 - lb + 1;
				j++;
			}
		}

		while (i <= hi1) temp[k++] = A[i++];
		while (j <= hi2) temp[k++] = A[j++];

		// copy back the merged array
		for (i = lo1, k = 0; i <= hi2; i++, k++)
			A[i] = temp[k];

		return reversedPairs;
	}
};
/*
2 4  1 3 5

*/







class Solution {
	vector<int> temp;
public:
	int reversePairs(vector<int>& A) {
		int N = A.size();
		temp.resize(N);
		return mergeSort(A, 0, N-1);
	}

	int mergeSort(vector<int>& A, int lo, int hi) {
		if (lo == hi) return 0;
		int m = lo + (hi-lo) / 2;
		int reversedPairs = mergeSort(A, lo, m)
			+ mergeSort(A, m+1, hi)
			+ merge(A, lo, m, m+1, hi);
		return reversedPairs;
	}

	int merge(vector<int>& A, int lo1, int hi1, int lo2, int hi2) {
		int reversedPairs = 0;
		// count reversed pairs
		for (int idx = lo1; idx <= hi1; idx++) {
			int lb = lower_bound(
				A.begin()+lo2, A.begin()+hi2+1, A[idx] / 2.0)
				- A.begin();
			reversedPairs += lb - lo2;
		}

		// merge two arrays
		int i = lo1, j = lo2, k = 0;

		while (i <= hi1 and j <= hi2) {
			if (A[i] <= A[j]) temp[k++] = A[i++];
			else temp[k++] = A[j++];
		}
		while (i <= hi1) temp[k++] = A[i++];
		while (j <= hi2) temp[k++] = A[j++];

		// copy back the merged array
		for (i = lo1, k = 0; i <= hi2; i++, k++)
			A[i] = temp[k];

		return reversedPairs;
	}
};
/*
2 4  1 3 5
*/





// or just sort the array using built in sort
class Solution {
public:
	int reversePairs(vector<int>& A) {
		int N = A.size();
		return mergeSort(A, 0, N-1);
	}

	int mergeSort(vector<int>& A, int lo, int hi) {
		if (lo == hi) return 0;
		int m = lo + (hi-lo) / 2;
		int reversedPairs = mergeSort(A, lo, m)
			+ mergeSort(A, m+1, hi)
			+ merge(A, lo, m, m+1, hi);
		return reversedPairs;
	}

	int merge(vector<int>& A, int lo1, int hi1, int lo2, int hi2) {
		int reversedPairs = 0;
		// count reversed pairs
		for (int idx = lo1; idx <= hi1; idx++) {
			int lb = lower_bound(
				A.begin()+lo2, A.begin()+hi2+1, A[idx] / 2.0)
				- A.begin();
			reversedPairs += lb - lo2;
		}

		// merge two arrays (sort them)
		sort(A.begin()+lo1, A.begin()+hi2+1);

		return reversedPairs;
	}
};
/*
2 4  1 3 5
*/