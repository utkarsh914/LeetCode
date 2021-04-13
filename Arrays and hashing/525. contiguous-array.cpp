// https://leetcode.com/problems/contiguous-array/

/*
Given a binary array, find the maximum length of a contiguous subarray with equal number of 0 and 1.

Example 1:
Input: [0,1]
Output: 2
Explanation: [0, 1] is the longest contiguous subarray with equal number of 0 and 1.
*/

/*
treat 0 as -1. then problem becomes finding longest contiguous subarray
which has sum zero, and can be solved using hashmap
*/
class Solution {
public:
	int findMaxLength(vector<int>& n) {
		unordered_map<int,int> map;
		map[0] = -1;
		int ans = 0, sum = 0;
		for (int i=0; i<n.size(); i++) {
			sum += n[i]==0 ? -1 : 1;
			if (map.count(sum)) ans = max(ans, i-map[sum]);
			else map[sum] = i;
		}
		return ans;
	}
};