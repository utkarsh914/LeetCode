// https://leetcode.com/problems/three-equal-parts/

/*
You are given an array arr which consists of only zeros and ones, divide the array into three non-empty parts such that all of these parts represent the same binary value.

If it is possible, return any [i, j] with i + 1 < j, such that:

arr[0], arr[1], ..., arr[i] is the first part,
arr[i + 1], arr[i + 2], ..., arr[j - 1] is the second part, and
arr[j], arr[j + 1], ..., arr[arr.length - 1] is the third part.
All three parts have equal binary values.
If it is not possible, return [-1, -1].

Note that the entire part is used when considering what binary value it represents. For example, [1,1,0] represents 6 in decimal, not 3. Also, leading zeros are allowed, so [0,1,1] and [1,1] represent the same value.

 

Example 1:

Input: arr = [1,0,1,0,1]
Output: [0,3]
Example 2:

Input: arr = [1,1,0,1,1]
Output: [-1,-1]
Example 3:

Input: arr = [1,1,0,0,1]
Output: [0,2]
 

Constraints:

3 <= arr.length <= 3 * 104
arr[i] is 0 or 1
*/








/*
What is 'same binary value' like?
Digits following first 1 in each part should be identical.

How could we decide which 1 is the first 1 of a divided part?

Assuming numOnes is number of 1s in A,
each part should be with numOnesPerPart = numOnes / 3 1s.
So the first '1' in left part is 1st '1',
first '1' in middle part is numOnesPerPart + 1th '1',
first '1' in right part is numOnesPerPart * 2 + 1th '1'.

Then we compare the rest part digit by digit. Hopefully,
the pointer in right part will reach A.length,
which means we can make three equal parts.

There is a corner case such as all elements in A are 0s.
*/
class Solution {
public:
	vector<int> threeEqualParts(vector<int>& A) {
		int n = count(A.begin(), A.end(), 1);
		if (n % 3 != 0) return {-1,-1};
		n /= 3;
		
		// find the starting indices of first, second, third substrings
		int left = -1, mid = -1, right = -1;
		for (int i = 0, c = 0; i < A.size(); i++) {
			if (A[i] == 0) continue;
			++c;
			if (c == 1) left = i;
			else if (c == n+1) mid = i;
			else if (c == 2*n+1) right = i;
		}

		// compare all three substrings
		while (left < mid and mid < right and right < A.size()) {
			if (A[left] == A[mid] and A[mid] == A[right])
				left++, mid++, right++;
			else break;
		}

		// if matched fully
		if (right == A.size()) return { left-1, mid };
		// if all 0's, and no 1's
		else if (right == -1) return { 0 , A.size()-1 };
		// otherwise
		else return {-1, -1};
	}
};