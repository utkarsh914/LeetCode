// https://leetcode.com/problems/make-sum-divisible-by-p/

/*
Given an array of positive integers nums, remove the smallest subarray (possibly empty) such that the sum of the remaining elements is divisible by p. It is not allowed to remove the whole array.

Return the length of the smallest subarray that you need to remove, or -1 if it's impossible.

A subarray is defined as a contiguous block of elements in the array.

 

Example 1:

Input: nums = [3,1,4,2], p = 6
Output: 1
Explanation: The sum of the elements in nums is 10, which is not divisible by 6. We can remove the subarray [4], and the sum of the remaining elements is 6, which is divisible by 6.
Example 2:

Input: nums = [6,3,5,2], p = 9
Output: 2
Explanation: We cannot remove a single element to get a sum divisible by 9. The best way is to remove the subarray [5,2], leaving us with [6,3] with sum 9.
Example 3:

Input: nums = [1,2,3], p = 3
Output: 0
Explanation: Here the sum is 6. which is already divisible by 3. Thus we do not need to remove anything.
Example 4:

Input: nums = [1,2,3], p = 7
Output: -1
Explanation: There is no way to remove a subarray in order to get a sum divisible by 7.
Example 5:

Input: nums = [1000000000,1000000000,1000000000], p = 3
Output: 0
 

Constraints:

1 <= nums.length <= 105
1 <= nums[i] <= 109
1 <= p <= 109
*/









/*
Intuition
Calculate the need = sum(A) % p.
Then one pass, record the prefix sum in a hashmap.


Explanation
Then the question become:
Find the shortest array with sum % p = need.

last[remainder] = index records the last index that
(A[0] + A[1] + .. + A[i]) % p = remainder


Complexity
Time O(N)
Space O(N)
*/

int minSubarray(vector<int>& A, long p) {
	int ans = INT_MAX;
	int extra = accumulate(A.begin(), A.end(), 0L) % p;
	if (extra == 0) return 0;
	long sum = 0;
	unordered_map<int, int> map;
	map[0] = -1;
	
	for (int i = 0; i < A.size(); i++) {
		sum += A[i];
		int target = (sum % p) - extra;
		if (target < 0) target += p;
		if (map.count(target))
			ans = min(ans, i - map[target]);
		map[sum % p] = i;
	}
	
	return ans >= A.size() ? -1 : ans;
}


int minSubarray(vector<int>& A, int p) {
	int n = A.size(), res = n, need = 0, cur = 0;
	for (auto a : A)
		need = (need + a) % p;

	unordered_map<int, int> last = {{0, -1}};

	for (int i = 0; i < n; ++i) {
		cur = (cur + A[i]) % p;
		last[cur] = i;
		int want = (cur - need + p) % p;
		if (last.count(want))
			res = min(res, i - last[want]);
	}

	return res < n ? res : -1;
}