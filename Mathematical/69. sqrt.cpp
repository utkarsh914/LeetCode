// https://leetcode.com/problems/sqrtx/submissions/

class Solution {
public:
	int mySqrt(int x) {
		if (x==0) return 0;

		int lo=1, hi=x/2;

		while (lo < hi) {
			int m = lo+(hi-lo)/2;
			if (m > x/m) hi=m-1;
			else {
				if ((m+1) > x/(m+1))
					return m;
				else lo=m+1;
			}
		}
		
		return lo;
	}
};