// https://leetcode.com/problems/find-the-smallest-divisor-given-a-threshold/

class Solution {
public:
	int smallestDivisor(vector<int>& nums, int threshold) {
		int start = 1, end = *max_element(nums.begin(), nums.end());
		while (start < end) {
			int mid = start + (end-start)/2;
			if (possible(nums, threshold, mid))
				end = mid;
			else start = mid+1;
		}
		return start;
	}
	
	bool possible(vector<int>& nums, int thresholdSum, int divisor) {
		int sum = 0;
		for (int n : nums) sum += 1 + ((n-1) / divisor);
		return sum <= thresholdSum;
	}
};