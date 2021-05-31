// https://leetcode.com/problems/minesweeper/

/*
Let's play the minesweeper game (Wikipedia, online game)!

You are given an m x n char matrix board representing the game board where:

'M' represents an unrevealed mine,
'E' represents an unrevealed empty square,
'B' represents a revealed blank square that has no adjacent mines (i.e., above, below, left, right, and all 4 diagonals),
digit ('1' to '8') represents how many mines are adjacent to this revealed square, and
'X' represents a revealed mine.
You are also given an integer array click where click = [clickr, clickc] represents the next click position among all the unrevealed squares ('M' or 'E').

Return the board after revealing this position according to the following rules:

If a mine 'M' is revealed, then the game is over. You should change it to 'X'.
If an empty square 'E' with no adjacent mines is revealed, then change it to a revealed blank 'B' and all of its adjacent unrevealed squares should be revealed recursively.
If an empty square 'E' with at least one adjacent mine is revealed, then change it to a digit ('1' to '8') representing the number of adjacent mines.
Return the board when no more squares will be revealed.
 

Example 1:


Input: board = [["E","E","E","E","E"],["E","E","M","E","E"],["E","E","E","E","E"],["E","E","E","E","E"]], click = [3,0]
Output: [["B","1","E","1","B"],["B","1","M","1","B"],["B","1","1","1","B"],["B","B","B","B","B"]]
Example 2:


Input: board = [["B","1","E","1","B"],["B","1","M","1","B"],["B","1","1","1","B"],["B","B","B","B","B"]], click = [1,2]
Output: [["B","1","E","1","B"],["B","1","X","1","B"],["B","1","1","1","B"],["B","B","B","B","B"]]
 

Constraints:

m == board.length
n == board[i].length
1 <= m, n <= 50
board[i][j] is either 'M', 'E', 'B', or a digit from '1' to '8'.
click.length == 2
0 <= clickr <= m
0 <= clickc <= n
board[clickr][clickc] is either 'M' or 'E'.

*/









/*
This is a typical Search problem, either by using DFS or BFS. Search rules:

If click on a mine ('M'), mark it as 'X', stop further search.
If click on an empty cell ('E'), depends on how many surrounding mine:
2.1 Has surrounding mine(s), mark it with number of surrounding mine(s), stop further search.
2.2 No surrounding mine, mark it as 'B', continue search its 8 neighbors.
*/
class Solution {
	int dr[8] = {-1,-1,-1,0,0,1,1,1};
	int dc[8] = {-1,0,1,-1,1,-1,0,1};
	int R, C;

public:
	vector<vector<char>> updateBoard(vector<vector<char>>& B,
		vector<int>& click) {
		R = B.size(), C = B[0].size();
		processClick(B, click[0], click[1]);
		return B;
	}

	void processClick(vector<vector<char>>& B, int r, int c) {
		// mine detected. stop here
		if (B[r][c] == 'M') {
			B[r][c] = 'X';
			return;
		}

		if (B[r][c] != 'E') return;

		int count = countNeighbors(B, r, c);
		if (count > 0) {
			B[r][c] = count + '0';
		}
		else {
			B[r][c] = 'B';
			// recursively reveal all neighbors
			for (int i = 0; i < 8; i++) {
				int x = r + dr[i], y = c + dc[i];
				if (x<0 or x>=R or y<0 or y>=C) continue;
				processClick(B, x, y);
			}
		}
	}

	int countNeighbors(vector<vector<char>>& B, int r, int c) {
		int count = 0;
		for (int i = 0; i < 8; i++) {
			int x = r + dr[i], y = c + dc[i];
			if (x>=0 && x<R && y>=0 && y<C && B[x][y]=='M')
				count++;
		}
		return count;
	}
};