// https://leetcode.com/problems/remove-all-adjacent-duplicates-in-string-ii/

class Solution {
public:
	string removeDuplicates(string S, int k) {
		stack<pair<char,int>> s; // store continuous count of same char

		for (char c:S) {
			int freq = (!s.empty() && s.top().first==c)
					? s.top().second+1 : 1;

			s.push({ c, freq });
			if (freq == k) {
				while (freq-- && !s.empty()) s.pop();
			}
		}

		string ans; ans.reserve(s.size());
		while (!s.empty()) {
			ans.push_back(s.top().first);
			s.pop();
		}
		reverse(ans.begin(), ans.end());
		
		return ans;
	}
};



// ********* two pointers *********
	string removeDuplicates(string s, int k) {
		int i = 0, n = s.length();
		vector<int> count(n);
		for (int j = 0; j < n; ++j, ++i) {
			s[i] = s[j];
			count[i] = i > 0 && s[i - 1] == s[j] ? count[i - 1] + 1 : 1;
			if (count[i] == k) i -= k;
		}
		return s.substr(0, i);
	}