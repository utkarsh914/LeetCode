// https://leetcode.com/problems/sell-diminishing-valued-colored-balls/

/*
You have an inventory of different colored balls, and there is a customer that wants orders balls of any color.

The customer weirdly values the colored balls. Each colored ball's value is the number of balls of that color you currently have in your inventory. For example, if you own 6 yellow balls, the customer would pay 6 for the first yellow ball. After the transaction, there are only 5 yellow balls left, so the next yellow ball is then valued at 5 (i.e., the value of the balls decreases as you sell more to the customer).

You are given an integer array, inventory, where inventory[i] represents the number of balls of the ith color that you initially own. You are also given an integer orders, which represents the total number of balls that the customer wants. You can sell the balls in any order.

Return the maximum total value that you can attain after selling orders colored balls. As the answer may be too large, return it modulo 109 + 7.

 

Example 1:


Input: inventory = [2,5], orders = 4
Output: 14
Explanation: Sell the 1st color 1 time (2) and the 2nd color 3 times (5 + 4 + 3).
The maximum total value is 2 + 5 + 4 + 3 = 14.
Example 2:

Input: inventory = [3,5], orders = 6
Output: 19
Explanation: Sell the 1st color 2 times (3 + 2) and the 2nd color 4 times (5 + 4 + 3 + 2).
The maximum total value is 3 + 2 + 5 + 4 + 3 + 2 = 19.
*/








/*
1. Greedily sell the most expensive ball.

2. There is some value k where all balls of value > k are sold,
and some, (maybe 0) of balls of value k are sold.

3. Use binary search to find this value k,
and use maths to find the total sum.
*/
class Solution {
public:
	int maxProfit(vector<int>& A, long orders) {
		long lo = 0;
		long hi = *max_element(A.begin(), A.end());
		long k = lo;
		
		/*
		find the biggest k which can fulfill all orders
		if we sell every ball at price >= k
		*/
		while (lo <= hi) {
			long mid = lo + (hi-lo)/2;
			if (isPossible(A, orders, mid))
				k = mid, lo = mid+1;
			else hi = mid-1;
		}
		
		/*
		calculate the maximum value that can be earned
		first we sell all balls at cost > k
		after this, if all orders aren't fulfilled,
		we can sell remaining orders at k price
		*/

		long sold = 0, mod = 1e9+7;

		for (int& x : A) {
			if (x <= k) continue;
			sold = (sold + getSum(x, k)) % mod;
			orders -= x-k;
		}

		sold = (sold + orders * k) % mod;
		return sold;
	}

	/*
	checks if we can fulfill all the orders for a given k
	*/
	bool isPossible(vector<int>& A, long orders, long k) {
		long done = 0;
		for (int& n : A)
			done += max(0L, n-k+1);
		return done >= orders;
	}

	/*
	returns the total amount if we sell
	all balls greater than k for the Xth ball
	e.g. k = 2, x = 7
	then rates at which balls can be sold are 3,4,5,6,7 -> (total 5 balls can be sold)
	so it returns 3+4+5+6+7
	*/
	long getSum(long x, long k) {
		long n = x - k;
		if (n < 1) return 0;
		return (n * (k+1 + x)) / 2;
	}
};
