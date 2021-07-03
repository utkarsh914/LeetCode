// https://leetcode.com/problems/find-xor-sum-of-all-pairs-bitwise-and/submissions/

/*
The XOR sum of a list is the bitwise XOR of all its elements.
If the list only contains one element, then its XOR sum will be equal to this element.

For example, the XOR sum of [1,2,3,4] is equal to 1 XOR 2 XOR 3 XOR 4 = 4, and the XOR sum of [3] is equal to 3.
You are given two 0-indexed arrays arr1 and arr2 that consist only of non-negative integers.

Consider the list containing the result of arr1[i] AND arr2[j] (bitwise AND) for every (i, j) pair where 0 <= i < arr1.length and 0 <= j < arr2.length.

Return the XOR sum of the aforementioned list.

 

Example 1:

Input: arr1 = [1,2,3], arr2 = [6,5]
Output: 0
Explanation: The list = [1 AND 6, 1 AND 5, 2 AND 6, 2 AND 5, 3 AND 6, 3 AND 5] = [0,1,2,0,2,1].
The XOR sum = 0 XOR 1 XOR 2 XOR 0 XOR 2 XOR 1 = 0.
Example 2:

Input: arr1 = [12], arr2 = [4]
Output: 4
Explanation: The list = [12 AND 4] = [4]. The XOR sum = 4.
 

Constraints:

1 <= arr1.length, arr2.length <= 105
0 <= arr1[i], arr2[j] <= 109
*/










class Solution {
public:
	int getXORSum(vector<int>& A1, vector<int>& A2) {
		// store how many numbers in array have their ith bit set
		unordered_map<int, long> map1, map2;
		// store bit freq map of first array
		for (int n : A1) {
			for (int i = 0; i < 32; i++)
				if (n & (1 << i)) map1[i]++;
		}
		// store bit freq map of second array
		for (int n : A2) {
			for (int i = 0; i < 32; i++)
				if (n & (1 << i)) map2[i]++;
		}
		
		int ans = 0;
		// ith bit of answer will be set only if there are
		// an odd number of pairs whose AND has ith bit set.
		for (int i = 0; i < 32; i++) {
			long totalPairs = map1[i] * map2[i];
			if (totalPairs % 2 == 1)
				ans = ans | (1 << i);
		}
		
		return ans;
	}
};







/*
Intuition
We all know the distributive property that (a1+a2)*(b1+b2) = a1*b1 + a1*b2 + a2*b1 + a2*b2

Now focus on each bit,
for example the last bit of A[i] and B[j],
and think how it works and affect the result.


Explanation
Distributive property is similar for AND and XOR here.
(a1^a2) & (b1^b2) = (a1&b1) ^ (a1&b2) ^ (a2&b1) ^ (a2&b2)
(I wasn't aware of this at first either)


Complexity
Time O(A + B)
Space O(1)

*/

int getXORSum(vector<int>& A, vector<int>& B) {
	int xora = 0, xorb = 0;
	for (int& a: A)
		xora ^= a;
	for (int& b: B)
		xorb ^= b;
	return xora & xorb;
}