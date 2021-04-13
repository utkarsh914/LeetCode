// https://leetcode.com/problems/maximum-value-at-a-given-index-in-a-bounded-array/

class Solution {
public:
	int maxValue(int size, int index, int maxSum) {
		int start = 1, end = maxSum, ans = 1;
		while (start <= end) {
			int mid = start + (end-start)/2;
			if (feasible(mid, size, index, maxSum))
				ans = mid, start = mid+1;
			else
				end = mid-1;
		}
		return ans;
	}

	bool feasible(int n, int size, int index, int maxSum) {
		long sum = n;
		long leftSum = getSum(n, index);
		long rightSum = getSum(n, size-index-1);
		sum += leftSum + rightSum;
		return sum <= (long)maxSum;
	}

	long getSum(int n, int index) {
		long x = min(n-1, index); // length of decreasing seq from n-1 till 1 inclusive
		long y = index - x; // length of seq having extra 1(s)
		long sum = y + ((n-x + n-1) * x) / (long)2;
		return sum;
	}
};









/*
Explanation
We first do maxSum -= n,
then all elements needs only to valid A[i] >= 0

We binary search the final result between left and right,
where left = 0 and right = maxSum.

For each test, we check minimum sum if A[index] = a.
The minimum case would be A[index] is a peak in A.
It's arithmetic sequence on the left of A[index] with difference is 1.
It's also arithmetic sequence on the right of A[index] with difference is -1.

On the left, A[0] = max(a - index, 0),
On the right, A[n - 1] = max(a - ((n - 1) - index), 0),

The sum of arithmetic sequence {b, b+1, ....a},
equals to (a + b) * (a - b + 1) / 2.


Complexity
Because O(test) is O(1)
Time O(log(maxSum))
Space O(1)
*/

class Solution {
public:
	int maxValue(int n, int index, int maxSum) {
		maxSum -= n;
		int left = 0, right = maxSum, mid;
		while (left < right) {
			mid = (left + right + 1) / 2;
			if (test(n, index, mid) <= maxSum)
				left = mid;
			else
				right = mid - 1;
		}
		return left + 1;
	}

	long test(int n, int index, int a) {
		int b = max(a - index, 0);
		long res = long(a + b) * (a - b + 1) / 2;
		b = max(a - ((n - 1) - index), 0);
		res += long(a + b) * (a - b + 1) / 2;
		return res - a;
	}
};
