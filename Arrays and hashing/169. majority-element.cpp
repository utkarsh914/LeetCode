/*
https://leetcode.com/problems/majority-element/
*/

class Solution {
public:
	int majorityElement(vector<int>& nums) {
		return majority(nums, 0, nums.size()-1).first;
	}

	pair<int,int> majority(vector<int>& nums, int start, int end) {
		if (start==end) return {nums[start], 1};
		int mid = (start+end)/2;
		pair<int,int> left=majority(nums, start, mid), right=majority(nums, mid+1, end);
		// if left majority and right majority are equal
		if (left.first == right.first)
			return {left.first, left.second+right.second};
		// if right extra is greater, return right majority
		else if (right.second > left.second)
			return {right.first, right.second-left.second};
		// if left extra is greater or equal, return left majority
		else
			return {left.first, left.second-right.second};
	}
};