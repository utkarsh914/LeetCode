// https://leetcode.com/problems/trapping-rain-water/

class Solution {
public:
	int trap(vector<int>& height) {
		int size = height.size();
		if (!size) return 0;

		int maxOnLeft[size], maxOnRight[size];
		int max_ = INT_MIN;
		for (int i=size-1; i>=0; i--) {
			max_ = max(max_, height[i]);
			maxOnRight[i] = max_;
		}
		max_ = INT_MIN;
		for (int i=0; i<size; i++) {
			max_ = max(max_, height[i]);
			maxOnLeft[i] = max_;
		}

		int water = 0;
		for (int i=0; i<size; i++) {
			water += min(maxOnLeft[i], maxOnRight[i]) - height[i];
		}
		return water;
	}
};




// ********** two pointer, O(1) space *********
class Solution {
public:
	int trap(vector<int>& h) {
		int size = h.size();
		if (size < 3) return 0;

		int maxOnLeft = 0, maxOnRight = 0;
		int left = 0, right = size-1;
		int water = 0;

		while (left <= right) {
			maxOnLeft = max(maxOnLeft, h[left]);
			maxOnRight = max(maxOnRight, h[right]);
			if (maxOnLeft <= maxOnRight) {
				water += maxOnLeft-h[left];
				left++;
			}
			else {
				water += maxOnRight-h[right];
				right--;
			}
		}

		return water;
	}
};

