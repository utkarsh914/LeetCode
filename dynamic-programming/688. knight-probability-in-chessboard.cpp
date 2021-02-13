// https://leetcode.com/problems/knight-probability-in-chessboard/

// similar to: 576. out-of-boundary-paths

class Solution {
public:
	double knightProbability(int N, int K, int r, int c) {
		double dp[25][25][101] = {};
		int moves[8][2] = {{1,2}, {1,-2}, {2,1}, {2,-1}, {-1,2}, {-1,-2}, {-2,1}, {-2,-1}};

		for (int k=0; k<=K; k++) {
			for (int i=0; i<N; i++) {
				for (int j=0; j<N; j++) {
					if (k==0) {
						dp[i][j][k] = 1.0;
					}
					else {
						for (int x=0; x<8; x++) {
							int row = i+moves[x][0], col = j+moves[x][1];
							if (isValid(N, row, col)) dp[i][j][k] += dp[row][col][k-1];
						}
					}
				}
			}
		}

		return dp[r][c][K] / pow(8,K); // total possible moves is 8^k
	}

	bool isValid(int N, int i, int j) {
		return i>=0 && i<N && j>=0 && j<N;
	}
};









class Solution {
	bool isValid(int N, int i, int j) {
		return i>=0 && i<N && j>=0 && j<N;
	}

public:
	double knightProbability(int N, int K, int r, int c) {
		double dp[25][25][101] = {};

		for (int k=0; k<=K; k++) {
			for (int i=0; i<N; i++) {
				for (int j=0; j<N; j++) {
					if (k==0) dp[i][j][k] = 1;
					else {
						double tl_1 = isValid(N, i-1, j-2) ? dp[i-1][j-2][k-1] : 0;
						double tl_2 = isValid(N, i-2, j-1) ? dp[i-2][j-1][k-1] : 0;
						double tr_1 = isValid(N, i-2, j+1) ? dp[i-2][j+1][k-1] : 0;
						double tr_2 = isValid(N, i-1, j+2) ? dp[i-1][j+2][k-1] : 0;
						double br_1 = isValid(N, i+1, j+2) ? dp[i+1][j+2][k-1] : 0;
						double br_2 = isValid(N, i+2, j+1) ? dp[i+2][j+1][k-1] : 0;
						double bl_1 = isValid(N, i+2, j-1) ? dp[i+2][j-1][k-1] : 0;
						double bl_2 = isValid(N, i+1, j-2) ? dp[i+1][j-2][k-1] : 0;
						dp[i][j][k] = tl_1 + tl_2 + tr_1 + tr_2 + br_1 + br_2 + bl_1 + bl_2;
					}
				}
			}
		}

		return dp[r][c][K] / pow(8,K); // total possible moves is 8^k
	}
};