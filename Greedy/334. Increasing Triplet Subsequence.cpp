// https://leetcode.com/problems/increasing-triplet-subsequence/

/*
Given an integer array nums, return true if there exists a triple of indices (i, j, k) such that i < j < k and nums[i] < nums[j] < nums[k]. If no such indices exists, return false.

 

Example 1:

Input: nums = [1,2,3,4,5]
Output: true
Explanation: Any triplet where i < j < k is valid.
Example 2:

Input: nums = [5,4,3,2,1]
Output: false
Explanation: No triplet exists.
Example 3:

Input: nums = [2,1,5,0,4,6]
Output: true
Explanation: The triplet (3, 4, 5) is valid because nums[3] == 0 < nums[4] == 4 < nums[5] == 6.
 

Constraints:

1 <= nums.length <= 5 * 105
-231 <= nums[i] <= 231 - 1
 

Follow up: Could you implement a solution that runs in O(n) time complexity and O(1) space complexity?
*/








/*
There is a O(nlogk) solution to LIS ,
where n is the array length and k is the length of LIS.
Here, k is no larger than 2, so it is O(nlog2) = O(n).
Very well, a O(n) solution is so easily obtained here:
*/

bool increasingTriplet(vector<int>& nums) {
	vector<int> dp;
	for (auto n : nums) {
		auto iter = lower_bound(begin(dp), end(dp), n);
		if (iter == end(dp)) dp.push_back(n);
		else *iter = n;
		if (dp.size() == 3) return true;
	}
	return false;
}
/*
The only difference between LIS and this problem is the check "if (dp.size() == 3)";
For comparison, this is the code to return the LIS of the input nums:
You can copy-paste it to the LIS problem and pass it actually.
*/
int LIS(vector<int>& nums) {
	vector<int> dp;
	for (auto n : nums) {
		auto iter = lower_bound(begin(dp), end(dp), n);
		if (iter == end(dp)) dp.push_back(n);
		else *iter = n;
		if (dp.size() == 3) return true;
	}
	return dp.size();
}

/*
Apparently, as you may have already noticed,
the "dp" here contains at most 2 elements,
so one instant simplification here is to replace "lower_bound" call
to a simple "if comparison else comparison".
Then a much more simplified version is obtained:
*/
class Solution {
public:
	bool increasingTriplet(vector<int>& nums) {
		int a = INT_MAX, b = INT_MAX;
		for (auto n : nums) {
			if (n <= a) a = n; // same as if lower bound is index 0
			else if (n <= b) b = n; // same as if lower bound is index 1
			else return true; // same as if lower bound is index 2 (i.e. doesn't exist)
		}
		return false;
	}
};
/*
Here, it is so easy to understand:
it is just a simple version of Binary Search for 2 elements --
the replacement of lower_bound in above solution.
*/








/*
start with two largest values, as soon as
we find a number bigger than both,
while both have been updated, return true.
*/
bool increasingTriplet(vector<int>& nums) {
	int first = INT_MAX, second = INT_MAX;
	for (int& n : nums) {
		if (n <= first) first = n; // update small if n is smaller than both
		else if (n <= second) second = n; // // update big only if greater than small but smaller than big
		else return true; // return if you find a number bigger than both
	}
	return false;
}
/*
I argued myself it cannot pass the case like [1,2,0,3] since c1 is changed.
But when I take a closer look, it does [1,2,0,3] very well.
And I realize that c1 and c2 are indeed having the meaning of:

C1 = so far best candidate of end element of a one-cell subsequence
	to form a triplet subsequence

C2 = so far best candidate of end element of a two-cell subsequence
	to form a triplet subsequence
*/

