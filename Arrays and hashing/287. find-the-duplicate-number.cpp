// https://leetcode.com/problems/find-the-duplicate-number/

class Solution {
public:
	int findDuplicate(vector<int>& nums) {
		int slow = nums[0];
		int fast = nums[0];

		do {
			slow = nums[slow];
			fast = nums[nums[fast]];
		} while (slow != fast);

		int start = nums[0];
		while (start != slow) {
			start = nums[start];
			slow = nums[slow];
		}

		return start;
	}
};


/* ********** binary search ************
At first the search space is numbers between 1 to n. Each time I select a number mid (which is the one in the middle)
and count all the numbers equal to or less than mid. Then if the count is more than mid,
the search space will be [1 mid] otherwise [mid+1 n]. I do this until search space is only one number.

Let's say n=10 and I select mid=5. Then I count all the numbers in the array which are less than equal mid.
If the there are more than 5 numbers that are less than 5, then by Pigeonhole Principle
(https://en.wikipedia.org/wiki/Pigeonhole_principle) one of them has occurred more than once.
So I shrink the search space from [1 10] to [1 5].
Otherwise the duplicate number is in the second half so for the next step the search space would be [6 10].
*/

class Solution {
public:
	int findDuplicate(vector<int>& nums) {
		
		int start = 1, end = nums.size()-1;
		int duplicate = 1;

		while (start <= end) {
			int mid = start + (end-start)/2;
			// count elements <= mid in the array
			int count = 0;
			for (int n:nums) count += n<=mid;

			if (count > mid) // mid is potential ans, or ans is lower than mid
				duplicate = mid, end = mid-1;
			else
				start = mid+1; // else answer is higher than mid
		}

		return start;
	}
};