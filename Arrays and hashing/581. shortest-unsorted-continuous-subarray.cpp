// https://leetcode.com/problems/shortest-unsorted-continuous-subarray/

class Solution {
public:
	int findUnsortedSubarray(vector<int>& nums) {
		vector<int> sorted(nums.begin(), nums.end());
		sort(sorted.begin(), sorted.end());
		vector<int> indices;
		for (int i=0; i < nums.size(); i++) {
			if (nums[i] != sorted[i])
				indices.push_back(i);
		}
		if (indices.size() == 0) return 0;
		if (indices.size() == 1) return nums.size()-indices[0];
		return indices.back() - indices.front() + 1;
	}
};




class Solution {
public:
	int findUnsortedSubarray(vector<int>& nums) {
		vector<int> sorted(nums.begin(), nums.end());
		sort(sorted.begin(), sorted.end());
		int start = -1, end = -1;
		for (int i=0; i < nums.size(); i++) {
			istart (nums[i] == sorted[i])
				continue;
			if (start == -1) start = i;
			else end = i+1;
		}
		if (start == -1) return 0;
		return end - start;
	}
};




/*
Algorithm

The idea behind this approach is also based on selective sorting. We need to determine the correct position of the minimum and the maximum element in the unsorted subarray to determine the boundaries of the required unsorted subarray.

To do so, in this implementation, we make use of a stackstack. We traverse over the numsnums array starting from the beginning. As we go on facing elements in ascending order(a rising slope), we keep on pushing the elements' indices over the stackstack. This is done because such elements are in the correct sorted order(as it seems till now). As soon as we encounter a falling slope, i.e. an element nums[j]nums[j] which is smaller than the element on the top of the stackstack, we know that nums[j]nums[j] isn't at its correct position.

In order to determine the correct position of nums[j]nums[j], we keep on popping the elemnents from the top of the stackstack until we reach the stage where the element(corresponding to the index) on the top of the stackstack is lesser than nums[j]nums[j]. Let's say the popping stops when the index on stackstack's top is kk. Now, nums[j]nums[j] has found its correct position. It needs to lie at an index k + 1k+1.

We follow the same process while traversing over the whole array, and determine the value of minimum such kk. This marks the left boundary of the unsorted subarray.

Similarly, to find the right boundary of the unsorted subarray, we traverse over the numsnums array backwards. This time we keep on pushing the elements if we see a falling slope. As soon as we find a rising slope, we trace forwards now and determine the larger element's correct position. We do so for the complete array and thus, determine the right boundary.

We can look at the figure below for reference. We can observe that the slopes directly indicate the relative ordering. We can also observe that the point bb needs to lie just after index 0 marking the left boundary and the point aa needs to lie just before index 7 marking the right boundary of the unsorted subarray.
*/
class Solution {
public:
	int findUnsortedSubarray(vector<int>& a) {
		if (a.size() < 2) return 0;
		stack<int> s; // contains indices
		int left = a.size(), right = 0;

		for (int i = 0; i < a.size(); i++) {
			while (!s.empty() && a[s.top()] > a[i])
				left = min(left, s.top()), s.pop();
			s.push(i);
		}

		s.clear();
		for (int i = a.size()-1; i >= 0; i--) {
			while (!s.empty() && a[s.top()] < a[i])
				right = max(right, s.top()), s.pop();
			s.push(i);
		}

		return (right-left > 0) ? right-left+1 : 0;
	}
};





/*
Algorithm

The idea behind this method is that the correct position of the minimum element in the unsorted subarray helps to determine the required left boundary. Similarly, the correct position of the maximum element in the unsorted subarray helps to determine the required right boundary.

Thus, firstly we need to determine when the correctly sorted array goes wrong. We keep a track of this by observing rising slope starting from the beginning of the array. Whenever the slope falls, we know that the unsorted array has surely started. Thus, now we determine the minimum element found till the end of the array numsnums, given by minmin.

Similarly, we scan the array numsnums in the reverse order and when the slope becomes rising instead of falling, we start looking for the maximum element till we reach the beginning of the array, given by maxmax.

Then, we traverse over numsnums and determine the correct position of minmin and maxmax by comparing these elements with the other array elements. e.g. To determine the correct position of minmin, we know the initial portion of numsnums is already sorted. Thus, we need to find the first element which is just larger than minmin. Similarly, for maxmax's position, we need to find the first element which is just smaller than maxmax searching in numsnums backwards.
*/
class Solution {
public:
	int findUnsortedSubarray(vector<int>& a) {
		
		int mn = INT_MAX, mx = INT_MIN;
		bool flag = false;

		for (int i = 1; i < a.size(); i++) {
			if (a[i] < a[i-1]) flag = true;
			if (flag == true) mn = min(mn, a[i]);
		}

		flag = false;
		for (int i = a.size()-2; i >= 0; i--) {
			if (a[i] > a[i+1]) flag = true;
			if (flag == true) mx = max(mx, a[i]);
		}

		int left = 0, right = a.size()-1;

		for ( ; left < a.size(); left++) {
			if (a[left] > mn) break;
		}
		for ( ; right >= 0; right--) {
			if (a[right] < mx) break;
		}

		return (right-left > 0) ? right-left+1 : 0;
	}
};