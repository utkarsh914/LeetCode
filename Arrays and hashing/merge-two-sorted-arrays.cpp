// https://practice.geeksforgeeks.org/problems/merge-two-sorted-arrays-1587115620/1#

/*
Given two sorted arrays arr1[] and arr2[] of sizes n and m in non-decreasing order. Merge them in sorted order without using any extra space. Modify arr1 so that it contains the first N elements and modify arr2 so that it contains the last M elements.
 

Example 1:

Input: 
n = 4, arr1[] = [1 3 5 7] 
m = 5, arr2[] = [0 2 6 8 9]
Output: 
arr1[] = [0 1 2 3]
arr2[] = [5 6 7 8 9]
Explanation:
After merging the two 
non-decreasing arrays, we get, 
0 1 2 3 5 6 7 8 9.
Example 2:

Input: 
n = 2, arr1[] = [10, 12] 
m = 3, arr2[] = [5 18 20]
Output: 
arr1[] = [5 10]
arr2[] = [12 18 20]
Explanation:
After merging two sorted arrays 
we get 5 10 12 18 20.


Your Task:
You don't need to read input or print anything. You only need to complete the function merge() that takes arr1, arr2, n and m as input parameters and modifies them in-place so that they look like the sorted merged array when concatenated.
 

Expected Time Complexity:  O((n+m) log(n+m))
Expected Auxilliary Space: O(1)
 

Constraints:
1 <= n, m <= 5*104
0 <= arr1i, arr2i <= 107
*/




class Solution{
public:
	//Function to merge the arrays.
	void merge(long long *A, long long *B, int n, int m) {
		int partition = getPartition(A, B, n, m);
		// now swap all n - partition ele from B into A
		for (int i = partition, j = 0; i < n; i++, j++) {
			swap(A[i], B[j]);
		}
		
		// sort both arrays
		sort(A, A+n);
		sort(B, B+m);
	}


	int getPartition(long long *A, long long *B, int n, int m) {
		// find partition index in A
		int lo = 0, hi = n, partition = n;
		// in case A is longer than B, p2 becomes valid, so it fixes that
		if (n > m) {
			lo = n - m;
		}
		
		while (lo <= hi) {

			int pA = (lo + hi) / 2; // partition for A
			int pB = n - pA; // partition for B
			
			int lA = getLeft(A, n, pA);
			int rA = getRight(A, n, pA);
			int lB = getLeft(B, m, pB);
			int rB = getRight(B, m, pB);
			
			if (lA <= rB and lB <= rA) {
				partition = pA;
				break;
			}
			if (lA > rB) hi = pA - 1;
			else lo = pA + 1;
		}

		return partition;
	}
	
	long getLeft(long long * A, int n, int i) {
		if (i == 0) return INT_MIN;
		return A[i-1];
	}
	
	long getRight(long long * A, int n, int i) {
		if (i == n) return INT_MAX;
		return A[i];
	}
};