// https://leetcode.com/problems/find-minimum-in-rotated-sorted-array-ii/

/*
There are 4 kinds of relationship among num[lo], nums[mi], nums[hi]

nums[lo] <= nums[mi] <= nums[hi], min is nums[lo]
nums[lo] > nums[mi] <= nums[hi], (lo, mi] is not sorted, min is inside
nums[lo] <= nums[mi] > nums[hi], (mi, hi] is not sorted, min is inside
nums[lo] > nums[mi] > nums[hi], impossible

*/
class Solution {
public:
		int findMin(vector<int>& nums) {
		
		int lo = 0, hi = nums.size() - 1;

		while (lo < hi) {
			int mi = lo + (hi - lo) / 2;

			if (nums[mi] > nums[hi]) { 
				lo = mi + 1;
			}
			else if (nums[mi] < nums[lo]) { 
				hi = mi;
				lo++;
			}
			else { // nums[lo] <= nums[mi] <= nums[hi] 
				hi--;
			}
		}
		
		return nums[lo];
	}
};




int findMin(vector<int>& a) {
	int lo = 0, hi = a.size()-1;
	while (lo <= hi) {
		int m = lo + (hi-lo) / 2;
		if (a[m] >= a[lo] && a[m] >= a[hi]) {
			lo = m + 1;
		} else if (a[m] <= a[lo] && a[m] <= a[hi]) {
			hi = m;
		} else {
			hi = m-1;
			// or hi = lo;
		}
	}
	return a[hi];
}