// https://leetcode.com/problems/remove-sub-folders-from-the-filesystem/

class Solution {
public:
	vector<string> removeSubfolders(vector<string>& folders) {
		sort(folders.begin(), folders.end(), [](auto& w1, auto& w2) {
			return w1.length() < w2.length();
		});

		unordered_set<string> s;

		for (auto& folder : folders) {
			string temp; temp.reserve(folder.size());
			bool present = false;
			for (auto& c : folder) {
				if (c == '/' and s.count(temp)) {
					present = true; break;
				}
				temp.push_back(c);
			}
			if (!present)
				s.insert(temp);
		}

		return vector<string> (s.begin(), s.end());
	}
};





class Solution {
public:
	vector<string> removeSubfolders(vector<string>& folders) {
		sort(folders.begin(), folders.end());

		vector<string> ans {folders[0]};

		for (int i = 1; i < folders.size(); i++) {
			string& last = ans.back();
			if (folders[i].find(last + "/") == string::npos)
				ans.push_back(folders[i]);
		}

		return ans;
	}
};