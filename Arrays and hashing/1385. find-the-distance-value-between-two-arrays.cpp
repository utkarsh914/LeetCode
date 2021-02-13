/*
https://leetcode.com/problems/find-the-distance-value-between-two-arrays/
*/

class Solution {
public:
	// using binary search, return closest number to target
	int closest(vector<int>& a, int tar) {
		int i=0, j=a.size()-1, diff=INT_MAX, ans=a[0];
		while (i <= j) {
			int mid = (i+j)/2;
			// update difference and value with current mid value
			if (abs(a[mid]-tar) < diff)
				diff=abs(a[mid]-tar), ans=a[mid];
			// update low, high ptrs
			if (a[mid] < tar)	i = mid+1;
			else j = mid-1;
		}
		return ans;
	}
	
	int findTheDistanceValue(vector<int>& a1, vector<int>& a2, int d) {
		sort(a2.begin(), a2.end());
		int c=0;
		for (int n:a1) {
			if (abs(n-closest(a2,n)) > d) c++;
		}
		return c;
	}
};