// https://leetcode.com/problems/letter-tile-possibilities/


/*
I generate all the possible sequences of length 'size'.
do this for every possible value of 'size' (i.e. [1, tiles.size()])
and sum up the answers.
*/
class Solution {
	unordered_set<string> set;
	string cur;
public:
	int numTilePossibilities(string& tiles) {
		long ans = 0;
		for (int size = 1; size <= tiles.size(); size++) {
			set.clear();
			cur = "";
			getWays(tiles, size, 0);
			ans += set.size();
		}
		return ans;
	}
	
	void getWays(string& s, int size, int mask) {
		if (size == 0) {
			set.insert(cur);
			return;
		}
		
		for (int i = 0; i < s.size(); i++) {
			if (mask & (1 << i)) continue;
			cur += s[i];
			getWays(s, size-1, mask | (1 << i));
			cur.pop_back();
		}
	}
};