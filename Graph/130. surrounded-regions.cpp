/*
https://leetcode.com/problems/surrounded-regions/

Given a 2D board containing 'X' and 'O' (the letter O), capture all regions surrounded by 'X'.
A region is captured by flipping all 'O's into 'X's in that surrounded region.

Example:

X X X X
X O O X
X X O X
X O X X

After running your function, the board should be:

X X X X
X X X X
X X X X
X O X X

Explanation:
Surrounded regions shouldn’t be on the border, which means that any 'O' on the border of the board are not flipped to 'X'.
Any 'O' that is not on the border and it is not connected to an 'O' on the border will be flipped to 'X'.
Two cells are connected if they are adjacent cells connected horizontally or vertically.
*/

class Solution {
public:
int R,C;

void dfs(int r, int c, vector<vector<char>>& board) {
	board[r][c] = '.';
	int dr[4] = {-1,1,0,0}, dc[4] = {0,0,1,-1};
	for (int k=0; k<4; k++) {
		int rr=r+dr[k], cc=c+dc[k];
		if (rr<0 or rr>=R or cc<0 or cc>=C or board[rr][cc]!='O') continue;
		dfs(rr, cc, board);
	}
}

void solve(vector<vector<char>>& board) {
	R=board.size();
	if (!R) return;
	C=board[0].size();
	for (int i=0; i<R; i++) {
		for (int j=0; j<C; j++) {
			if (i==0 or i==R-1 or j==0 or j==C-1) {
				if (board[i][j]=='O') dfs(i, j, board);
			}
		}
	}
	// after dfs done, ineligible 0's will be changed to '.'
	// so, except '.' set all other elements to 'x'
	for (int i=0; i<R; i++) {
		for (int j=0; j<C; j++) {
			if (board[i][j]=='.') board[i][j]='O';
			else board[i][j]='X';
		}
	}
	
}};