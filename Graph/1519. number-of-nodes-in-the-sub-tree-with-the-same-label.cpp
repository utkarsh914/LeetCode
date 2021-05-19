// https://leetcode.com/problems/number-of-nodes-in-the-sub-tree-with-the-same-label/

class Solution {
	vector<bool> vis;
public:
	vector<int> countSubTrees(int n, vector<vector<int>>& edges, string& labels) {
		// create graph
		vector<vector<int>> G(n);
		for (auto& e : edges) {
			G[e[0]].push_back(e[1]);
			G[e[1]].push_back(e[0]);
		}

		vis.resize(n, false);
		vector<int> result(n);

		dfs(G, labels, result, 0);
		return result;
	}

	unordered_map<char,int> dfs(vector<vector<int>>& G, string& labels,
		vector<int>& result, int u ) {
		// mark visited
		vis[u] = true;

		unordered_map<char,int> map;
		map[labels[u]]++;
		// visit all its children
		for (int& v : G[u]) {
			if (vis[v]) continue;
			unordered_map<char,int> subMap = dfs(G, labels, result, v);
			for (auto& p : subMap) {
				map[p.first] += p.second;
			}
		}
		// set result of curr 'u'
		result[u] = map[labels[u]];
		return map;
	}
};






class Solution {
	vector<bool> vis;
public:
	vector<int> countSubTrees(int n, vector<vector<int>>& edges, string& labels) {
		// create graph
		vector<vector<int>> G(n);
		for (auto& e : edges) {
			G[e[0]].push_back(e[1]);
			G[e[1]].push_back(e[0]);
		}

		vis.resize(n, false);
		vector<int> result(n);

		dfs(G, labels, result, 0);
		return result;
	}

	vector<int> dfs(vector<vector<int>>& G, string& labels,
		vector<int>& result, int u ) {
		// mark visited
		vis[u] = true;

		vector<int> map(26);
		map[labels[u] - 'a']++;
		// visit all its children
		for (int& v : G[u]) {
			if (vis[v]) continue;
			vector<int> subMap = dfs(G, labels, result, v);
			for (int i = 0; i < 26; i++) {
				map[i] += subMap[i];
			}
		}
		// set result of curr 'u'
		result[u] = map[labels[u] - 'a'];
		return map;
	}
};