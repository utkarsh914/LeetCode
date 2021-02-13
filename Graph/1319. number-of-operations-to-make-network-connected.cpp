/*
https://leetcode.com/problems/number-of-operations-to-make-network-connected/

There are n computers numbered from 0 to n-1 connected by ethernet cables connections forming a network
where connections[i] = [a, b] represents a connection between computers a and b.
Any computer can reach any other computer directly or indirectly through the network.
Given an initial computer network connections.
You can extract certain cables between two directly connected computers,
and place them between any pair of disconnected computers to make them directly connected.
Return the minimum number of times you need to do this in order to make all the computers connected.
If it's not possible, return -1. 

Example 1:
Input: n = 4, connections = [[0,1],[0,2],[1,2]]
Output: 1
Explanation: Remove cable between computer 1 and 2 and place between computers 1 and 3.
Example 2:



Input: n = 6, connections = [[0,1],[0,2],[0,3],[1,2],[1,3]]
Output: 2
Example 3:

Input: n = 6, connections = [[0,1],[0,2],[0,3],[1,2]]
Output: -1
Explanation: There are not enough cables.
*/


// return no. of connected groups-1;
// or no. of islands - 1;
class Solution {
public:

vector<int> parent;

int find(int x) {
	if (parent[x] != x)
		parent[x] = find(parent[x]);
	return parent[x];
}

void uni(int x, int y) {
	x = find(x);
	y = find(y);
	if (x != y) {
		parent[y] = x;
	}
}

int makeConnected(int n, vector<vector<int>>& connections) {
	if (connections.size() < n-1)
		return -1;
	parent = vector<int> (n, 0);
	for (int i = 0; i < parent.size(); i++) parent[i] = i;
	// make unions of all edges
	for (auto& c:connections) {
		uni(c[0], c[1]);
	}
	vector<int> freq(n, 0);
	int groups = 0;
	for (int i=0; i<n; i++) {
		int p = find(i);
		if (freq[p]==0)
			freq[p]++, groups++;
		else
			freq[p]++;
	}
	return groups-1;
}};