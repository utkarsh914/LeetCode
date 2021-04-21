// https://leetcode.com/problems/expressive-words/

class Solution {
public:
	int expressiveWords(string& s, vector<string>& words) {
		vector<array<int,2>> main_group = getGroups(s);
		int ans = 0;

		for (auto& word : words) {
			auto cur_group = getGroups(word);
			if (compare_groups(main_group, cur_group))
				ans++;
		}

		return ans;
	}

	bool compare_groups(vector<array<int,2>>& main_group,
		vector<array<int,2>>& cur_group) {
		if (main_group.size() != cur_group.size())
			return false;
		for (int i=0; i < main_group.size(); i++) {
			auto& mg = main_group[i], &cg = cur_group[i];
			// different character
			if (mg[0] != cg[0]) return false;
			// if it is not possible to stretch current group to length of main grp
			if (mg[1] < cg[1] or (mg[1] > cg[1] && mg[1] < 3)) return false;
		}
		return true;
	}

	vector<array<int,2>> getGroups(string& s) {
		vector<array<int,2>> groups;
		if (s.empty()) return groups;

		array<int,2> group = {s[0],1};
		for (int i=1; i < s.length(); i++) {
			if (s[i] == s[i-1]) group[1]++;
			else {
				groups.push_back(group);
				group = {s[i], 1};
			}
		}
		groups.push_back(group);

		return groups;
	}
};