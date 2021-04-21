// https://leetcode.com/problems/bulb-switcher/

/*
There are n bulbs that are initially off.
You first turn on all the bulbs, then you turn off every second bulb.

On the third round, you toggle every third bulb
(turning on if it's off or turning off if it's on).
For the ith round, you toggle every i bulb.
For the nth round, you only toggle the last bulb.

Return the number of bulbs that are on after n rounds.
*/

/*
find number of perfect squares <= n

bcz only perfect squares will have odd number of factors
rest all nums will have even no. of factors
so, even no. of factors means, at the end, their initial state(OFF) will be restored
*/
class Solution {
public:
	int bulbSwitch(int n) {
		// int c = 0;
		// for (int i=1; i*i <= n; i++, c++);
		// return c;
		return int(sqrt(n));
	}
};