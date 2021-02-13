// https://leetcode.com/problems/search-in-rotated-sorted-array-ii/

class Solution {
public:
	bool search(vector<int>& n, int target) {
		int l = 0, r = n.size()-1;
		while(l <= r) {

			int mid = (r - l)/2 + l;
			double comparator = n[mid];
			
			// need to handle: 1,3,1,1,1
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
				return true;
			if(target > comparator)
				l = mid+1;
			else
				r = mid-1;

		}
		return false;
	}
};








bool search(vector<int>& nums, int target) {
	int start = 0;
	int end = nums.size() - 1;
	
	while (start <= end) {
		int mid = start + (end - start) / 2;
		
		if (nums[mid] == target) return true;
		
		// need to handle: 1,3,1,1,1
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
	
	return false;
}













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
	bool search(vector<int>& nums, int target) {
		int pivot = getPivot(nums, 0, nums.size()-2);
		// bool leftPart = binarySearch(nums, target, 0, pivot) != -1;
		// bool rightPart = binarySearch(nums, target, pivot+1, nums.size()-1) != -1;
		return binarySearch(nums, target, 0, pivot) != -1
			or binarySearch(nums, target, pivot+1, nums.size()-1) != -1;
	}
};