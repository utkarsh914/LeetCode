// https://leetcode.com/problems/smallest-range-ii/

/*
Given an array A of integers, for each integer A[i] we need to choose either x = -K or x = K, and add x to A[i] (only once).
After this process, we have some array B.
Return the smallest possible difference between the maximum value of B and the minimum value of B.

Example 1:

Input: A = [1], K = 0
Output: 0
Explanation: B = [1]
Example 2:

Input: A = [0,10], K = 2
Output: 6
Explanation: B = [2,8]
Example 3:

Input: A = [1,3,6], K = 3
Output: 3
Explanation: B = [4,6,3]
*/



/*
The idea is to minimize the difference between max and min:

Max value tends to become smaller
Min value tends to become larger
Cause A[i] < A[i + 1], to minimize the difference:

make smaller larger: A[i] + K, A[0] + K
make larger smaller: A[i + 1] - K, A[-1] - K
Update the Max and Min:

max: max(A[-1] - K, A[i] + K)
min: min(A[0] + K, A[i + 1] - K)
Update the result:

res = max - min
We know, A - B = (A + K) - (B + K),

res = max - min = max(A[-1] - K, A[i] + K) - min(A[0] + K, A[i + 1] - K)
res = max - min = max(A[-1], A[i] + 2 * K) - min(A[0] + 2 * K, A[i + 1])
*/

class Solution {
public:
	int smallestRangeII(vector<int>& A, int K) {
		sort(A.begin(), A.end());
		int n=A.size(), mx=A[n-1], mn=A[0], diff=mx-mn;
		for (int i=0; i<n-1; i++) {
			mx = max(A[n-1]-K, A[i]+K);
			mn = min(A[i+1]-K, A[0]+K);
			diff = min(diff, mx-mn);
		}
		return diff;
	}
};




/*
Sort the vector.
Assuming there is a point, on the left of the point, all elements add K, on the right of the point,
all elements substract K,check each possible point. (a point is between two numbers).

we're making the array in this form
(A[0]+K, A[1]+K, ..., A[i]+K, A[i+1]-K, ..., A[n]-K)
trying out all the possible points to split. (left has +K, right hs -K );
*/
class Solution {
public:
	int smallestRangeII(vector<int>& A, int K) {
		sort(A.begin(), A.end());
		int res = A[A.size() - 1] - A[0];
		int left = A[0] + K, right = A[A.size() - 1] - K;
		for (int i = 0; i < A.size() - 1; i++) {
			int maxi = max(A[i] + K, right), mini = min(left, A[i + 1] - K);
			res = min(res, maxi - mini);
		}
		return res;
	}
};
/*
More explanation:
Cause there are two segments (A[0]+K, A[1]+K, ..., A[i]+K, A[i+1]-K, ..., A[n]-K),
the first one is on the left of the current point (A[i] + K is the last element of the first segment),
the second one is on the right of the current point (A[i + 1] - K is the first element of the second segment).
For the first segment, the smallest element is left, the largest is A[i] + K;
For the second segment, A[i + 1] - K is the smallest element, the largest is right.
Thus, for each point, the largest element should be either A[i] + K or right,
the smallest element should be either left or A[i + 1] - K.
*/