// https://leetcode.com/problems/find-first-and-last-position-of-element-in-sorted-array/

class Solution {
public:

	int binarySearch(vector<int>& nums, int target, int lo, int hi) {
		while (lo <= hi) {
			int mid = (lo+hi)/2;
			if (nums[mid] == target)
				return mid;
			if (target < nums[mid])
				hi=mid-1;
			else if (target > nums[mid])
				lo=mid+1;
		}
		return -1;
	}

	vector<int> searchRange(vector<int>& nums, int target) {
		// find first occurence
		int found = binarySearch(nums, target, 0, nums.size()-1);
		// cout << found << endl;
		if (found == -1) return {-1,-1};

		set<int> st;
		st.insert(found);
		// find leftmost occurence
		int start=0, end=found-1;
		while (1) {
			int i = binarySearch(nums, target, start, end);
	  	// cout<<"start: "<<start<<" end: "<<end<<" i: "<<i<<endl;
			if (i==-1) break;
			st.insert(i);
			end = i-1;
		}
		// find rightmost occurence
		start=found+1, end=nums.size()-1;
		while (1) {
			int i = binarySearch(nums, target, start, end);
	  	// cout<<"start: "<<start<<" end: "<<end<<" i: "<<i<<endl;
			if (i==-1) break;
			st.insert(i);
			start = i+1;
		}
		return {*st.begin(), *st.rbegin()};
	}

};

/*
********************* MORE EFFICIENT ***************

public class Solution {
	public int[] searchRange(int[] A, int target) {
		int start = Solution.firstGreaterEqual(A, target);
		if (start == A.length || A[start] != target) {
			return new int[]{-1, -1};
		}
		return new int[]{start, Solution.firstGreaterEqual(A, target + 1) - 1};
	}

	//find the first number that is greater than or equal to target.
	//could return A.length if target is greater than A[A.length-1].
	//actually this is the same as lower_bound in C++ STL.
	private static int firstGreaterEqual(int[] A, int target) {
		int low = 0, high = A.length;
		while (low < high) {
			int mid = low + ((high - low) >> 1);
			//low <= mid < high
			if (A[mid] < target) {
				low = mid + 1;
			} else {
				//should not be mid-1 when A[mid]==target.
				//could be mid even if A[mid]>target because mid<high.
				high = mid;
			}
		}
		return low;
	}
}

*/