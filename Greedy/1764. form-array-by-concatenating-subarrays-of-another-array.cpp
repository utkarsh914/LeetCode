// https://leetcode.com/problems/form-array-by-concatenating-subarrays-of-another-array/

/*
You are given a 2D integer array groups of length n.
You are also given an integer array nums.

You are asked if you can choose n disjoint subarrays from the array nums
such that the ith subarray is equal to groups[i] (0-indexed), and if i > 0,
the (i-1)th subarray appears before the ith subarray in nums
(i.e. the subarrays must be in the same order as groups).

Return true if you can do this task, and false otherwise.

Note that the subarrays are disjoint if and only
if there is no index k such that nums[k] belongs to more than one subarray.
A subarray is a contiguous sequence of elements within an array.

Example 1:

Input: groups = [[1,-1,-1],[3,-2,0]], nums = [1,-1,0,1,-1,-1,3,-2,0]
Output: true
Explanation: You can choose the 0th subarray as [1,-1,0,1,-1,-1,3,-2,0]
and the 1st one as [1,-1,0,1,-1,-1,3,-2,0].
These subarrays are disjoint as they share no common nums[k] element.

Example 2:

Input: groups = [[10,-2],[1,2,3,4]], nums = [1,2,3,4,10,-2]
Output: false
Explanation: Note that choosing the subarrays [1,2,3,4,10,-2] and [1,2,3,4,10,-2] is incorrect because they are not in the same order as in groups.
[10,-2] must come before [1,2,3,4].
*/




/*
1. When we use a subarray, the room for the next subarrays
	will be the suffix after the used subarray.

2. If we can match a group with multiple subarrays,
we should choose the first one, as this will just
leave the largest room for the next subarrays.
*/
class Solution {
public:
	bool canChoose(vector<vector<int>>& groups, vector<int>& nums) {
		int start = 0;
		for (auto& g : groups) {
			int next = rabinKarp(g, nums, start);
			if (next == start) return false;
			start = next;
		}
		return true;
	}

	// searches A inside B. returns ending index
	// on not found, returns start index of txt
	int rabinKarp(vector<int>& pat, vector<int>& txt, int start) {
		for (int i = start; i + pat.size() - 1 < txt.size(); i++) {
			bool matched = true;
			for (int j = 0; j < pat.size(); j++) {
				if (pat[j] != txt[i+j]) {
					matched = false; break;
				}
			}
			if (matched) {
				return i + pat.size();
			}
		}
		return start;
	}
};