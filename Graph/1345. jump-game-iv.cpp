// https://leetcode.com/problems/jump-game-iv/

class Solution {
public:
	int minJumps(vector<int>& arr) {
		if (arr.size() == 1) return 0;

		unordered_map<int, vector<int>> map;
		// store frequencies
		for (int i=0; i<arr.size(); i++) {
			map[arr[i]].push_back(i);
		}

		// perform dfs and find steps to reach end
		int steps = 0, target = arr.size()-1;
		queue<int> q; q.push(0);
		vector<bool> vis(arr.size(), false);
		vis[0] = true;

		while (!q.empty()) {
			int size = q.size();
			while (size--) {
				int i = q.front(); q.pop();
				if (i == target) return steps;
				// push its branches
				auto& indices = map[arr[i]];
				if (i>0) indices.push_back(i-1);
				if (i+1<arr.size()) indices.push_back(i+1);
				for (int ind: indices) {
					if (!vis[ind]) {
						vis[ind] = true;
						q.push(ind);
					}
				}
				indices.clear(); // very imp. to avoid later lookup map arr[i]
			}
			steps++;
		}

		return steps;
	}
};
/*
********* EXPLANATION FOR USING indices.clear() **********
If you do not clear, every time you see value in which you already perform the arr[i] == arr[j] movement,
you will loop through the hashmap again and would result in possibly looping through the same list n time.
(Worse case O(n^2)). After you clear the list, second time you visit the same value
you will only need to consider the option +1 and -1.



I actually understand the solution my comment is an attempt to explain the solution to ajray27,
and while you are correct that the bfs will have only one solution, (it can have whatever number of paths bfs will give
output as the shortest path always), the reason we need to clear the unordered_map or hashmap is that
we save many compares by deleting it after going through it for e.g take the case of 5, 5, 5, 5
our map will have {5: 0, 1, 2, 3} on first iteration bfs will put 1, 2, 3 in the queue (as we start with index 0)
for next loop, it will compare 0, 1, 2, 3 (as adjList is same regardless of the fact we have visited it once),
again even though it won't insert those values this time (as they are visited) and basically in an edge case
with 20-30,000 same elements it ends up doing O(n^2) compares in this manner
(does the traversal of an adjList of size n, n times) if not cleared and that's why we need to clear,
it won't put an element once in the queue again in the queue (or re run bfs from same node twice to say in other words).
Compare although constant time operation in large number does slow down performance significantly,
enough in this case to TLE even though the solution is indeed linear (in terms of queue, but n^2 in terms of compares).


ref: https://leetcode.com/problems/jump-game-iv/discuss/502699/JavaC%2B%2B-BFS-Solution-Clean-code-O(N)
*/






// *********** by building actual graph (TLE) ***********
class Solution {
public:
	int minJumps(vector<int>& arr) {
		if (arr.size() == 1) return 0;

		vector<vector<int>> g(arr.size(), vector<int>());
		unordered_map<int, vector<int>> map;
		// store frequencies
		for (int i=0; i<arr.size(); i++) {
			map[arr[i]].push_back(i);
		}
		// build graph
		for (int i=0; i<arr.size(); i++) {
			if (i>0) g[i].push_back(i-1);
			if (i+1<arr.size()) g[i].push_back(i+1);
			vector<int>& indices = map[arr[i]];
			for (int ind: indices) {
				if (ind!=i && ind!=i-1 && ind!=i+1)
					g[i].push_back(ind);
			}
		}

		// perform dfs and find steps to reach end
		int steps = 0, target = arr.size()-1;
		queue<int> q;
		vector<bool> vis(arr.size(), false);
		q.push(0);
		while (!q.empty()) {
			int size = q.size();
			while (size--) {
				int curr = q.front(); q.pop();
				vis[curr] = true;
				if (curr == target) return steps;
				for (int v:g[curr])
					if (!vis[v]) q.push(v);
			}
			steps++;
		}

		return steps;
	}
};