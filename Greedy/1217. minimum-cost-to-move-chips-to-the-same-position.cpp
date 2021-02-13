// https://leetcode.com/problems/minimum-cost-to-move-chips-to-the-same-position/

/*
We have n chips, where the position of the ith chip is position[i].

We need to move all the chips to the same position.
In one step, we can change the position of the ith chip from position[i] to:

position[i] + 2 or position[i] - 2 with cost = 0.
position[i] + 1 or position[i] - 1 with cost = 1.
Return the minimum cost needed to move all the chips to the same position.

Example 1:
Input: position = [1,2,3]
Output: 1
Explanation: First step: Move the chip at position 3 to position 1 with cost = 0.
Second step: Move the chip at position 2 to position 1 with cost = 1.
Total cost is 1.

Example 2:
Input: position = [2,2,2,3,3]
Output: 2
Explanation: We can move the two chips at position  3 to position 2. Each move has cost = 1. The total cost = 2.

Example 3:
Input: position = [1,1000000000]
Output: 1
*/


/*
all chips at even positions can be concentrated at one even location at zero cost.
similarly, all chips at odd positions can be concentrated at one odd location at zero cost.

now, as we want to minimize the cost, we can pick those concentrated locations for odd and even
to be adjacent to each other (having 1 diff in their positions).

now, if odd concentration size is less, shift it to even stack,
else shift even stack to odd stack.
hence, cost incurred = min(odd, even).
*/
class Solution {
public:
	int minCostToMoveChips(vector<int>& position) {
		int odd = 0, even = 0;
		for (int p : position) {
			if (p % 2) odd++;
			else even++;
		}
		return min(odd,even);
	}
};