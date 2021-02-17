// https://leetcode.com/problems/minimum-number-of-days-to-make-m-bouquets/

// similar to: 1011. capacity-to-ship-packages-within-d-days

/*
Given an integer array bloomDay, an integer m and an integer k.

We need to make m bouquets. To make a bouquet, you need to use k adjacent flowers from the garden.

The garden consists of n flowers, the ith flower will bloom in the bloomDay[i]
and then can be used in exactly one bouquet.

Return the minimum number of days you need to wait to be able to make m bouquets from the garden.
If it is impossible to make m bouquets return -1.


Example 1:

Input: bloomDay = [1,10,3,10,2], m = 3, k = 1
Output: 3
Explanation: Let's see what happened in the first three days. x means flower bloomed and _ means flower didn't bloom in the garden.
We need 3 bouquets each should contain 1 flower.
After day 1: [x, _, _, _, _]   // we can only make one bouquet.
After day 2: [x, _, _, _, x]   // we can only make two bouquets.
After day 3: [x, _, x, _, x]   // we can make 3 bouquets. The answer is 3.
Example 2:

Input: bloomDay = [1,10,3,10,2], m = 3, k = 2
Output: -1
Explanation: We need 3 bouquets each has 2 flowers, that means we need 6 flowers. We only have 5 flowers so it is impossible to get the needed bouquets and we return -1.
Example 3:

Input: bloomDay = [7,7,7,7,12,7,7], m = 2, k = 3
Output: 12
Explanation: We need 2 bouquets each should have 3 flowers.
Here's the garden after the 7 and 12 days:
After day 7: [x, x, x, x, _, x, x]
We can make one bouquet of the first three flowers that bloomed. We cannot make another bouquet from the last three flowers that bloomed because they are not adjacent.
After day 12: [x, x, x, x, x, x, x]
It is obvious that we can make two bouquets in different ways.
*/

class Solution {
public:
	int minDays(vector<int>& bloomDay, int m, int k) {
		if (m * k > bloomDay.size()) return -1;
		
		auto p = minmax_element(bloomDay.begin(), bloomDay.end());
		int start = *p.first, end = *p.second;
		
		while (start < end) {
			int mid = start + (end-start)/2;
			if (possible(bloomDay, m, k, mid))
				end = mid;
			else start = mid+1;
		}
		return start;
	}
	// tells if it is possible to get m bouquets of size k in daysToWait no. of days
	// if all the continuous groups of size k are >= m, then it is possible
	// note that, flowers included in a group should be adjacent, otherwise we make another group
	bool possible(vector<int>& bloomDay, int m, int k, int daysTowait) {
		int bouquetsMade = 0, curSize = 0;
		for (int d : bloomDay) {
			if (d <= daysTowait) curSize++; // if it can be take, ad it to group size
			else curSize = 0; // if can't take this, reset the group size
			if (curSize == k) // if got required group size, make a bouquet, and start new group size
				bouquetsMade++, curSize = 0;
		}
		return bouquetsMade >= m;
	}
};