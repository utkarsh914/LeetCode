// https://leetcode.com/problems/find-k-th-smallest-pair-distance/

class Solution {
public:
	int smallestDistancePair(vector<int>& nums, int k) {
		sort(nums.begin(), nums.end());
		int start = 0, end = nums.back() - nums.front();
		while (start < end) {
			int mid = start + (end-start)/2;
			if (feasible(nums, mid, k))
				end = mid;
			else start = mid+1;
		}
		return start;
	}
	
	bool feasible(vector<int>& n, int diff, int requiredCount) {
		int count = 0, left = 0, right = 0;
		// use 2 ptrs to count no. of pairs with diff<=diff
		// take advantage of sorted sequence
		while (right < n.size() or left < n.size()) {
			while (right < n.size() && n[right]-n[left] <= diff)
				right++;
			count += right - left - 1;
			left++;
		}
		return count >= requiredCount;
		// for (int i=0; i < n.size()-1; i++) {
		// 	count += lower_bound(n.begin()+i, n.end(), n[i]+diff+1) - (n.begin()+i) -1;
		// }
	}
};