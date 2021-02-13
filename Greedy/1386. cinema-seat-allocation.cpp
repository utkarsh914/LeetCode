// https://leetcode.com/problems/cinema-seat-allocation/

class Solution {
public:
	int maxNumberOfFamilies(int n, vector<vector<int>>& seats) {
		sort(seats.begin(), seats.end());
		int size = seats.size(), i = 0, rows = 0, count = 0;
		while (i < size) {
			vector<bool> f(11, true);
			int curRow = seats[i][0];
			rows++;
			while (i<size && seats[i][0]==curRow) {
				f[seats[i++][1]] = false;
			}
			// count groups in curr row
			bool flag = false;
			if (f[2] && f[3] && f[4] && f[5]) count += 1, flag=1;
			if (f[6] && f[7] && f[8] && f[9]) count += 1, flag=1;
			if (!flag && f[4] && f[5] && f[6] && f[7]) count += 1;
		}
		
		count += (n-rows)*2;
		return count;
	}
};