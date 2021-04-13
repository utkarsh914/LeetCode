// https://leetcode.com/problems/3sum-with-multiplicity/

/*
Given an integer array arr, and an integer target,
return the number of tuples i, j, k such that i < j < k and arr[i] + arr[j] + arr[k] == target.

As the answer can be very large, return it modulo 109 + 7.

Example 1:

Input: arr = [1,1,2,2,3,3,4,4,5,5], target = 8
Output: 20
Explanation: 
Enumerating by the values (arr[i], arr[j], arr[k]):
(1, 2, 5) occurs 8 times;
(1, 3, 4) occurs 8 times;
(2, 2, 4) occurs 2 times;
(2, 3, 3) occurs 2 times.
*/


// Build a map for counting different sums of two numbers
class Solution {
public:
	int threeSumMulti(vector<int>& A, int target) {
		unordered_map<int,int> m;
		long long count = 0, mod = 1e9+7;
		
		for (int i=0; i < A.size(); i++) {
			count = (count + m[target-A[i]]) % mod;
			
			for (int j=0; j < i; j++) {
				m[A[i]+A[j]]++;
			}
		}
		
		return count;
	}
};




/*
Count the occurrence of each number.
using hashmap or array up to you.

Loop i on all numbers,
loop j on all numbers,
check if k = target - i - j is valid.

Add the number of this combination to result.
3 cases covers all possible combination:

i == j == k
i == j != k
i < k && j < k
Time Complexity:
3 <= A.length <= 3000, so N = 3000
But 0 <= A[i] <= 100
So my solution is O(N + 101 * 101)
*/
// Build a map for counting different sums of two numbers
class Solution {
public:
	int threeSumMulti(vector<int>& A, int target) {
		unordered_map<int, long> c;
		for (int a : A) c[a]++;
		long res = 0;
		for (auto it : c)
			for (auto it2 : c) {
				int i = it.first, j = it2.first, k = target - i - j;
				if (!c.count(k)) continue;
				if (i == j && j == k)
					res += c[i] * (c[i] - 1) * (c[i] - 2) / 6;
				else if (i == j && j != k)
					res += c[i] * (c[i] - 1) / 2 * c[k];
				else if (i < j && j < k)
					res += c[i] * c[j] * c[k];
			}
		return res % int(1e9 + 7);
	}
};