// https://leetcode.com/problems/sort-the-matrix-diagonally/

class Solution {
	// use (i-j) as index for every diagonal element
public:
	vector<vector<int>> diagonalSort(vector<vector<int>>& mat) {
		unordered_map<int, priority_queue<int, vector<int>, greater<int>>> lists;
		for (int i=0; i<mat.size(); i++)
			for (int j=0; j<mat[0].size(); j++)
				lists[i-j].push(mat[i][j]);

		for (int i=0; i<mat.size(); i++) {
			for (int j=0; j<mat[0].size(); j++) {
				auto& pq = lists[i-j];
				mat[i][j] = pq.top();
				pq.pop();
			}
		}
		return mat;
	}
};