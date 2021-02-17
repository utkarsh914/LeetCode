// https://leetcode.com/problems/partition-to-k-equal-sum-subsets/


/*
Given an array of integers nums and a positive integer k,
find whether it's possible to divide this array into k non-empty subsets whose sums are all equal.

Example 1:

Input: nums = [4, 3, 2, 3, 5, 2, 1], k = 4
Output: True
Explanation: It's possible to divide it into 4 subsets (5), (1, 4), (2,3), (2,3) with equal sums.

Note:
1 <= k <= len(nums) <= 16.
0 < nums[i] < 10000.
*/







/*
basic idea is to find a subset of sum = sum/k.
if found, search next subset. if found again, keep searching until all are found.

keep track of numbers which have been taken in any of the previously found sets.
While finding a set, take only untaken nums, and if answer isn't found by taking this num,
untake it, and backtrack by taking next untaken num, and repeat the same.

if all nums finished, and ans not found, return false.

This problem is NPC, so time complexity is exp O(n^k)
as for each number in nums we need to decide which target slot it belongs to.
*/
class Solution {
	vector<bool> taken;
	int target;
public:
	bool canPartitionKSubsets(vector<int>& n, int k) {
		int sum = accumulate(begin(n), end(n), 0);
		if (sum % k != 0) return false;
		
		taken.resize(n.size(), false);
		this->target = sum / k;
		return hasSubset(n, 0, k, 0, 0);
	}
	
	bool hasSubset(vector<int>& n, int start, int k, int sum, int nTaken) {
		if (k == 1) return true; // if k-1 subsets are already found, then all left nums should form the last subset
		if (sum == target && nTaken > 0) { // if a subset is found, and it is non-empty, find another set
			return hasSubset(n, 0, k-1, 0, 0);
		}

		for (int i=start; i < n.size(); i++) {
			if (!taken[i]) {
				taken[i] = true;
				if (hasSubset(n, i+1, k, sum+n[i], nTaken+1))
					return true;
				taken[i] = false;
			}
		}
		
		return false;
	}
};





/*
class Solution {
public:
	bool canPartitionKSubsets(vector<int>& n, int k) {
		int sum = accumulate(begin(n), end(n), 0);
		if (sum % k != 0) return false;
		
		vector<int> sums(k, sum/k);
		return hasSubset(n, k, 0, sums);
	}
	
	bool hasSubset(vector<int>& n, int k, int start, vector<int> sum) {
		if (start == n.size()) {
			for (int s:sum) if (s!=0) return false;
			return true;
		}
		
		for (int s:sum) if (s<0) return false;

		for (int i=0; i<k; i++) {
			sum[i] -= n[start];
			if (hasSubset(n, k, start+1, sum))
				return true;
		}
		
		return false;
	}
};
*/