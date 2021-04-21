// https://leetcode.com/problems/max-chunks-to-make-sorted/

/*
Given an array arr that is a permutation of [0, 1, ..., arr.length - 1],
we split the array into some number of "chunks" (partitions), and individually sort each chunk.
After concatenating them, the result equals the sorted array.

What is the most number of chunks we could have made?

Example 1:

Input: arr = [4,3,2,1,0]
Output: 1
Explanation:
Splitting into two or more chunks will not return the required result.
For example, splitting into [4, 3], [2, 1, 0] will result in [3, 4, 0, 1, 2], which isn't sorted.
*/



/*
======== MERGE INTERVALS ========

create intervals (a,b) for every element
which consists of current pos and the pos which that element should be in a sorted array.
then merge those intervals

total numbers of intervals remaining after merge operation is the answer
*/
class Solution {
public:
	int maxChunksToSorted(vector<int>& A) {
		vector<array<int,2>> intervals;
		for (int i = 0; i < A.size(); i++) {
			intervals.push_back({min(A[i],i), max(A[i],i)});
		}
		// merge those intervals, sort by starting time
		sort(intervals.begin(), intervals.end());
		int mergedCount = 1; // already considering the last merged interval
		for (int i = 1; i < intervals.size(); i++) {
			auto &prev = intervals[i-1], &cur = intervals[i];
			if (prev[1] >= cur[0]) {
				cur = {prev[0], max(prev[1], cur[1])};
			}
			else mergedCount++;
		}

		return mergedCount;
	}
};





/*
Iterate the array, if the max(A[0] ~ A[i]) = i,
then we can split the array into two chunks at this index.
*/
class Solution {
public:
	int maxChunksToSorted(vector<int>& A) {
		int ans = 0, curMax = INT_MIN;
		for (int i = 0; i < A.size(); i++) {
			curMax = max(curMax, A[i]);
			if (i == curMax) ans++;
		}
		return ans;
	}
};



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