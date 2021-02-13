/*
https://leetcode.com/problems/regions-cut-by-slashes/

n a N x N grid composed of 1 x 1 squares, each 1 x 1 square consists of a /, \, or blank space.
These characters divide the square into contiguous regions.
(Note that backslash characters are escaped, so a \ is represented as "\\".)
Return the number of regions.

Example 1:
Input:
[
  " /",
  "/ "
]
Output: 2
Explanation: The 2x2 grid is as follows:

Example 2:
Input:
[
  " /",
  "  "
]
Output: 1
Explanation: The 2x2 grid is as follows:

Example 3:
Input:
[
  "\\/",
  "/\\"
]
Output: 4
Explanation: (Recall that because \ characters are escaped, "\\/" refers to \/, and "/\\" refers to /\.)
The 2x2 grid is as follows:

Example 4:
Input:
[
  "/\\",
  "\\/"
]
Output: 5
Explanation: (Recall that because \ characters are escaped, "/\\" refers to /\, and "\\/" refers to \/.)
The 2x2 grid is as follows:

Example 5:
Input:
[
  "//",
  "/ "
]
Output: 3
Explanation: The 2x2 grid is as follows:

Note:
1 <= grid.length == grid[0].length <= 30
grid[i][j] is either '/', '\', or ' '.

*/


/*
 ******** IT IS BASICALLY LIKE FIND NO. OF ISLANDS *****

Split a cell in to 4 parts like this.
We give it a number top is 0, right is 1, bottom is 2 left is 3.

image: https://assets.leetcode.com/users/images/c1f05c28-9c76-4211-b25a-4fe8df539938_1600322994.7242403.png
(photo by @Sabbi_coder)

Two adjacent parts in different cells are contiguous regions.
In case '/', top and left are contiguous, botton and right are contiguous.
In case '\\', top and right are contiguous, bottom and left are contiguous.
In case ' ', all 4 parts are contiguous.

Congratulation.
Now you have another problem of counting the number of islands.
*/


// ************* UNION FIND BASED *************
class Solution {
public:
int count, gridSize;
vector<int> parent;

int find(int x) {
	if (parent[x] != x)
		parent[x] = find(parent[x]);
	return parent[x];
}

void uni(int x, int y) {
	int xset = find(x);
	int yset = find(y);
	if (xset != yset) {
		parent[xset] = yset;
		count--;
	}
}

int ind(int r, int c, int i) {
	return (r * gridSize + c) * 4 + i;
}

int regionsBySlashes(vector<string>& grid) {
	gridSize = grid.size();
	count = gridSize * gridSize * 4;
	parent = vector<int> (count, 0);
	for (int i=0; i<count; i++) parent[i]=i;

	for (int i=0; i<gridSize; i++) {
		for (int j=0; j<gridSize; j++) {
			if (i>0) uni(ind(i-1, j, 2), ind(i, j, 0));
			if (j>0) uni(ind(i, j-1, 1), ind(i, j, 3));
			if (grid[i][j] != '/') {
				uni(ind(i, j, 0), ind(i, j, 1));
				uni(ind(i, j, 2), ind(i, j, 3));
			}
			if (grid[i][j] != '\\') {
				uni(ind(i, j, 0), ind(i, j, 3));
				uni(ind(i, j, 1), ind(i, j, 2));
			}
		}
	}
	return count;
}};