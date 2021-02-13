// https://leetcode.com/problems/jump-game-iii/

class Solution {
public:
	bool canReach(vector<int>& arr, int start) {
		queue<int> q;
		unordered_set<int> visited;
		q.push(start);
		while (!q.empty()) {
			int curr = q.front(); q.pop();
			if (arr[curr] == 0) return true;
			if (visited.count(curr)) continue;
			visited.insert(curr);
			if (curr-arr[curr] >= 0) q.push(curr-arr[curr]);
			if (curr+arr[curr] < arr.size()) q.push(curr+arr[curr]);
		}
		return false;
	}
};