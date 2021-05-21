// https://leetcode.com/problems/queens-that-can-attack-the-king/

/*
On an 8x8 chessboard, there can be multiple Black Queens and one White King.

Given an array of integer coordinates queens that represents the positions of the Black Queens, and a pair of coordinates king that represent the position of the White King, return the coordinates of all the queens (in any order) that can attack the King.

 

Example 1:



Input: queens = [[0,1],[1,0],[4,0],[0,4],[3,3],[2,4]], king = [0,0]
Output: [[0,1],[1,0],[3,3]]
Explanation:  
The queen at [0,1] can attack the king cause they're in the same row. 
The queen at [1,0] can attack the king cause they're in the same column. 
The queen at [3,3] can attack the king cause they're in the same diagnal. 
The queen at [0,4] can't attack the king cause it's blocked by the queen at [0,1]. 
The queen at [4,0] can't attack the king cause it's blocked by the queen at [1,0]. 
The queen at [2,4] can't attack the king cause it's not in the same row/column/diagnal as the king.
*/






/*
Check 8 directions around the King.
Find the nearest queen in each direction.
*/
class Solution {
public:
	vector<vector<int>> queensAttacktheKing(vector<vector<int>>& q, vector<int>& k) {
		vector<vector<int>> ans;
		set<vector<int>> Q_set(q.begin(), q.end());

		int dr[] = {-1,-1,-1, 0, 0,+1,+1,+1};
		int dc[] = {-1, 0,+1,-1,+1,-1, 0,+1};

		// explore all 8 dir
		for (int i = 0; i < 8; i++) {
			int r = k[0] + dr[i], c = k[1] + dc[i];
			// keep going in that dir until a queen is found
			while (r>=0 && r<8 && c>=0 && c<8) {
				if (Q_set.count({ r, c })) {
					ans.push_back({ r, c });
					break;
				}
				r += dr[i], c += dc[i];
			}
		}
		// sort the queens based on position
		sort(ans.begin(), ans.end(), [](auto& a, auto& b) {
			if (a[0] == b[0]) return a[1] < b[1];
			return a[0] < b[0];
		});
		return ans;
	}
};