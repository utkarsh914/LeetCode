// https://leetcode.com/problems/frequency-of-the-most-frequent-element/

/*
The frequency of an element is the number of times it occurs in an array.

You are given an integer array nums and an integer k.
In one operation, you can choose an index of nums
and increment the element at that index by 1.

Return the maximum possible frequency of an element after performing at most k operations.


Example 1:

Input: nums = [1,2,4], k = 5
Output: 3
Explanation: Increment the first element three times
and the second element two times to make nums = [4,4,4].
4 has a frequency of 3.

Example 2:

Input: nums = [1,4,8,13], k = 5
Output: 2
Explanation: There are multiple optimal solutions:
- Increment the first element three times to make nums = [4,4,8,13]. 4 has a frequency of 2.
- Increment the second element four times to make nums = [1,8,8,13]. 8 has a frequency of 2.
- Increment the third element five times to make nums = [1,4,13,13]. 13 has a frequency of 2.

Example 3:

Input: nums = [3,9,6], k = 2
Output: 1
 

Constraints:

1 <= nums.length <= 105
1 <= nums[i] <= 105
1 <= k <= 105
*/







/*
main idea is to do a binary search over presum
for every index i, we will find a lowerbound in range [0, i)
where we need to add a max of k amount to the range sum,
so that it becomes divisible by A[i].
*/
class Solution {
	vector<long> sum;
public:
	int maxFrequency(vector<int>& A, int k) {
		sort(A.begin(), A.end());
		// populate presum array
		sum.resize(A.size()+1, 0);
		for (int i = 1; i < sum.size(); i++)
			sum[i] = sum[i-1] + A[i-1];

		int ans = 1;
		for (int i = A.size()-1; i > 0; i--) {
			int lowerBound = binSearch(A, i, k, 0, i);
			ans = max(ans, i - lowerBound + 1);
		}

		return ans;
	}

	int binSearch(vector<int>& A, int i, long k, int lo, int hi) {
		while (lo < hi) {
			int m = lo + (hi-lo)/2;
			long presum = sum[i+1] - sum[m];
			long neededSum = long(A[i]) * long(i - m + 1);
			if (neededSum - presum <= k)
				hi = m;
			else lo = m+1;
		}
		return lo;
	}
};






/*
Intuition
Sort the input array A
Sliding window prolem actually,
the key is to find out the valid condition:
k + sum >= size * max
which is
k + sum >= (j - i + 1) * A[j]


Explanation
For every new element A[j] to the sliding window,
Add it to the sum by sum += A[j].
Check if it'a valid window by
sum + k < (long)A[j] * (j - i + 1)

If not, removing A[i] from the window by
sum -= A[i] and i += 1.

Then update the res by res = max(res, j - i + 1).

I added solution 1 for clearly expain the process above.
Don't forget to handle the overflow cases by using long.

*/


class Solution {
public:
	int maxFrequency(vector<int>& A, long k) {
		sort(A.begin(), A.end());

		long ans = 1, sum = 0;
		for (long i = 0, j = 0; j < A.size(); j++) {
			sum += A[j];
			long max_ = A[j];
			// remove from window until condition doesn't hold
			while (i < j and ((j-i+1L)*max_ - sum) > k)
				sum -= A[i++];
			// update ans
			ans = max(ans, j - i +1);
		}

		return ans;
	}
};



// OJ: https://leetcode.com/problems/frequency-of-the-most-frequent-element/
// Author: github.com/lzl124631x
// Time: O(NlogN)
// Space: O(1)

	int maxFrequency(vector<int>& A, int k) {
		sort(begin(A), end(A));
		long i = 0, ans = 1, sum = 0;
		for (int j = 0; j < A.size(); ++j) {
			sum += A[j];
			while ((j - i + 1) * A[j] - sum > k) sum -= A[i++];
			ans = max(ans, j - i + 1);
		}
		return ans;
	}