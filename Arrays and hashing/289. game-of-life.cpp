// https://leetcode.com/problems/game-of-life/

/*
According to Wikipedia's article: "The Game of Life, also known simply as Life, is a cellular automaton devised by the British mathematician John Horton Conway in 1970."

The board is made up of an m x n grid of cells, where each cell has an initial state: live (represented by a 1) or dead (represented by a 0). Each cell interacts with its eight neighbors (horizontal, vertical, diagonal) using the following four rules (taken from the above Wikipedia article):

Any live cell with fewer than two live neighbors dies as if caused by under-population.
Any live cell with two or three live neighbors lives on to the next generation.
Any live cell with more than three live neighbors dies, as if by over-population.
Any dead cell with exactly three live neighbors becomes a live cell, as if by reproduction.
The next state is created by applying the above rules simultaneously to every cell in the current state, where births and deaths occur simultaneously. Given the current state of the m x n grid board, return the next state.
*/


/*
0th bit stores current state
1st bit stores next state of each cell
*/
class Solution {
public:
	void gameOfLife(vector<vector<int>>& board) {
		int R = board.size(), C = board[0].size();
		for (int i=0; i < R; i++) {
			for (int j=0; j < C; j++) {
				int neighbours = countNeighbours(board, i, j, R, C);
				if ((board[i][j] & 1) == 0) {
					// reproduction
					if (neighbours == 3)
						board[i][j] |= (1<<1);
					continue;
				}
				// lives to next generation
				if (neighbours == 2 or neighbours == 3)
					board[i][j] |= (1<<1);
			}
		}

		for (int i=0; i < R; i++)
			for (int j=0; j < C; j++)
				board[i][j] >>= 1;
	}

	int countNeighbours(vector<vector<int>>& board, int i, int j, int R, int C) {
		int dr[] = {-1,-1,0,1,1,1,0,-1};
		int dc[] = {0,1,1,1,0,-1,-1,-1};
		int neighbours = 0;
		for (int k=0; k < 8; k++) {
			int x = i+dr[k], y = j+dc[k];
			if (x<R && x>=0 && y<C && y>=0)
				neighbours += (board[x][y] & 1) == 1;
		}
		return neighbours;
	}
};