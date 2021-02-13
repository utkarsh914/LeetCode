/*
https://leetcode.com/problems/add-to-array-form-of-integer/
*/

class Solution {
public:
	vector<int> addToArrayForm(vector<int>& A, int k) {
		vector<int> B;
		int c=0, i=A.size()-1;
		for ( ; i>=0; i--, k/=10) {
			if (!k) k=0;
			int n = k%10;
			B.push_back((c+n+A[i])%10);
			c = (c+n+A[i])/10;
		}
		while (k) {
			int n = k%10; k/=10;
			B.push_back((c+n)%10);
			c = (c+n)/10;
		}
		if (c) B.push_back(c);
		reverse(B.begin(), B.end());
		return B;
	}
};