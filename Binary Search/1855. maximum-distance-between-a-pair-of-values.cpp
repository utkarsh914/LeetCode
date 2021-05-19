// https://leetcode.com/problems/maximum-distance-between-a-pair-of-values/

/*
You are given two non-increasing 0-indexed integer arrays nums1​​​​​​ and nums2​​​​​​.
A pair of indices (i, j), where 0 <= i < nums1.length and 0 <= j < nums2.length,
is valid if both i <= j and nums1[i] <= nums2[j]. The distance of the pair is j - i​​​​.
Return the maximum distance of any valid pair (i, j). If there are no valid pairs, return 0.
An array arr is non-increasing if arr[i-1] >= arr[i] for every 1 <= i < arr.length. 

Example 1:

Input: nums1 = [55,30,5,4,2], nums2 = [100,20,10,10,5]
Output: 2
Explanation: The valid pairs are (0,0), (2,2), (2,3), (2,4), (3,3), (3,4), and (4,4).
The maximum distance is 2 with pair (2,4).
*/







/*
Since both arrays are sorted in a non-increasing way
this means that for each value in the first array.
We can find the farthest value smaller than it using binary search.
*/
class Solution {
public:
	int maxDistance(vector<int>& A, vector<int>& B) {
		int ans = 0;
		for (int i = 0; i < min(A.size(), B.size()); i++) {
			if (A[i] > B[i]) continue;
			int j = getMaxInd(B, i, B.size()-1, A[i]);
			ans = max(ans, j - i);
		}
		return ans;
	}
	
	int getMaxInd(vector<int>& A, int start, int end, int target) {
		int ans = start;
		while (start <= end) {
			int mid = start + (end-start)/2;
			if (A[mid] >= target)
				ans = mid, start = mid + 1;
			else
				end = mid-1;
		}
		return ans;
	}
};





/*
since the first array is non-increasing
the farthest j such that nums2[j] ≥ nums1[i] is at least as far as
the farthest j such that nums2[j] ≥ nums1[i-1]
*/
class Solution {
public:
	int maxDistance(vector<int>& A, vector<int>& B) {
		int ans = 0;
		for (int i = 0, j = 0; i < min(A.size(), B.size()); i++) {
			if (j < i) j = i;
			while (j < B.size() and B[j] >= A[i]) {
				ans = max(ans, j - i);
				j++;
			}
		}
		return ans;
	}
};

int maxDistance(vector<int>& A, vector<int>& B) {
	int ans = 0;
	for (int i = 0, j = 0; i < min(A.size(), B.size()); i++) {
		for (j = max(i, j); j < B.size() and B[j] >= A[i]; j++)
			ans = max(ans, j - i);
	}
	return ans;
}