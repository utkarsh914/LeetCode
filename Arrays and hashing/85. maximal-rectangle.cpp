

class Solution {
public:
	int maximalRectangle(vector<vector<char>>& M);
};

int Solution::maximalRectangle(vector<vector<char>>& M) {
	int R = M.size();
	if (!R) return 0;
	int C = M[0].size();
	if (!C) return 0;
	int left[C], right[C], height[C];
	fill_n(left, C, 0); fill_n(right, C, C); fill_n(height, C, 0);
	int ans = 0;

	for (int i=0; i<R; i++) {
		// calculate heights of 1's
		for (int j=0; j<C; j++) {
			if (M[i][j]=='0') height[j]=0;
			else height[j]++;
		}
		int cur_left=0, cur_right=C;
		// fill indices of closest zero on left
		for (int j=0; j<C; j++) {
			if (M[i][j]=='0') left[j]=0, cur_left=j+1;
			else left[j]=max(left[j], cur_left);
		}
		// fill indices of closest zero on right
		for (int j=C-1; j>=0; j--) {
			if (M[i][j]=='0') right[j]=C, cur_right=j;
			else right[j]=min(right[j], cur_right);
		}
		// find largest rectangle in histogram now
		for (int j=0; j<C; j++)
			ans = max(ans, height[j]*(right[j]-left[j]));
	}

	for (int i=0; i<C; i++) cout<<left[i]<<" ";
	cout << "\n";
	for (int i=0; i<C; i++) cout<<right[i]<<" ";
	cout << "\n";
	for (int i=0; i<C; i++) cout<<height[i]<<" ";
	
	return ans;
}