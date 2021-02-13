// https://leetcode.com/problems/longest-mountain-in-array/

class Solution {
public:
	int longestMountain(vector<int>& arr) {
		int maxL=0, inc=0, dec=0;
		for (int i=1; i<arr.size(); i++) {
			if (arr[i] > arr[i-1]) { // increasing
				if (dec == 0) inc++;
				else dec=0, inc=1;
			}
			else if (arr[i] < arr[i-1]) { // decreasing
				if (inc == 0) dec=0;
				else dec++;
			}
			else { // equal
				inc = dec = 0;
			}
			if (inc>0 && dec>0)
				maxL = max(maxL, inc+dec+1);
		}
		return maxL;
	}
};