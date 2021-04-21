// https://leetcode.com/problems/number-of-submatrices-that-sum-to-target/

/*
Given a matrix and a target, return the number of non-empty submatrices that sum to target.

A submatrix x1, y1, x2, y2 is the set of all cells matrix[x][y] with x1 <= x <= x2 and y1 <= y <= y2.

Two submatrices (x1, y1, x2, y2) and (x1', y1', x2', y2') are different if they have some coordinate that is different: for example, if x1 != x1'.
*/



/*
Intuition
Preaquis: 560. Subarray Sum Equals K
Find the Subarray with Target Sum in linear time.


Explanation
For each row, calculate the prefix sum.
For each pair of columns,
calculate the accumulated sum of rows.
Now this problem is same to, "Find the Subarray with Target Sum".


Complexity
Time O(MN^2)
Space O(N)

*/


class Solution {
	int R, C;
	vector<vector<int>> ps;
public:
	int numSubmatrixSumTarget(vector<vector<int>>& m, int target) {
		R = m.size(), C = m[0].size();
		calculatePreSum(m);

		int count = 0;

		for (int r1=0; r1 < R; r1++) {
			for (int r2=r1; r2 < R; r2++) {
				count += countSubarraysWithSum(r1, r2, target);
			}
		}

		return count;
	}

	int countSubarraysWithSum(int r1, int r2, int target) {
		unordered_map<int,int> map; // presum -> freq
		map[0] = 1;
		int sum = 0, count = 0;

		for (int c1=0, c2=0; c2 < C; c2++) {
			sum = presum(r1, r2, c1, c2);
			if (map.count(sum - target))
				count += map[sum - target];
			map[sum]++;
		}

		return count;
	}

	void calculatePreSum(vector<vector<int>>& m) {
		ps.resize(R+1, vector<int> (C+1, 0));
		for (int i=1; i <= R; i++)
			for (int j=1; j <= C; j++)
				ps[i][j] = ps[i-1][j] + ps[i][j-1] -ps[i-1][j-1] + m[i-1][j-1];
	}

	int presum(int r1, int r2, int c1, int c2) {
		return ps[r2+1][c2+1] - ps[r1][c2+1] - ps[r2+1][c1] + ps[r1][c1];
	}
};