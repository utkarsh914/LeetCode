// https://leetcode.com/problems/minimum-limit-of-balls-in-a-bag/

// concept similar to: 1011. capacity-to-ship-packages-within-d-days



/*
You are given an integer array nums where the ith bag contains nums[i] balls. You are also given an integer maxOperations.

You can perform the following operation at most maxOperations times:

Take any bag of balls and divide it into two new bags with a positive number of balls.
For example, a bag of 5 balls can become two new bags of 1 and 4 balls, or two new bags of 2 and 3 balls.
Your penalty is the maximum number of balls in a bag. You want to minimize your penalty after the operations.

Return the minimum possible penalty after performing the operations.

 

Example 1:

Input: nums = [9], maxOperations = 2
Output: 3
Explanation: 
- Divide the bag with 9 balls into two bags of sizes 6 and 3. [9] -> [6,3].
- Divide the bag with 6 balls into two bags of sizes 3 and 3. [6,3] -> [3,3,3].
The bag with the most number of balls has 3 balls, so your penalty is 3 and you should return 3.
Example 2:

Input: nums = [2,4,8,2], maxOperations = 4
Output: 2
Explanation:
- Divide the bag with 8 balls into two bags of sizes 4 and 4. [2,4,8,2] -> [2,4,4,4,2].
- Divide the bag with 4 balls into two bags of sizes 2 and 2. [2,4,4,4,2] -> [2,2,2,4,4,2].
- Divide the bag with 4 balls into two bags of sizes 2 and 2. [2,2,2,4,4,2] -> [2,2,2,2,2,4,2].
- Divide the bag with 4 balls into two bags of sizes 2 and 2. [2,2,2,2,2,4,2] -> [2,2,2,2,2,2,2,2].
The bag with the most number of balls has 2 balls, so your penalty is 2 an you should return 2.
*/






/*
Minimum possible penlty can be 1, and max possible penalty can be eq to max element
This is the possible range of our answer.
If we have a helper fn which tells if it is possible to get a certain penalty
considering the max number of operations allowed,
we can perform binary search on above range to minimize the possible penalty.

***** helper functon *****
it calculates the total number of ops required to make a number less than or eq to the current assumed penalty.
If the total ops required is less than or eq to the given limit of maxOps, it is possible.
*/
class Solution {
public:
	int minimumSize(vector<int>& nums, int maxOperations) {
		int start = 1, end = *max_element(nums.begin(), nums.end());
		int minPenalty = end;
		// do binary search on possible range
		while (start <= end) {
			int penalty = start + (end-start)/2;
			if (isPossible(nums, maxOperations, penalty))
				minPenalty = penalty, end = penalty-1;
			else
				start = penalty+1;
		}

		return minPenalty;
	}

	bool isPossible(vector<int>& nums, int maxOperations, int penalty) {
		int requiredOps = 0;
		for (int n : nums) {
			// ops required to bring n less than or eq to curr assumed penalty
			int x = n / penalty;
			// if n is divisible by penalty, need to subtract 1
			if (n % penalty == 0) x--;
			requiredOps += x;
		}
		// getting current penalty possible only if required ops is <= maxOps
		return requiredOps <= maxOperations;
	}
};