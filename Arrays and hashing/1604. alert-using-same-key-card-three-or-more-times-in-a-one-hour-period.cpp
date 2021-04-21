// https://leetcode.com/problems/alert-using-same-key-card-three-or-more-times-in-a-one-hour-period/

class Solution {
public:
	vector<string> alertNames(vector<string>& keyName, vector<string>& keyTime) {
		int size = keyTime.size();
		vector<pair<int, string>> entries(size);
		for (int i=0; i < size; i++) {
			entries[i] = { duration(keyTime[i]), keyName[i] };
		}
		sort(entries.begin(), entries.end());

		set<string> alerted;
		unordered_map<string, queue<int>> map; // string -> {last 2 times}

		for (auto& e : entries) {
			string& k = e.second;
			int t = e.first;
			if (map[k].size() == 2) {
				if (t - map[k].front() <= 60)
					alerted.insert(k);
				map[k].pop();
			}
			map[k].push(t);
		}

		return vector<string>(alerted.begin(), alerted.end());
	}

	int duration(string& t) {
		return stoi(t.substr(0,2)) * 60 + stoi(t.substr(3));
	}
};







// Collect times for each person, sort them, and then use a sliding window to check for alarms.
class Solution {
public:
	vector<string> alertNames(vector<string>& names, vector<string>& times) {
		unordered_map<string, vector<int>> log;
		vector<string> ans;
		for (int i = 0; i < names.size(); ++i) {
			log[names[i]].push_back(duration(times[i]));
		}

		for (auto &p : log) {
			sort(begin(p.second), end(p.second));
			for (int i = 0, j = 0; i < p.second.size(); ++i) {
				while(p.second[i] - p.second[j] > 60)
					++j;
				if (i - j >= 2) {
					ans.push_back(p.first);
					break;
				}
			}
		}
		sort(begin(ans), end(ans));
		return ans;
	}

	int duration(string& t) {
		return stoi(t.substr(0,2)) * 60 + stoi(t.substr(3));
	}
};