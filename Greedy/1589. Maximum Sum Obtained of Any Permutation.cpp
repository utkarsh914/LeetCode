// https://leetcode.com/problems/maximum-sum-obtained-of-any-permutation/

/*
We have an array of integers, nums, and an array of requests
where requests[i] = [starti, endi]. The ith request asks for the sum of
nums[starti] + nums[starti + 1] + ... + nums[endi - 1] + nums[endi].
Both starti and endi are 0-indexed.

Return the maximum total sum of all requests among all permutations of nums.

Since the answer may be too large, return it modulo 109 + 7.

 

Example 1:

Input: nums = [1,2,3,4,5], requests = [[1,3],[0,1]]
Output: 19
Explanation: One permutation of nums is [2,1,3,4,5] with the following result: 
requests[0] -> nums[1] + nums[2] + nums[3] = 1 + 3 + 4 = 8
requests[1] -> nums[0] + nums[1] = 2 + 1 = 3
Total sum: 8 + 3 = 11.
A permutation with a higher total sum is [3,5,4,2,1] with the following result:
requests[0] -> nums[1] + nums[2] + nums[3] = 5 + 4 + 2 = 11
requests[1] -> nums[0] + nums[1] = 3 + 5  = 8
Total sum: 11 + 8 = 19, which is the best that you can do.
*/








/*
Intuition
We want to calculate the frequency for A[i].
Assign the big element A[i] to the position queried more frequently.


Explanation
For each request [i,j],
we set count[i]++ and count[j + 1]--,

Then we sweep once the whole count,
we can find the frequency for count[i].

Note that for all intervals inputs,
this method should be the first intuition you come up with.


Complexity
Time O(NlogN) for sorting
Space O(N)
*/
class Solution {
public:
	int maxSumRangeQuery(vector<int>& nums, vector<vector<int>>& req) {
		int size = nums.size();
		vector<int> freq(size+1);
		for (auto& r : req) {
			freq[r[0]]++, freq[r[1]+1]--;
		}
		for (int i = 1; i < freq.size(); i++)
			freq[i] += freq[i-1];
		// sort
		sort(freq.begin(), freq.end(), greater<int>());
		sort(nums.begin(), nums.end(), greater<int>());

		long ans = 0, mod = 1e9+7;
		for (int i = 0; i < size and freq[i] > 0; i++) {
			ans = (ans + long(freq[i]) * long(nums[i])) % mod;
		}
		return ans;
	}
};