// https://leetcode.com/problems/count-nice-pairs-in-an-array/

/*
You are given an array nums that consists of non-negative integers. Let us define rev(x) as the reverse of the non-negative integer x. For example, rev(123) = 321, and rev(120) = 21. A pair of indices (i, j) is nice if it satisfies all of the following conditions:

0 <= i < j < nums.length
nums[i] + rev(nums[j]) == nums[j] + rev(nums[i])
Return the number of nice pairs of indices. Since that number can be too large, return it modulo 109 + 7.
*/



/*
Explanation
A[i] + rev(A[j]) == A[j] + rev(A[i])
A[i] - rev(A[i]) == A[j] - rev(A[j])
B[i] = A[i] - rev(A[i])

Then it becomes an easy question that,
how many pairs in B with B[i] == B[j]
*/

class Solution {
public:
	int countNicePairs(vector<int>& nums) {
		unordered_map<int, long> map;
		long ans = 0, m = 1e9+7;
		for (int i=0; i < nums.size(); i++) {
			int cur = revNum(nums[i]) - nums[i];
			if (map.count(cur)) ans = (ans + map[cur]) % m;
			map[cur]++;
		}
		return ans;
	}
	
	int revNum(int num) {
		int a = 0;
		while (num > 0) {
			a = a*10 + (num%10);
			num /= 10;
		}
		return a;
	}
};