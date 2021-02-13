// https://leetcode.com/problems/sliding-window-median/

class Solution {
public:
	vector<double> medianSlidingWindow(vector<int>& nums, int k) {
		multiset<int> window(nums.begin(), nums.begin()+k); // decreasing order
		vector<double> medians;
		auto mid = next(window.begin(), k/2);

		// curr window is i to j inclusive
		for (int i=1, j=i+k-1; j <= nums.size(); i++, j++) {
			// push previous window median;
			double median = ((double)*mid + *(prev(mid, 1 - k%2))) / 2; // fancy way of taking values from middle 2 vals, or 1 val (depending if k is even or odd)

			medians.push_back(median);
			if (j == nums.size()) break;
			
			// insert curr element
			window.insert(nums[j]);
			if (nums[j] < *mid) mid--;
			// erase nums[i-1]
			if (nums[i-1] <= *mid) mid++;
			window.erase( window.lower_bound(nums[i-1]) );
		}

		return medians;
	}
};

/*
 ********* mid iterator will never be erased **********

iterator's value should be equal to the nums[i-k] to be removed.
But it never happens because before erasing nums[i-k], iterator moves forward.
if (nums[i-k] <= *mid)
mid++;
And when erasing the nums[i-k] value, we find a lower_bound of nums[i-k],
and it is guaranteed that the result of lower bound is the first iterator of its value
window.erase(window.lower_bound(nums[i-k]));
so if we erase the first iterator of its value, the mid will never be removed
*/