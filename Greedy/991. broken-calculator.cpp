// https://leetcode.com/problems/broken-calculator/

/*
On a broken calculator that has a number showing on its display, we can perform two operations:

Double: Multiply the number on the display by 2, or;
Decrement: Subtract 1 from the number on the display.
Initially, the calculator is displaying the number X.

Return the minimum number of operations needed to display the number Y.

 

Example 1:

Input: X = 2, Y = 3
Output: 2
Explanation: Use double operation and then decrement operation {2 -> 4 -> 3}.
Example 2:

Input: X = 5, Y = 8
Output: 2
Explanation: Use decrement and then double {5 -> 4 -> 8}.
Example 3:

Input: X = 3, Y = 10
Output: 3
Explanation:  Use double, decrement and double {3 -> 6 -> 5 -> 10}.
Example 4:

Input: X = 1024, Y = 1
Output: 1023
Explanation: Use decrement operations 1023 times.
 

Note:

1 <= X <= 10^9
1 <= Y <= 10^9
*/



// ******* using BFS (TLE) ******
class Solution {
public:
	int brokenCalc(int X, int Y) {
		if (Y <= X) return X-Y;
		unordered_set<int> taken;
		queue<int> q;
		q.push(X);
		int steps = 0;
		while (!q.empty()) {
			int size = q.size();
			while (size--) {
				int cur = q.front(); q.pop();
				if (cur == Y) return steps;
				if (cur <= (1e9)/2 && !taken.count(cur*2)) {
					q.push(cur*2);
					taken.insert(cur*2);
				}
				if (!taken.count(cur-1) && cur>1) {
					q.push(cur-1);
					taken.insert(cur-1);
				}
			}
			steps++;
		}
		return -1;
	}
};



/*
// ================= greedy ==================

if Y is smaller or equal to X return the difference, since
to go from a bigger to a smaller number, we can only perform decrease operation.

if Y is even, we can always double the last number (i.e. Y/2) to get Y,
which will cost us 1 + cost(Y/2).

if Y is odd, we can take get Y in 1 decrease operation on (Y+1),
which will cost us 1 + cost(Y+1);
*/
class Solution {
public:
	int brokenCalc(int X, int Y) {
		if (Y <= X) return X-Y;
		if (Y % 2 == 0) {
			return 1 + brokenCalc(X, Y/2);
		} else {
			return 1 + brokenCalc(X, Y+1);
		}
	}
};

// iterative
class Solution {
public:
	int brokenCalc(int X, int Y) {
		int moves = 0;
		while (Y > X) {
			if (Y % 2 == 0) Y = Y/2;
			else Y = Y+1;
			moves++;
		}
		return moves + X-Y;
	}
};

