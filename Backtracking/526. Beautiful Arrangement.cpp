// https://leetcode.com/problems/beautiful-arrangement/

/*
Suppose you have n integers labeled 1 through n.
A permutation of those n integers perm (1-indexed) is considered a beautiful arrangement
if for every i (1 <= i <= n), either of the following is true:

perm[i] is divisible by i.
i is divisible by perm[i].
Given an integer n, return the number of the beautiful arrangements that you can construct.

 

Example 1:

Input: n = 2
Output: 2
Explanation: 
The first beautiful arrangement is [1,2]:
    - perm[1] = 1 is divisible by i = 1
    - perm[2] = 2 is divisible by i = 2
The second beautiful arrangement is [2,1]:
    - perm[1] = 2 is divisible by i = 1
    - i = 2 is divisible by perm[2] = 1
Example 2:

Input: n = 1
Output: 1
 

Constraints:

1 <= n <= 15
*/









/*
use bitmask to mark the numbers (1 to n) that have been taken previously.

at current index, try placing all the numbers in range [1,n]
if a number satisfies the condition to be placed, place it (mark in bitmask), 
and recur on remaining part


time complexity:

if k = # of valid permutations
greater than O(k), and less than O(N!)


Even though some of the iterations will get counted in k,
we are wasting others because for loop always runs from 1 to N
*/
class Solution {
	int ans, n;
public:
	int countArrangement(int n) {
		this->ans = 0;
		this->n = n;
		backtrack(1, 0);
		return ans;
	}

	void backtrack(int index, int mask) {
		if (index > n) {
			ans++;
			return;
		}

		for (int i = 1; i <= n; i++) {
			if (mask & (1 << i)) continue;
			if (i % index == 0 or index % i == 0) {
				backtrack(index + 1, mask | (1 << i));
			}
		}
	}
};



// shorter by using default parameters
class Solution {
public:
	int countArrangement(int N, int index = 1, int mask = 0) {
		if (index > N) return 1;

		int ans = 0;
		for (int i = 1; i <= N; i++) {
			if (mask & (1 << i)) continue;
			if (i % index == 0 or index % i == 0) {
				ans += countArrangement(N, index + 1, mask | (1 << i));
			}
		}

		return ans;
	}
};