// https://leetcode.com/problems/sum-of-floored-pairs/

/*
Given an integer array nums, return the sum of floor(nums[i] / nums[j])
for all pairs of indices 0 <= i, j < nums.length in the array.
Since the answer may be too large, return it modulo 109 + 7.

The floor() function returns the integer part of the division.


Example 1:

Input: nums = [2,5,9]
Output: 10
Explanation:
floor(2 / 5) = floor(2 / 9) = floor(5 / 9) = 0
floor(2 / 2) = floor(5 / 5) = floor(9 / 9) = 1
floor(5 / 2) = 2
floor(9 / 2) = 4
floor(9 / 5) = 1

We calculate the floor of the division for every pair of indices
in the array then sum them up.

Example 2:

Input: nums = [7,7,7,7,7,7,7]
Output: 49
 

Constraints:

1 <= nums.length <= 105
1 <= nums[i] <= 105
*/











/*
--- HINTS ---
Find the frequency (number of occurrences) of all elements in the array.
For each element, iterate through its multiples and multiply frequencies to find the answer.
*/







/*
I fix every number as denominator once,
and check how many count of numbers in the array can give
quotient as 0, 1, 2, 3, 4....
let number is 5.
so, numbers in range
[0,4] -> q = 0
[5,9] -> q = 1
[10,14] -> q = 2
and so on...

we just need to know the count of elements in those ranges,
and sum the value of (count * quotient)



now, to deal with duplicate elements
let [7,7,7,7]
if we fix each 7 at once, it will create the same sum as any other 7
so, instead of repeating the work for every 7, just store calculate for once
and multiply by freq of 7.

so, we iterate over unique elements, and use
	ans += q * count * freq

*/
class Solution {
public:
	int sumOfFlooredPairs(vector<int>& A) {
		long mx = *max_element(A.begin(), A.end());
		vector<int> bucket(mx + 1, 0);
		for (int n : A) bucket[n]++;
		// generate cumulative count
		vector<int> precount = bucket;
		for (int i = 1; i < bucket.size(); i++)
			precount[i] += precount[i-1];
		
		unordered_map<int, int> map;
		for (int n : A) map[n]++;
		
		long ans = 0, mod = 1e9+7;
		for (auto [n, freq] : map) {
			/*
			e.g. n = 5, so
			check how many ele lie in range [0,4], [5,9], [10,14]
			which will give quotient as 0, 1, 2 respectively when divided by 5
			*/
			long q = 1, left = n, right = min(mx, left+n-1);
			while (left <= right and right <= mx) {
				long count = precount[right] - precount[left] + bucket[left];
				ans = (ans + q * count * freq) % mod;
				left = right + 1;
				right = min(mx, left + n - 1);
				q++;
			}
		}
		
		return ans;
	}
};





// optimized: use bucket array as freq map
class Solution {
public:
	int sumOfFlooredPairs(vector<int>& A) {
		long mx = *max_element(A.begin(), A.end());
		vector<int> bucket(mx + 1, 0);
		for (int n : A) bucket[n]++;
		// generate cumulative count
		vector<int> precount = bucket;
		for (int i = 1; i < bucket.size(); i++)
			precount[i] += precount[i-1];
		
		long ans = 0, mod = 1e9+7;
		
		for (int i = 0; i < bucket.size(); i++) {
			long n = i, freq = bucket[i];
			if (freq == 0) continue;
			long q = 1, left = n, right = min(mx, left+n-1);
			while (left <= right and right <= mx) {
				long count = precount[right] - precount[left] + bucket[left];
				ans = (ans + q * count * freq) % mod;
				left = right + 1;
				right = min(mx, left + n - 1);
				q++;
			}
		}
		
		return ans;
	}
};