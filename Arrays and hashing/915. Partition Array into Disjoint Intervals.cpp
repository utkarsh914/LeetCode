// https://leetcode.com/problems/partition-array-into-disjoint-intervals/

/*
Given an array nums, partition it into two (contiguous) subarrays left and right so that:

Every element in left is less than or equal to every element in right.
left and right are non-empty.
left has the smallest possible size.
Return the length of left after such a partitioning.
It is guaranteed that such a partitioning exists.


Example 1:

Input: nums = [5,0,3,8,6]
Output: 3
Explanation: left = [5,0,3], right = [8,6]
Example 2:

Input: nums = [1,1,1,0,6,12]
Output: 4
Explanation: left = [1,1,1,0], right = [6,12]
*/


/*
need to keep track of leftMax and rightMin
and at partition, leftMax <= rightMin
*/
class Solution {
public:
	int partitionDisjoint(vector<int>& A) {
		int N = A.size();
		vector<int> leftMax(N), rightMin(N);
		// find left max upto i index
		for (int i = 0, mx = A[0]; i < N; i++) {
			mx = max(mx, A[i]);
			leftMax[i] = mx;
		}
		// find right max after i index (inclusive i.e. [i, N-1] )
		for (int i = N-1, mn = A[N-1]; i >= 0; i--) {
			mn = min(mn, A[i]);
			rightMin[i] = mn;
		}
		
		// select an index to partition
		for (int i = 0; i < N-1; i++) {
			if (leftMax[i] <= rightMin[i+1])
				return i+1;
		}
		
		return -1;
	}
};






// calculate leftMax on the fly
class Solution {
public:
	int partitionDisjoint(vector<int>& A) {
		int N = A.size();
		int rightMin[N];
		// find right max after i index (inclusive i.e. [i, N-1] )
		for (int i = N-1, mn = A[N-1]; i >= 0; i--) {
			mn = min(mn, A[i]);
			rightMin[i] = mn;
		}
		
		// select an index to partition
		// calculate leftMax on the fly
		for (int i = 0, leftMax = A[0]; i < N-1; i++) {
			leftMax = max(leftMax, A[i]);
			if (leftMax <= rightMin[i+1])
				return i+1;
		}
		
		return -1;
	}
};



/*
--------- ONE PASS O(1) space ---------

def partitionDisjoint(self, A):
	disjoint = 0
	curmax = leftmax = A[0]
	for i,num in enumerate(A):
		curmax = max(curmax, num)
		if num < leftmax:
			leftmax = curmax
			disjoint = i
	return disjoint + 1
*/