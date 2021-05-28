// https://leetcode.com/problems/count-triplets-that-can-form-two-arrays-of-equal-xor/

/*
Given an array of integers arr.

We want to select three indices i, j and k where (0 <= i < j <= k < arr.length).

Let's define a and b as follows:

a = arr[i] ^ arr[i + 1] ^ ... ^ arr[j - 1]
b = arr[j] ^ arr[j + 1] ^ ... ^ arr[k]
Note that ^ denotes the bitwise-xor operation.

Return the number of triplets (i, j and k) Where a == b.

 

Example 1:

Input: arr = [2,3,1,6,7]
Output: 4
Explanation: The triplets are (0,1,2), (0,2,2), (2,3,4) and (2,4,4)
Example 2:

Input: arr = [1,1,1,1,1]
Output: 10
Example 3:

Input: arr = [2,3]
Output: 0
Example 4:

Input: arr = [1,3,5,7,9]
Output: 3
Example 5:

Input: arr = [7,11,12,9,5,2,7,17,22]
Output: 8
 

Constraints:

1 <= arr.length <= 300
1 <= arr[i] <= 10^8
*/









/*
We are searching for sub-array of length ≥ 2
and we need to split it to 2 non-empty arrays
so that the xor of the first array is equal to the xor of the second array.
This is equivalent to searching for sub-array with xor = 0.

let subarray is [i, j]
so we have (j-i) possible locations for k
so we add j-i to the count every time we find an array
*/
class Solution {
public:
	int countTriplets(vector<int>& A) {
		vector<int> preXOR(A.size());
		preXOR[0] = A[0];
		for (int i = 1; i < preXOR.size(); i++) {
			preXOR[i] = (preXOR[i-1] ^ A[i]);
		}

		int count = 0;
		for (int i = 0; i < A.size(); i++) {
			for (int j = i+1; j < A.size(); j++) {
				if ((preXOR[j] ^ preXOR[i] ^ A[i]) == 0)
					count += j-i;
			}
		}

		return count;
	}
};



// keep running xor value
// no need for preXOR array
class Solution {
public:
	int countTriplets(vector<int>& A) {
		int count = 0;
		for (int i = 0; i < A.size(); i++) {
			int exor = A[i];
			for (int j = i+1; j < A.size(); j++) {
				exor = exor ^ A[j];
				if (exor == 0) count += j-i;
			}
		}
		return count;
	}
};