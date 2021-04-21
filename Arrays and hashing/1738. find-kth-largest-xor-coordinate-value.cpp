// https://leetcode.com/problems/find-kth-largest-xor-coordinate-value/

/*

*/

class Solution {
public:
	int kthLargestValue(vector<vector<int>>& M, int k) {
		// top row
		for (int j = 1; j < M[0].size(); j++)
			M[0][j] = M[0][j] ^ M[0][j-1];
		// left col
		for (int i = 1; i < M.size(); i++)
			M[i][0] = M[i][0] ^ M[i-1][0];

		for (int i = 1; i < M.size(); i++)
			for (int j = 1; j < M[0].size(); j++)
				M[i][j] = M[i][j] ^ M[i-1][j] ^ M[i][j-1] ^ M[i-1][j-1];

		priority_queue<int, vector<int>, greater<int>> pq;
		for (int i = 0; i < M.size(); i++) {
			for (int j = 0; j < M[0].size(); j++) {
				pq.push(M[i][j]);
				if (pq.size() > k) pq.pop();
			}
		}

		return pq.top();
	}
};