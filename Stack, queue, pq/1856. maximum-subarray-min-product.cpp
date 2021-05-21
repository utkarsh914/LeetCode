// https://leetcode.com/problems/maximum-subarray-min-product/

/*

*/





/*
The main idea is

1. As we want to find min-product, calculating minimum number from all sub arrays gives us TLE
2. So what we do is, we consider nums[i] where 0<=i< n, as min element and find the min-products of subarrays with minimum as nums[i].
3. First we find the prefix sum of given array.
4. Then we find the number of largest numbers to the left in "array left" and number of largest numbers to the right in "array right" with nums[i] as minimum.
5. After finding that, now its become simple, as we know the length of sub array with nums[i] as minimum.
6. To get starting index a, a = i-left[i]+1, and ending index b = i+right[i]-1.
7. Then process the res, as we know the sum of subarray as we have prefix sum and minimum element is nums[i].
8. Update the res by finding maximum of min-product.



count is the number of elements greater than or equal tonums[i] to its left from its position i, similar for the case in calculating right array.
For Example: consider array to be [2,3,5,1,6,4].
left[i] for index i =0 is 1, since there are no elements left to 2. so, counting itself gives 1. and right[i] = 3 as there are 2 more elements which are greater than 2 to its right.
In this case, cnt = 1 for index 0 while calculating left array, whereas cnt = 3 for index 0 while calculating right array.
*/

class Solution {
public:
	int maxSumMinProduct(vector<int>& A) {
		int size = A.size();
		int left[size], right[size];
		long presum[size];
		stack<array<int,2>> stk;

		// calculate for each i, on left of it, how many
		// contiguous elements are >= A[i] (including A[i])
		for (int i = 0; i < size; i++) {
			int count = 1;
			while (!stk.empty() and stk.top()[0] >= A[i])
				count += stk.top()[1], stk.pop();
			stk.push({ A[i], count });
			left[i] = count;
		}

		// calculate for each i, on right of it, how many
		// contiguous elements are >= A[i] (including A[i])
		stk = stack<array<int,2>> ();
		for (int i = size-1; i >= 0; i--) {
			int count = 1;
			while (!stk.empty() and stk.top()[0] >= A[i])
				count += stk.top()[1], stk.pop();
			stk.push({ A[i], count });
			right[i] = count;
		}

		// calculate presum
		presum[0] = A[0];
		for (int i = 1; i < size; i++) {
			presum[i] = presum[i-1] + A[i];
		}

		// now consider the largest subarray having A[i] as min ele
		// and calculate min-sum for every case
		long ans = INT_MIN;
		for (int i = 0; i < size; i++) {
			int l = i - left[i] + 1;
			int r = i + right[i] - 1;
			long sum = presum[r] - presum[l] + A[l];
			ans = max(ans, sum * A[i]);
		}

		return ans % 1000000007L;
	}
};