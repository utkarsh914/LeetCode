// https://leetcode.com/problems/find-in-mountain-array/

/**
 * // This is the MountainArray's API interface.
 * // You should not implement it, or speculate about its implementation
 * class MountainArray {
 *   public:
 *	 int get(int index);
 *	 int length();
 * };
 */

class Solution {
	int findPeak(MountainArray &arr) {
		int start=0, end=arr.length()-2, peak=1;
		while (start <= end) {
			int mid = start + (end-start)/2;
			if (arr.get(mid) > arr.get(mid+1))
				peak=mid, end=mid-1;
			else
				start=mid+1;
		}
		return peak;
	}
	
public:
	int findInMountainArray(int target, MountainArray &arr) {
		int peak = findPeak(arr);
		// search on left of peak (in increasing sequence)
		int start=0, end=peak;
		while (start <= end) {
			int mid = start + (end-start)/2;
			int midVal = arr.get(mid);
			if (midVal == target)
				return mid;
			if (midVal > target)
				end = mid-1;
			else
				start = mid+1;
		}
		// search on right of peak (in decreasing sequence)
		start=peak+1, end=arr.length()-1;
		while (start <= end) {
			int mid = start + (end-start)/2;
			int midVal = arr.get(mid);
			if (midVal == target)
				return mid;
			if (midVal < target)
				end = mid-1;
			else
				start = mid+1;
		}
		// doesn't exist
		return -1;
	}
};