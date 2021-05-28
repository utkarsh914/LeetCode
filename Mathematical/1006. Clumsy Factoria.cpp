// https://leetcode.com/problems/clumsy-factorial/


class Solution {
public:
	int clumsy(int N) {
		int ans = eval(N, 1);
		N -= 4;

		while (N > 0) {
			ans += eval(N, -1);
			N -= 4;
		}

		return ans;
	}

	int eval(int n, int sign = 1) {
		if (n <= 0) return 0;

		int a = n * sign;
		int b = (n - 1 > 0) ? n - 1 : 1;
		int c = (n - 2 > 0) ? n - 2 : 1;
		int d = (n - 3 > 0) ? n - 3 : 0;

		return (a * b) / c + d;
	}
};





class Solution {
public:
	int clumsy(int N) {
		int res = 0, cur = 0, index = -1;

		while (N > 0) {
			switch (++index % 4) {
				case 0:
					cur = index == 0 ? N : -N;
					break;
				case 1:
					cur *= N;
					break;
				case 2:
					cur /= N;
					break;
				case 3:
					res += cur + N;
					cur = 0;
					break;
			}
			N--; 
		}

		return res + cur; 
	}
};

/*

class Solution:
	def evaluate(self, n: int, sign: int) -> int:
		a = n
		b = n-1 if n-1 > 0 else 1
		c = n-2 if n-2 > 0 else 1
		d = n-3 if n-3 > 0 else 0
		return sign * ((a * b) // c) + d
	
	def clumsy(self, n: int) -> int:
		ans = self.evaluate(n, 1)
		n -= 4
		while n > 0:
			ans += self.evaluate(n, -1)
			n -= 4
		return ans
*/