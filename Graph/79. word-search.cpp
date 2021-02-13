// https://leetcode.com/problems/word-search/

/*
Given an m x n board and a word, find if the word exists in the grid.

The word can be constructed from letters of sequentially adjacent cells,
where "adjacent" cells are horizontally or vertically neighboring.
The same letter cell may not be used more than once.
*/



// alternatively we can use a vis table too
// but that isn't needed

class Solution {
	int R, C;
public:

	bool exist(vector<vector<char>>& board, string& word) {
		this->R = board.size();
		this->C = board[0].size();
		for (int i=0; i<R; i++) {
			for (int j=0; j<C; j++) {
				if (board[i][j] == word[0]) {
					if (dfs(board, word, 0, i, j)) return true;
				}
			}			
		}
		return false;
	}
	
	bool dfs(vector<vector<char>>& board, string& word, int start, int r, int c) {
		if (!isValid(board, word, start, r, c))
			return false;
		// mask this char to mark it as visited
		board[r][c] = '#';

		// if it is the last word
		if (start == word.size()-1)
			return true;

		// explore neighbors
		int dr[] = {-1,1,0,0}, dc[] = {0,0,-1,1};
		for (int i=0; i<4; i++) {
			int x = r+dr[i], y = c+dc[i];
			if (dfs(board, word, start+1, x, y))
				return true;
		}
		// if not found from this place, unvisit it (backtrack)
		// so that this place can again be checked
		board[r][c] = word[start];
		return false;
	}
	
	bool isValid(vector<vector<char>>& board, string& word, int start, int r, int c) {
		return r>=0 && r<R && c>=0 && c<C &&
			start<word.size() && board[r][c]==word[start];
	}
};

/*
 ********* TIME COMPLEXITY *********
 O(m * n * (3^L + 1))
 Having x^L means there are x branches that then branch x times and so on... until a total depth of L chosen branches. The "go back" case exits immediately. It does not branch to a total depth of L
*/