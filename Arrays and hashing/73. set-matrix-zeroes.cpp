/*
https://leetcode.com/problems/set-matrix-zeroes/

Given an m x n matrix. If an element is 0, set its entire row and column to 0. Do it in-place.

Follow up:
A straight forward solution using O(mn) space is probably a bad idea.
A simple improvement uses O(m + n) space, but still not the best solution.
Could you devise a constant space solution?
*/

class Solution {
public:
	void setZeroes(vector<vector<int>>& M) {
		int R=M.size(), C=M[0].size();
		bool fr = false, fc = false;
		
		for (int i=0; i<R; i++)
		for (int j=0; j<C; j++) {
			if (M[i][j]!=0) continue;
			if (i==0) fr=true;
			if (j==0) fc=true;
			M[i][0]=0, M[0][j]=0;
		}
		// nullify all rows except first row, and first col
		for (int i=1; i<R; i++)
		for (int j=1; j<C; j++) {
			if (M[i][0]==0 or M[0][j]==0) M[i][j]=0;
		}
		// first row
		if (fr) {
			for (int k=0; k<C; k++) M[0][k]=0;
		}
		// first col
		if (fc) {
			for (int k=0; k<R; k++) M[k][0]=0;
		}
	}
};

static auto _______ = [](){
	std::ios::sync_with_stdio(false);
	std::cin.tie(NULL);
	std::cout.tie(NULL);
	return 0;
}();