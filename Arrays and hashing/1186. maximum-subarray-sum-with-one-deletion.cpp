// https://leetcode.com/problems/maximum-subarray-sum-with-one-deletion/

/*
Given an array of integers, return the maximum sum for a non-empty subarray (contiguous elements) with at most one element deletion. In other words, you want to choose a subarray and optionally delete one element from it so that there is still at least one element left and the sum of the remaining elements is maximum possible.

Note that the subarray needs to be non-empty after deleting one element.

Example 1:

Input: arr = [1,-2,0,3]
Output: 4
Explanation: Because we can choose [1, -2, 0, 3] and drop -2, thus the subarray [1, 0, 3] becomes the maximum value.
*/




// modified Kadane's algo
class Solution {
public:
	int maximumSum(vector<int>& arr) {
		int s, size = arr.size(), overall_max = INT_MIN;
		if (size == 1) return arr[0];

		vector<int> fw(size), bw(size);
		// (fw) calculate kadane's max subarray sum ending at that particular index i
		s = fw[0] = arr[0];
		for (int i=1; i < size; i++) {
			s = max(arr[i], arr[i]+s);
			overall_max = max(overall_max, s); // needed if no element should be deleted
			fw[i] = s;
		}
		// (bw) calculate kadane's max subarray sum starting at that particular index i
		s = bw[size-1] = arr[size-1];
		for (int i=size-2; i >= 0; i--) {
			s = max(arr[i], arr[i]+s);
			bw[i] = s;
		}

		// try deleting every element
		// and find the maximum subarray sum to both sides
		int ans = overall_max;
		for (int i=-1; i <= size; i++) {
			int ending_here = i>0 ? fw[i-1] : 0;
			int starting_here = i+1<size ? bw[i+1] : 0;
			ans = max(ans, ending_here + starting_here);
		}

		return ans;
	}
};