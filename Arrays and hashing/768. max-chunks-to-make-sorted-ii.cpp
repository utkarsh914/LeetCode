// https://leetcode.com/problems/max-chunks-to-make-sorted-ii/

/*
This question is the same as "Max Chunks to Make Sorted" except the integers of the given array are not necessarily distinct, the input array could be up to length 2000, and the elements could be up to 10**8.

Given an array arr of integers (not necessarily distinct), we split the array into some number of "chunks" (partitions), and individually sort each chunk.  After concatenating them, the result equals the sorted array.

What is the most number of chunks we could have made?

Example 1:

Input: arr = [5,4,3,2,1]
Output: 1
Explanation:
Splitting into two or more chunks will not return the required result.
For example, splitting into [5, 4], [3, 2, 1] will result in [4, 5, 1, 2, 3], which isn't sorted.
*/





/*
Iterate through the array,
each time all elements to the left are smaller (or equal)to all elements to the right,
there is a new chunck.
*/
class Solution {
public:
	int maxChunksToSorted(vector<int>& A) {
		int ans = 0, n = A.size();
		vector<int> maxOnLeft(n), minOnRight(n);

		maxOnLeft[0] = A[0];
		for (int i = 1; i < A.size(); i++) {
			maxOnLeft[i] = max(maxOnLeft[i-1], A[i]);
		}

		minOnRight[n-1] = A[n-1];
		for (int i = n-2; i >= 0; i--) {
			minOnRight[i] = min(minOnRight[i+1], A[i]);
		}

		for (int i = 0; i+1 < A.size(); i++) {
			if (maxOnLeft[i] <= minOnRight[i+1]) ans++;
		}

		return ans+1;
	}
};






/*
Using presum and sorted array
*/
class Solution {
public:
	int maxChunksToSorted(vector<int>& A) {
		vector<int> B = A;
		sort(B.begin(), B.end());
		long ans = 0, presum1 = 0, presum2 = 0;

		for (int i = 0; i < A.size(); i++) {
			presum1 += A[i];
			presum2 += B[i];
			if (presum1 == presum2) {
				// this is only needed to prevent possible overflow on addition
				// otherwise optional
				presum1 = presum2 = 0;
				ans++;
			}
		}

		return ans;
	}
};