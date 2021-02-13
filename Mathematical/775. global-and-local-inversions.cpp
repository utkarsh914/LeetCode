// https://leetcode.com/problems/global-and-local-inversions/

/*
We have some permutation A of [0, 1, ..., N - 1], where N is the length of A.
The number of (global) inversions is the number of i < j with 0 <= i < j < N and A[i] > A[j].
The number of local inversions is the number of i with 0 <= i < N and A[i] > A[i+1].
Return true if and only if the number of global inversions is equal to the number of local inversions.

Example 1:

Input: A = [1,0,2]
Output: true
Explanation: There is 1 global inversion, and 1 local inversion.
Example 2:

Input: A = [1,2,0]
Output: false
Explanation: There are 2 global inversions, and 1 local inversion.
*/

/*
The original order should be [0, 1, 2, 3, 4...], the number i should be on the position i.
We just check the offset of each number, if the absolute value is larger than 1,
means the number of global inversion must be bigger than local inversion,
because a local inversion is a global inversion, but a global one may not be local.
*/
class Solution {
public:
	bool isIdealPermutation(vector<int>& A) {
		for (int i=0; i<A.size(); i++)
			if (abs(A[i] - i) > 1)
				return false;
		return true;
	}
};