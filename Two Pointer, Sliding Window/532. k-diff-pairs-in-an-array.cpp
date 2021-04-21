// https://leetcode.com/problems/k-diff-pairs-in-an-array/

/*
Given an array of integers nums and an integer k,
return the number of unique k-diff pairs in the array.

A k-diff pair is an integer pair (nums[i], nums[j]), where the following are true:

0 <= i, j < nums.length
i != j
|nums[i] - nums[j]| == k
Notice that |val| denotes the absolute value of val.
*/

// need to handle k==0 specially
class Solution {
public:
	int findPairs(vector<int>& nums, int k) {
		int c = 0;
		unordered_map<int, int> map;

		for (int n : nums) {
			if (map.count(n)) {
				c += (k==0 and map[n]==1);
			}
			else {
				c += map.count(n-k);
				c += map.count(n+k);
			}
			map[n]++;
		}
		return c;
	}
};


// can be solved with 2 pointer.
// similar to 2-sum problem