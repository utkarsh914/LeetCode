/*
https://leetcode.com/problems/sort-characters-by-frequency/
*/

class Solution {
public:
	string frequencySort(string s) {
		vector<pair<int,char>> hash(256, make_pair(0,'a'));
		for (auto i:s) {
			hash[i] = {hash[i].first+1, i};
		}
		sort(hash.begin(), hash.end());
		string ans;
		for (int i=255; i>=0; i--) {
			for (int j=0; j<hash[i].first; j++)
				ans.push_back(hash[i].second);
		}
		return ans;
	}
};