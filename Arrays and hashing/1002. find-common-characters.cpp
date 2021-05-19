// https://leetcode.com/problems/find-common-characters/

class Solution {
public:
	vector<string> commonChars(vector<string>& words) {
		vector<int> ans(128);
		for (auto& c : words[0]) ans[c]++;

		for (auto& w : words) {
			vector<int> temp(128);
			for (auto& c : w) ans[c]++;
			for (int i = 0; i < temp.size(); i++)
				ans[i] = min(ans[i], temp[i]);
		}

		vector<string> result;
		for (int i = 0; i < ans.size(); i++) {
			for (int j = 0; j < ans[i]; j++)
				result.push_back(string(char(i), 1));
		}
		return result;
	}
};