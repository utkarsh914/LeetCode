// https://leetcode.com/problems/gas-station/


// ********* brute force O(N^2) **********
class Solution {
public:
	int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
		int s = gas.size();
		for (int i=0; i < s; i++) {
			int tank = gas[i];
			int j = i;
			while (tank >= cost[j]) {
				tank += -cost[j] + gas[(j+1)%s];
				j = (j+1)%s;
				if (j == i) return i; // reached the start
			}
		}
		
		return -1;
	}
};


// ************ greedy O(N) ***********
class Solution {
public:
	int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
		int sumGas = 0, sumCost = 0, tank = 0, start = 0;

		for (int i=0; i < gas.size(); i++) {
			sumGas += gas[i];
			sumCost += cost[i];
			tank += gas[i] - cost[i];
			if (tank < 0) {
				tank = 0;
				start = i+1;
			}
		}
		
		return sumGas < sumCost ? -1 : start;
	}
};
/*
If car starts at A and can not reach B. Any station between A and B
can not reach B.(B is the first station that A can not reach.)
If the total number of gas is bigger than the total number of cost. There must be a solution.



The reason why I think this works:
1, if sum of gas is more than sum of cost, then there must be a solution. And the question guaranteed that the solution is unique(The first one I found is the right one).
2, The tank should never be negative, so restart whenever there is a negative number.



if you start from some index i,
and you know that sum of the gas is greater than the sum of the cost, it is impossible
that you get negative gas in some other point between that.
If you have negative gas at a later point,then there must be some point
after that but before your starting point that gives you enough fuel to continue.
If this is the case, why don't you just start at that point which you give you enough fuel?
So you must start at the first index where you got enough fuel to go to the next station.

*/