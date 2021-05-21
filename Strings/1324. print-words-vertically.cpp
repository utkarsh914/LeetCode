// https://leetcode.com/problems/print-words-vertically/

class Solution {
public:
	vector<string> printVertically(string& s) {
		vector<string> words;
		stringstream ss(s);
		string w;
		int maxSize = 0;

		while (ss >> w) {
			words.push_back(w);
			if (w.size() > maxSize)
				maxSize = w.size();
		}

		vector<string> ans(maxSize, string(words.size(), ' '));
		for (int i = 0; i < words.size(); i++) {
			for (int j = 0; j < words[i].size(); j++)
				ans[j][i] = words[i][j];
		}

		for (auto& w : ans) {
			while (w.size() and w.back() == ' ')
				w.pop_back();
		}

		return ans;
	}
};