// https://leetcode.com/problems/number-of-subarrays-with-bounded-maximum/

/*
We are given an array nums of positive integers,
and two positive integers left and right (left <= right).

Return the number of (contiguous, non-empty) subarrays
such that the value of the maximum array element in that subarray
is at least left and at most right.

Example:
Input: 
nums = [2, 1, 4, 3]
left = 2
right = 3
Output: 3
Explanation: There are three subarrays that meet the requirements: [2], [2, 1], [3].
Note:

left, right, and nums[i] will be an integer in the range [0, 109].
The length of nums will be in the range of [1, 50000].
*/











/*
my idea is that, any A[i] > Right splits the array in parts
which are valid.
so, just sum the number of possible subarrays of each part

now these valid parts also contain ele < Left.
all subarrays having all (ele < Left) will have to be discarded from every part,
as their max will not be in range [L, R]

so, keep counting the streak of smaller ele.
when that streak ends, subtract the # of total subarrays possible from that streak
and reset the streak to zero
*/
class Solution {
public:
	int numSubarrayBoundedMax(vector<int>& A, int left, int right) {
		long smaller = 0, count = 0;
		
		for (int i = 0, prevInd = 0; i < A.size(); i++) {
			if (A[i] < left) {
				smaller++;
			} else {
				count -= (smaller * (smaller+1)) / 2;
				smaller = 0;
			}

			if (A[i] > right) {
				long n = i - prevInd;
				count += (n * (n+1)) / 2L;
				prevInd = i+1;
			}

			if (i == A.size()-1) {
				long n = A.size() - prevInd;
				count += (n * (n+1)) / 2L;
				count -= (smaller * (smaller+1)) / 2;
				smaller = 0;
			}
		}
		
		return count;
	}
};
/*
[16,69,88,85,79,87,37,33,39,34]
55
57
*/



class Solution {
public:
	int numSubarrayBoundedMax(vector<int>& A, int left, int right) {
		long smaller = 0, count = 0;
		
		for (int i = 0, prevInd = 0; i < A.size(); i++) {
			if (A[i] < left) {
				smaller++;
			}
			else if (A[i] > right) {
				long n = i - prevInd;
				count += (n * (n+1)) / 2L;
				prevInd = i+1;
				count -= (smaller * (smaller+1)) / 2;
				smaller = 0;
			}
			else {
				count -= (smaller * (smaller+1)) / 2;
				smaller = 0;
			}
			if (i == A.size()-1) {
				long n = A.size() - prevInd;
				count += (n * (n+1)) / 2L;
				count -= (smaller * (smaller+1)) / 2;
			}
		}
		
		return count;
	}
};
