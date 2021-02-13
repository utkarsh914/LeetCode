// https://leetcode.com/problems/capacity-to-ship-packages-within-d-days/

class Solution {
	bool canShip(vector<int>& weights, int D, int capacity) {
		int days = 1, curTotal = 0;
		for (int w:weights) {
			curTotal += w;
			if (curTotal > capacity)
				days++, curTotal = w;
		}
		return days <= D;
	}

public:
	int shipWithinDays(vector<int>& w, int D) {
		int start = *max_element(w.begin(), w.end());
		int end = accumulate(w.begin(), w.end(), 0);
		int capacity = start;

		// we have to minimize the capacity, so BS the minimum possible capacity
		while (start <= end) {
			int mid = start + (end-start)/2;
			if (canShip(w, D, mid))
				capacity = mid, end = mid-1;
			else
				start = mid+1;
		}

		return capacity;
	}
};