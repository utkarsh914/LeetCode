// https://leetcode.com/problems/maximum-of-absolute-value-expression/

/*
Given two arrays of integers with equal lengths, return the maximum value of:

|arr1[i] - arr1[j]| + |arr2[i] - arr2[j]| + |i - j|

where the maximum is taken over all 0 <= i, j < arr1.length.

Example 1:

Input: arr1 = [1,2,3,4], arr2 = [-1,4,5,6]
Output: 13

Example 2:

Input: arr1 = [1,-2,-5,0,10], arr2 = [0,-2,-1,-7,-4]
Output: 20
 

Constraints:

2 <= arr1.length == arr2.length <= 40000
-10^6 <= arr1[i], arr2[i] <= 10^6
*/








/*
explanation : https://leetcode.com/problems/maximum-of-absolute-value-expression/discuss/340075/c%2B%2B-beats-100-(both-time-and-memory)-with-algorithm-and-image
*/

	int fun(vector<int>& A, int n) {
		int max_sum = A[0], min_sum = A[0];  
		for (int i = 0; i < n; i++) { // Finding max and min sum value 
			max_sum = max(max_sum, A[i]);
			min_sum = min(min_sum, A[i]);
		} 
		return (max_sum-min_sum); 
	}
	
	int maxAbsValExpr(vector<int>& A1, vector<int>& A2) {
		int n = A1.size();
		vector<int> sum1(n,0), diff1(n,0), sum2(n,0), diff2(n,0);
		for(int i = 0; i < n; i++) {
			sum1[i]  = A1[i] + A2[i] + i;
			diff1[i] = A1[i] - A2[i] + i;
			sum2[i]  = A1[i] + A2[i] - i;
			diff2[i] = A1[i] - A2[i] - i;
		}		
		return max(max(fun(sum1,n), fun(diff1,n)), max(fun(sum2,n), fun(diff2,n)));
	}


/*
class Solution:
	def maxAbsValExpr(self, arr1: list, arr2: list) -> int:
		a = [arr1[i] + arr2[i] + i for i in range(len(arr1))]
		b = [arr1[i] + arr2[i] - i for i in range(len(arr1))]
		c = [arr1[i] - arr2[i] + i for i in range(len(arr1))]
		d = [arr1[i] - arr2[i] - i for i in range(len(arr1))]
		return max(map(lambda x: max(x) - min(x), (a, b, c, d)))
*/