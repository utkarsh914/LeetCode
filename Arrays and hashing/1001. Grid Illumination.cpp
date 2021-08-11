// https://leetcode.com/problems/grid-illumination/

/*
There is a 2D grid of size n x n where each cell of this grid has a lamp that is initially turned off.

You are given a 2D array of lamp positions lamps, where lamps[i] = [rowi, coli] indicates that the lamp at grid[rowi][coli] is turned on. Even if the same lamp is listed more than once, it is turned on.

When a lamp is turned on, it illuminates its cell and all other cells in the same row, column, or diagonal.

You are also given another 2D array queries, where queries[j] = [rowj, colj]. For the jth query, determine whether grid[rowj][colj] is illuminated or not. After answering the jth query, turn off the lamp at grid[rowj][colj] and its 8 adjacent lamps if they exist. A lamp is adjacent if its cell shares either a side or corner with grid[rowj][colj].

Return an array of integers ans, where ans[j] should be 1 if the cell in the jth query was illuminated, or 0 if the lamp was not.

 

Example 1:


Input: n = 5, lamps = [[0,0],[4,4]], queries = [[1,1],[1,0]]
Output: [1,0]
Explanation: We have the initial grid with all lamps turned off. In the above picture we see the grid after turning on the lamp at grid[0][0] then turning on the lamp at grid[4][4].
The 0th query asks if the lamp at grid[1][1] is illuminated or not (the blue square). It is illuminated, so set ans[0] = 1. Then, we turn off all lamps in the red square.

The 1st query asks if the lamp at grid[1][0] is illuminated or not (the blue square). It is not illuminated, so set ans[1] = 0. Then, we turn off all lamps in the red rectangle.

Example 2:

Input: n = 5, lamps = [[0,0],[4,4]], queries = [[1,1],[1,1]]
Output: [1,1]
Example 3:

Input: n = 5, lamps = [[0,0],[0,4]], queries = [[0,4],[0,1],[1,4]]
Output: [1,1,0]
 

Constraints:

1 <= n <= 109
0 <= lamps.length <= 20000
0 <= queries.length <= 20000
lamps[i].length == 2
0 <= rowi, coli < n
queries[j].length == 2
0 <= rowj, colj < n
*/









/*
We can use a similar technique as in N-Queens.
We track illuminated x and y coordinates, as well as two diagonals.
Ascending (left-to-right) diagonal a_d is identified by the sum of the coordinates,
and descending d_d - by their difference.

For example, for the light in position [3, 2],
we would record ++x[3], ++y[2], ++a_d[5], and ++d_d[1].
Since lamps can be removed later, we use hashmap (not a hashset)
to track how many lamps are illuminating coordinates and diagonals.
Also, we use another hashmap ls to track lamp positions.
*/
class Solution {
	struct pairHash {
	  size_t operator()(const pair<int, int> &x) const {
		  return x.first ^ x.second;
	  }
	};

	int R, C;
	unordered_map<pair<int,int>, bool, pairHash> hasLamp;
	unordered_map<int, int> row, col;
	unordered_map<int, int> leftDiag, rightDiag;
	
public:
	vector<int> gridIllumination(int n, vector<vector<int>>& lamps,
		vector<vector<int>>& queries) {
		R = n, C = n;
		
		for (auto& l : lamps) {
			int i = l[0], j = l[1];
			if (hasLamp[{i,j}] == false)
				turnOn(i, j);
		}
		
		vector<int> ans;
		int dr[8] = {1,-1,0,0,1,1,-1,-1};
		int dc[8] = {0,0,-1,1,1,-1,1,-1};
		
		for (auto& q : queries) {
			int i = q[0], j = q[1];
			ans.push_back(isLampLit(i, j));
			
			if (hasLamp[{i,j}] == true)
				turnOff(i, j);
			
			for (int k = 0; k < 8; k++) {
				int x = i+dr[k], y = j+dc[k];
				if (x<0 or x>=n or y<0 or y>=n) continue;
				if (hasLamp[{x,y}] == true)
					turnOff(x, y);
			}
		}
		
		return ans;
	}
	
	inline void turnOn(int i, int j) {
		row[i]++, col[j]++;
		leftDiag[leftDiagInd(i, j)]++;
		rightDiag[rightDiagInd(i, j)]++;
		hasLamp[{i,j}] = true;
	}
	
	inline void turnOff(int i, int j) {
		row[i]--, col[j]--;
		leftDiag[leftDiagInd(i, j)]--;
		rightDiag[rightDiagInd(i, j)]--;
		hasLamp[{i,j}] = false;
	}
	
	inline int isLampLit(int i, int j) {
		if (row[i] > 0 or col[j] > 0 or
		 leftDiag[leftDiagInd(i, j)] or
		 rightDiag[rightDiagInd(i, j)])
			return 1;
		else return 0;
	}
	
	inline int leftDiagInd(int i, int j) {
		return C-1-j + i;
	}
	
	inline int rightDiagInd(int i, int j) {
		return i + j;
	}
};