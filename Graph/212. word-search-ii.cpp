// https://leetcode.com/problems/word-search-ii/


// same as 79:word-search
// just run word search for every word in given vector
/*
	NOTE: i had to use vis array here, however it wasn't necessary in Q-79
	as i need to find multiple words from same grid, so grid has to be in original state
	before searching any word. And if we're not using vis array but directly modifying the grid,
	the grid won't remain the same when we search for next word from the vector
	hence, vis array is needed, and that will be reset before searching any word
*/
class Solution {
	int R, C;
	bool vis[12][12];

public:
	vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
		this->R = board.size();
		this->C = board[0].size();
		vector<string> res;
		for (string& w:words) {
			if (exist(board, w)) {
				res.push_back(w);
			}
		}
		return res;
	}
	
	bool exist(vector<vector<char>>& board, string& word) {
		for (int i=0; i<R; i++) {
			for (int j=0; j<C; j++) {
				if (board[i][j] == word[0]) {
					memset(vis, 0, sizeof(vis));
					if (dfs(board, word, 0, i, j))
						return true;
				}
			}
		}
		return false;
	}
	
	bool dfs(vector<vector<char>>& board, string& word, int start, int r, int c) {
		if (!isValid(board, word, start, r, c))
			return false;
		// mask this char to mark it as visited
		if (vis[r][c]) return false;
		vis[r][c] = true;

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
		vis[r][c] = false;
		return false;
	}
	
	bool isValid(vector<vector<char>>& board, string& word, int start, int r, int c) {
		return r>=0 && r<R && c>=0 && c<C &&
			start<word.size() && board[r][c]==word[start];
	}
};