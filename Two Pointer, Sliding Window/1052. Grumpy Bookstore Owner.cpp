// https://leetcode.com/problems/grumpy-bookstore-owner/

/*
Today, the bookstore owner has a store open for customers.length minutes.  Every minute, some number of customers (customers[i]) enter the store, and all those customers leave after the end of that minute.

On some minutes, the bookstore owner is grumpy.  If the bookstore owner is grumpy on the i-th minute, grumpy[i] = 1, otherwise grumpy[i] = 0.  When the bookstore owner is grumpy, the customers of that minute are not satisfied, otherwise they are satisfied.

The bookstore owner knows a secret technique to keep themselves not grumpy for minutes minutes straight, but can only use it once.

Return the maximum number of customers that can be satisfied throughout the day.

 

Example 1:

Input: customers = [1,0,1,2,1,1,7,5], grumpy = [0,1,0,1,0,1,0,1], minutes = 3
Output: 16
Explanation: The bookstore owner keeps themselves not grumpy for the last 3 minutes. 
The maximum number of customers that can be satisfied = 1 + 1 + 1 + 1 + 7 + 5 = 16.
*/








/*
have a window of k length
for each window, keep track of the gain we can make
i.e. sum up all those customers insdide the window
where owner was grumpy. Bcz if we keep him non grumpy,
it would be a gain over the normal satisfied ones.

track the max gain we can make
*/
class Solution {
public:
	int maxSatisfied(vector<int>& customers, vector<int>& grumpy, int k) {
		int satisfied = 0, curGain = 0, maxGain = 0;

		// first window of k length
		for (int i = 0; i < k; i++) {
			if (grumpy[i] == 0) satisfied += customers[i];
			curGain += grumpy[i] * customers[i];
		}

		maxGain = curGain;

		for (int i = k; i < customers.size(); i++) {
			if (grumpy[i] == 0) satisfied += customers[i];
			curGain += grumpy[i] * customers[i]; // include cur element
			curGain -= grumpy[i-k] * customers[i-k]; // remove from window
			maxGain = max(maxGain, curGain);
		}

		return satisfied + maxGain;
	}
};