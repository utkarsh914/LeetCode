// https://leetcode.com/problems/snakes-and-ladders/

class Solution {
	int N;
public:
	int snakesAndLadders(vector<vector<int>>& B) {
		N = B.size();
		queue<int> q;
		vector<bool> vis(N*N+1, false);
		q.push(1);
		int steps = 0;

		while (!q.empty()) {
			int size = q.size();

			while (size--) {
				int u = q.front(); q.pop();
				if (vis[u]) continue;
				else vis[u]= true;
				if (u == N*N) return steps;

				for (int i = u+1; i <= min(u+6, N*N); i++) {
					int v = i;
					if (B[row(v)][col(v)] > 0)
						v = B[row(v)][col(v)];
					if (!vis[v]) q.push(v);
				}
			}

			steps++;
		}

		return -1;
	}

	int row(int x) {
		return (N-1) - ((x-1)/N);
	}

	int col(int x) {
		int y = (x-1) / N;
		if (y % 2 == 1)
			return (N-1) - ((x-1) % N);
		else
			return (x-1) % N;
	}
};