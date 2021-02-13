// https://leetcode.com/problems/powx-n/


class Solution {
public:
	double myPow(double x, int n) {
		if (n == 0) return 1;
		if (n == INT_MIN) {
			x = x*x;
			n = n/2;
		}
		if (n < 0) {
			n = -n;
			x = 1/x;
		}
		
		return n%2==0 ? myPow(x*x, n/2) : x*myPow(x*x, n/2);
	}
};





// ******** dirty solution ********
class Solution {
public:
	double myPow(double x, int n_) {
		if (x==1.0) return x;
		else if (x==-1) {
			return n_%2 ? -1 : 1;
		}
		double a = 1;
		long long int n = n_;
		if (n<0) {
			n = -n;
			x = 1/x;
		}
		while (n--) {
			a *= x;
			if (abs(a)<0.000001)
				break;
		}
		return a;
	}
};