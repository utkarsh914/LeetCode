// https://leetcode.com/problems/kth-smallest-number-in-multiplication-table/

class Solution {
public:
	int findKthNumber(int m, int n, int k) {
		int start = 1, end = m*n;
		while (start < end) {
			int mid = start + (end-start)/2;
			if (countNums(m, n, mid) >= k)
				end = mid;
			else start = mid+1;
		}
		return start;
	}
	
	int countNums(int R, int C, int num) {
		int count = 0;
		for (int row=1; row <= R; row++) {
			int add = min(C, num/row);
			if (add == 0) break;
			count += add;
		}
		return count;
	}

/* // alternatively below binary search and linear search fn can be used too
	int countNums(int R, int C, int num) {
		int count = 0;
		for (int row = 1; row <= R; row++) {
			int start = 1, end = C, x = 0;
			while (start <= end) {
				int mid = start + (end-start)/2;
				if (mid*row <= num)
					x = mid, start = mid+1;
				else end = mid-1;
			}
			count += x;
		}
		return count;
	}

	int countNums(int R, int C, int k) {
		int count = 0;
		for (int r=1; r <= R; r++) {
			int x = C;
			while (x>0 && r*x > k) x--;
			count += x;
		}
		return count;
	}
*/
};

/*
-----------------------------------------------------------------------
"Is the result from binary search actually in the Multiplication Table?".
-----------------------------------------------------------------------

The answer is yes, and we also can apply proof by contradiction.
Denote num as the minimal input that satisfies enough function.
Let's assume that num is not in the table,
which means that num is not divisible by any val in [1, m], that is, num % val > 0.
Therefore, changing the input from num to num - 1 doesn't have any effect
on the expression add = min(num // val, n).
So enough(num - 1) would also return True, same as enough(num).
But we already know num is the minimal input satisfying enough function,
so enough(num - 1) has to be False.
Contradiction! The opposite of our original assumption is true: num is actually in the table.
*/