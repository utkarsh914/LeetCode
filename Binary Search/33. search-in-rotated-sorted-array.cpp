// https://leetcode.com/problems/search-in-rotated-sorted-array/

/*
There is an integer array nums sorted in ascending order (with distinct values).

Prior to being passed to your function, nums is rotated at an unknown pivot index k (0 <= k < nums.length) such that the resulting array is [nums[k], nums[k+1], ..., nums[n-1], nums[0], nums[1], ..., nums[k-1]] (0-indexed). For example, [0,1,2,4,5,6,7] might be rotated at pivot index 3 and become [4,5,6,7,0,1,2].

Given the array nums after the rotation and an integer target, return the index of target if it is in nums, or -1 if it is not in nums.

You must write an algorithm with O(log n) runtime complexity.

 

Example 1:

Input: nums = [4,5,6,7,0,1,2], target = 0
Output: 4
Example 2:

Input: nums = [4,5,6,7,0,1,2], target = 3
Output: -1
Example 3:

Input: nums = [1], target = 0
Output: -1
 

Constraints:

1 <= nums.length <= 5000
-104 <= nums[i] <= 104
All values of nums are unique.
nums is guaranteed to be rotated at some pivot.
-104 <= target <= 104
*/










int search(vector<int>& A, int T) {
	
	int lo = 0, hi = A.size()-1;
	
	while (lo <= hi) {
		int m = lo + (hi - lo) / 2;
		if (A[m] == T) return m;
		// if left part
		if (A[lo] <= A[m]) {
			if (T >= A[lo] and T <= A[m]) hi = m-1;
			else lo = m+1;
		}
		// in right part
		else {
			if (T >= A[m] and T <= A[hi]) lo = m+1;
			else hi = m-1;
		}
	}
	
	return -1;
}










/*
ref: https://leetcode.com/problems/search-in-rotated-sorted-array/discuss/154836/The-INF-and-INF-method-but-with-a-better-explanation-for-dummies-like-me
*/
class Solution {
public:
	int search(vector<int>& n, int target) {
		int l = 0, r = n.size()-1;
		while(l <= r) {

			int mid = (r - l)/2 + l;
			double comparator = n[mid];
			
			// need to handle: 1,3,1,1,1 (to handle dups)
			while (n[l] == n[mid] && l != mid) {
				l++;
			}
			while (n[mid] == n[r] && r != mid) {
				r--;
			}

			// Checking if both target and n[mid] are on same side.
			if((target < n[l]) && (n[mid] < n[l]) or (target >= n[l]) && (n[mid] >= n[l])) {
				comparator = n[mid];
			}
			else {
				// Trying to figure out where n[mid] is and making comparator as -INF or INF
				if(target <n[l])
					comparator = -INFINITY;
				else
					comparator = INFINITY;
			}

			if(target == comparator)
				return mid;
			if(target > comparator)
				l = mid+1;
			else
				r = mid-1;

		}
		return -1;
	}
};










class Solution {
public:
	int search(vector<int>& nums, int target) {
		int start = 0;
		int end = nums.size() - 1;
		
		while (start <= end) {
			int mid = start + (end - start) / 2;
			
			if (nums[mid] == target) return mid;
			
			// need to handle: 1,3,1,1,1 (to handle dups)
			while (nums[start] == nums[mid] && start != mid) {
				start ++;
			}
			while (nums[mid] == nums[end] && mid != end) {
				end --;
			}

			// the following is the same as problem I (without dups)
			if (nums[start] <= nums[mid]) {
				if (nums[start] <= target && target < nums[mid]) {
					end = mid - 1;
				} else {
					start = mid + 1;
				}
			} else {
				if (nums[mid] < target && target <= nums[end]) {
					start = mid + 1;
				} else {
					end = mid - 1;
				}
			}
		}
		
		return -1;
	}

};










class Solution {
	int getPivot(vector<int>& nums, int start, int end) {
		while (start <= end) {
			int mid = start + (end-start)/2;
			if (nums[mid] > nums[mid+1])
				return max(mid, getPivot(nums, mid+1, end));
			else
				return max(getPivot(nums, start, mid-1), getPivot(nums, mid+1, end));
		}
		return -1;
	}

public:
	int search(vector<int>& nums, int target) {
		int pivot = getPivot(nums, 0, nums.size()-2);
		int shift = pivot+1;
		int s = nums.size();
		int start = 0, end = s-1;
		while (start <= end) {
			int mid = start + (end-start)/2;
			if (nums[(mid+shift)%s] == target)
				return (mid+shift)%s;
			if (nums[(mid+shift)%s] > target)
				end = mid-1;
			else
				start = mid+1;
		}
		return -1;
	}
};











// find the pivot element, then binary search on the left and right parts
class Solution {
	int getPivot(vector<int>& nums, int start, int end) {
		while (start <= end) {
			int mid = start + (end-start)/2;
			if (nums[mid] > nums[mid+1])
				return max(mid, getPivot(nums, mid+1, end));
			else
				return max(getPivot(nums, start, mid-1), getPivot(nums, mid+1, end));
		}
		return -1;
	}

	int binarySearch(vector<int>& nums, int target, int start, int end) {
		while (start <= end) {
			int mid = start + (end-start)/2;
			if (nums[mid] == target)
				return mid;
			if (nums[mid] > target)
				end = mid-1;
			else
				start = mid+1;
		}
		return -1;
	}

public:
	int search(vector<int>& nums, int target) {
		int pivot = getPivot(nums, 0, nums.size()-2);
		int leftPart = binarySearch(nums, target, 0, pivot);
		return leftPart!=-1 ? leftPart : binarySearch(nums, target, pivot+1, nums.size()-1);
	}
};