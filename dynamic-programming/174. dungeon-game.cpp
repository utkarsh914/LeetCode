// https://leetcode.com/problems/dungeon-game/

/*
The demons had captured the princess and imprisoned her in the bottom-right corner of a dungeon.
The dungeon consists of m x n rooms laid out in a 2D grid.
Our valiant knight was initially positioned in the top-left room
and must fight his way through dungeon to rescue the princess.

The knight has an initial health point represented by a positive integer.
If at any point his health point drops to 0 or below, he dies immediately.

Some of the rooms are guarded by demons (represented by negative integers),
so the knight loses health upon entering these rooms;
other rooms are either empty (represented as 0) or contain magic orbs
that increase the knight's health (represented by positive integers).

To reach the princess as quickly as possible,
the knight decides to move only rightward or downward in each step.

Return the knight's minimum initial health so that he can rescue the princess.

Note that any room can contain threats or power-ups,
even the first room the knight enters and the bottom-right room
where the princess is imprisoned.
*/






/*
Many users have asked question if solution for this problem can also be achieved
from top left corner navigating to the bottom right or not.
I believe it cannot be achieved.

This is because the path to be taken depends upon the future
demons seen on the way to princess, which is not available in top down approach.

e.g. Consider the matrix

0, -2, 0
-3, 0, 0
10, 0 P', -5 P

P' and P are potential positions for princess

If the matrix consists only of two columns (say princess is at P')
we would take the path Right->Down->Down (minimize the health and result = -(-2) + 1 = 3

However, if the matrix consists of three columns
we would take the path of Down->Down->Right->Right with result = -(-3)+1 = 4
Note that the previous path here would return suboptimal result = -(-2) + -(-5) + 1 = 8

This information cannot be computed when we are at node i=2, j=1
assuming zero based index
(i.e. we do not know if we have to minimize the health at current point
or take maximum positive value for the sake of higher health cost to account for future demons)
This can only be factored in by computing the result in bottom up manner.



 *****  ALSO  *****
Because it is known that the knight has to reach the end with at least one health point
and the health point with which the knight should start with is not known.

*/


int calculateMinimumHP(vector<vector<int>>& dungeon) {
	int M = dungeon.size();
	int N = dungeon[0].size();
	// hp[i][j] represents the min hp needed at position (i, j)
	// Add dummy row and column at bottom and right side
	vector<vector<int>> hp(M + 1, vector<int>(N + 1, INT_MAX));
	hp[M][N - 1] = 1;
	hp[M - 1][N] = 1;

	for (int i = M - 1; i >= 0; i--) {
		for (int j = N - 1; j >= 0; j--) {
			int need = min(hp[i + 1][j], hp[i][j + 1]) - dungeon[i][j];
			hp[i][j] = max(1, need);
		}
	}
	return hp[0][0];
}





// 1-D Code
int calculateMinimumHP(vector<vector<int>>& dungeon) {
	int height = dungeon.size();
	int len = dungeon[0].size();
	vector<int> dp(len+1, INT_MAX);
	dp[len-1] = 1;

	for (int i = height-1; i >= 0; i--) {
		for (int j = len-1; j >= 0; j--) {
			int need = min(dp[j+1], dp[j]) - dungeon[i][j];
			dp[j] = max(1, need);
		}
	}

	return dp[0];
}