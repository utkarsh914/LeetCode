// https://leetcode.com/problems/find-duplicate-file-in-system/

class Solution {
public:
	vector<vector<string>> findDuplicate(vector<string>& paths) {
		unordered_map<string, vector<string>> map;

		for (auto& path : paths) {
			stringstream ss(path); string file, base_path;
			ss >> base_path;
			while (ss >> file) {
				string name = s.substr(0, s.find('('));
		    string content = s.substr(s.find('(') + 1, s.find(')') - s.find('(') - 1);
				// store in map [content -> base_path + name]
				map[content].push_back(base_path + "/" + name);
			}
		}

		vector<vector<string>> ans;
		for (auto& p : map) {
			if (p.second.size() > 1)
				ans.emplace_back(p.second);
		}

		return ans;
	}
};