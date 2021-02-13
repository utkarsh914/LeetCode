// https://leetcode.com/problems/minimum-genetic-mutation/

class Solution {
public:
	int minMutation(string start, string end, vector<string>& Bank) {
		unordered_set<string> bank(Bank.begin(), Bank.end());
		if (!bank.count(end))	return -1;

		queue<string> q;
		q.push(start);
		int steps = 0;

		while (!q.empty()) {
			steps++;
			int size = q.size();
			while (size--) {
				string curr = q.front(); q.pop();
				for (string& next: getNextMutations(curr, end, bank)) {
					if (next == end) return steps;
					else q.push(next);
				}
			}
		}

		return -1;
	}

	vector<string> getNextMutations(string& curr, string& end, unordered_set<string>& bank) {
		vector<string> result;
		string set = "ACGT";

		// generate all possible valid strings by changing any one letter
		for (int i=0; i<curr.length(); i++) {
			char c = curr[i];
			for (char gene: set) {
				if (gene == c) continue;
				curr[i] = gene;
				if (bank.count(curr)) {
					result.push_back(curr);
					bank.erase(curr); // avoid taking this string again in future
				}
			}
			curr[i] = c;
		}
		
		return result;
	}
};