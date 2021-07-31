// https://leetcode.com/problems/count-pairs-of-nodes/

class Solution {
public:
	vector<int> countPairs(int N, vector<vector<int>>& edges, vector<int>& queries) {
		vector<int> deg(N+1);
		for (auto& e : edges) {
			deg[e[0]]++, deg[e[1]]++;
		}
		
	}
};