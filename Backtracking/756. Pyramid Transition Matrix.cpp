// https://leetcode.com/problems/pyramid-transition-matrix/

/*
We are stacking blocks to form a pyramid. Each block has a color which is a one-letter string.

We are allowed to place any color block C on top of two adjacent blocks of colors A and B, if and only if ABC is an allowed triple.

We start with a bottom row of bottom, represented as a single string. We also start with a list of allowed triples allowed. Each allowed triple is represented as a string of length 3.

Return true if we can build the pyramid all the way to the top, otherwise false.

 

Example 1:

Input: bottom = "BCD", allowed = ["BCG","CDE","GEA","FFF"]
Output: true
Explanation:
We can stack the pyramid like this:
		A
	 / \
	G	 E
 / \ / \
B	 C	 D

We are allowed to place G on top of B and C because BCG is an allowed triple.	Similarly, we can place E on top of C and D, then A on top of G and E.
Example 2:

Input: bottom = "AABA", allowed = ["AAA","AAB","ABA","ABB","BAC"]
Output: false
Explanation:
We cannot stack the pyramid to the top.
Note that there could be allowed triples (A, B, C) and (A, B, D) with C != D.
 

Constraints:

2 <= bottom.length <= 8
0 <= allowed.length <= 200
allowed[i].length == 3
The letters in all input strings are from the set {'A', 'B', 'C', 'D', 'E', 'F', 'G'}.
*/









/*
--------- simple backtracking --------

I assume the matrix G to be inverted, like
e.g. for bottom = "BCD"

B C D
G E
A

above is the target matrix.
so, we start with a matrix that looks like below

B C D
. . #
. # #

here, '.' means we have to place a letter here,
'#' means we don't bother with this cell, and just proceed

*/
class Solution {
	int N;
	vector<string> G;
	unordered_set<string> allowed;

public:
	bool pyramidTransition(string& bottom, vector<string>& allowed_) {
		this->N = bottom.size();
		for (auto& s : allowed_)
			allowed.insert(s);

		// initialize G matrix
		G.resize(N);
		G[0] = bottom;
		// fill other rows
		for (int i = 1; i < N; i++)
			G[i] = string(N-i, '.') + string(i, '#');

		// need to backtrack from 1 indexed row
		return backtrack(N);
	}

	bool backtrack(int cell) {
		if (cell >= N * N) return true; // reached the end
		int r = cell / N, c = cell % N;
		if (G[r][c] == '#') return backtrack(cell + 1);

		for (char ch = 'A'; ch <= 'G'; ch++) {
			if (canPlace(r, c, ch)) {
				G[r][c] = ch;
				if (backtrack(cell + 1))
					return true;
				// G[r][c] = '.';
			}
		}

		return false;
	}

	bool canPlace(int r, int c, char ch) {
		string mask;
		mask += G[r-1][c]; // upper
		mask += G[r-1][c+1]; // upper right
		mask += ch; // cur char
		return allowed.count(mask);
	}
};





// use bit masks
class Solution {
	int N;
	vector<string> G;
	unordered_set<int> allowed;

public:
	bool pyramidTransition(string& bottom, vector<string>& allowed_) {
		this->N = bottom.size();
		for (auto& s : allowed_) {
			int mask = s[0] - 'A';
			mask = (mask << 8) | (s[1] - 'A');
			mask = (mask << 8) | (s[2] - 'A');
			allowed.insert(mask);
		}

		// initialize G matrix
		G.resize(N);
		G[0] = bottom;
		// fill other rows
		for (int i = 1; i < N; i++)
			G[i] = string(N-i, '.') + string(i, '#');

		// need to backtrack from 1 indexed row
		return backtrack(N);
	}

	bool backtrack(int cell) {
		if (cell >= N * N) return true; // reached the end
		int r = cell / N, c = cell % N;
		if (G[r][c] == '#') return backtrack(cell + 1);

		for (char ch = 'A'; ch <= 'G'; ch++) {
			if (canPlace(r, c, ch)) {
				G[r][c] = ch;
				if (backtrack(cell + 1))
					return true;
			}
		}

		return false;
	}

	bool canPlace(int r, int c, char ch) {
		int mask = G[r-1][c] - 'A'; // upper
		mask = (mask << 8) | (G[r-1][c+1] - 'A'); // upper right
		mask = (mask << 8) | (ch - 'A'); // cur char
		return allowed.count(mask);
	}
};








class Solution {
	unordered_map<string, vector<char>> m;
public:
	bool pyramidTransition(string bottom, vector<string>& allowed) {
		for(auto& s:allowed) m[s.substr(0, 2)].push_back(s.back());
		return helper(bottom, 0, "");
	}
	bool helper(string bottom, int start, string next){
		if(bottom.size() == 1) return true;
		if(start == bottom.size() - 1) return helper(next, 0, "");
		for(char c : m[bottom.substr(start, 2)])
			if(helper(bottom, start+1, next+c)) return true;
		return false;
	}
};