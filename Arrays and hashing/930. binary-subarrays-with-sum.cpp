// https://leetcode.com/problems/binary-subarrays-with-sum/

/*
In an array A of 0s and 1s, how many non-empty subarrays have sum S?

Example 1:

Input: A = [1,0,1,0,1], S = 2
Output: 4
Explanation: 
The 4 subarrays are bolded below:
[1,0,1,0,1]
[1,0,1,0,1]
[1,0,1,0,1]
[1,0,1,0,1]
*/



class Solution {
public:
	int numSubarraysWithSum(vector<int>& A, int S) {
		return atMostSum(A, S) - atMostSum(A, S-1);
	}

	int atMostSum(vector<int>& A, int S) {
		if (S < 0) return 0;
		int presum = 0, left = 0, count = 0;
		for (int right=0; right < A.size(); right++) {
			presum += A[right];
			while (presum > S)
				presum -= A[left++];
			count += right - left + 1;
		}
		return count;
	}
};