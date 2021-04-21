// https://leetcode.com/problems/swap-for-longest-repeated-character-substring/

/*
Given a string text, we are allowed to swap two of the characters in the string.
Find the length of the longest substring with repeated characters.

Example 1:

Input: text = "ababa"
Output: 3
Explanation: We can swap the first 'b' with the last 'a', or the last 'b' with the first 'a'.
Then, the longest repeated character substring is "aaa", which its length is 3.
*/



/*
There are only 2 cases that we need to take care of:

extend the group by 1
merge 2 adjacent groups together, which are separated by only 1 character

Explanation
For S = "AAABBCB"
[[c, len(list(g))] for c, g in groupby(S)] --> [[A,3],[B,2],[C,1],[B,1]]
collections.Counter(S) --> {A:3, B:3, C:1}
With these two data, calculate the best solution for the two cases above.
*/

class Solution {
public:
	int maxRepOpt1(string& s) {
		vector<array<int,2>> v = groupString(s);
		unordered_map<char, int> f;
		for (char& c : s) f[c]++;
		int ans = 1;
		// check for extending group by 1
		for (auto& g : v) {
			int len = min(g[1]+1, f[g[0]]);
			ans = max(ans, len);
		}
		// merge 2 adjacent groups
		for (int i = 1; i+1 < v.size(); i++) {
			auto &prev = v[i-1], &cur = v[i], &next = v[i+1];
			if (cur[1]==1 && prev[0]==next[0]) {
				int len = min(prev[1] + 1 + next[1], f[prev[0]]);
				ans = max(ans, len);
			}
		}

		return ans;
	}

	vector<array<int,2>> groupString(string& s) {
		vector<array<int,2>> ans;
		char c = s[0], size = 1;
		for (int i = 1; i < s.length(); i++) {
			if (s[i] == c) size++;
			else {
				ans.push_back({c, size});
				c = s[i], size = 1;
			}
		}
		ans.push_back({c, size});
		return ans;
	}
};