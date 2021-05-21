// https://leetcode.com/problems/find-and-replace-in-string/

class Solution {
public:
	string findReplaceString(string& s, vector<int>& indexes,
		vector<string>& sources, vector<string>& targets) {

		// filter out invalid replacements first
		vector<bool> isValid(indexes.size());
		for (int i = 0; i < indexes.size(); i++) {
			isValid[i] = std::equal(sources[i].begin(),
				sources[i].end(), s.begin()+indexes[i]);
		}

		// build a vector containing { index, source, target}
		// v contains only valid replacements
		vector<vector<string>> v;
		for (int i = 0; i < indexes.size(); i++) {
			if (isValid[i])
				v.push_back({ to_string(indexes[i]), sources[i], targets[i] });
		}
		// sort v by index
		sort(v.begin(), v.end(), [](auto& a, auto& b) {
			return stoi(a[0]) < stoi(b[0]);
		});

		string ans;
		for (int i = 0, j = 0; i < s.size(); ) {
			// if replacement needed at this pos (i)
			if (j < v.size() and i == stoi(v[j][0])) {
				ans += v[j][2]; // target
				i += v[j][1].size(); // source
				j++;
			}
			else {
				ans += s[i];
				i++;
			}
		}

		return ans;
	}
};






/*
Intuition:
Verify equality of string and change it if necessay.
The only thing we need take attention is that the string form sources and targets can be different.
Instead of record the length changement, I sort indexes and do it from right to left.
(Since indexes.length <= 100 is really small)
In this way, the different length won't bother us anymore.


Explanation:

1. Descending indexes[] with tracking its index.
2. Verify equality of subring in S source and source.
3. Replace S if necessay.

Time Complexity:
O(SN)
*/

class Solution {
public:
	string findReplaceString(string S, vector<int>& indexes,
		vector<string>& sources, vector<string>& targets) {

		vector<pair<int,int>> sorted;
		for (int i = 0 ; i < indexes.size(); i++)
			sorted.push_back({indexes[i], i});
		sort(sorted.rbegin(), sorted.rend());

		for (auto& ind : sorted) {
			int i = ind.first, j = ind.second;
			string& source = sources[j], &target = targets[j];
			if (S.substr(i, source.length()) == source)
				S = S.substr(0, i) + target + S.substr(i + source.length());
		}
		return S;
	}
};