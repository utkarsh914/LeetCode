// https://leetcode.com/problems/longest-substring-of-all-vowels-in-order/





class Solution {
public:
	int longestBeautifulSubstring(string& w) {
		int ans = 0;
		for (int i = 0, j = 0; i < w.size(); ++i) {
			if (w[i] == 'a') {
				int cnt = 0;
				for (j = i + 1; j < w.size() && w[j-1] <= w[j]; ++j)
					cnt += w[j-1] < w[j];
				if (cnt == 4)
					ans = max(ans, j - i);
				i = j - 1;
			}
		}
		return ans;
	}
};



int longestBeautifulSubstring(string& W) {
	unordered_map<char, int> count;
	unordered_map<char,char> next{
		{'a', 'e'}, {'e', 'i'}, {'i', 'o'}, {'o', 'u'}, {'u', '#'}
	};
	
	int ans = 0;
	char prev = 'u';

	for (int i = 0, j = 0; j < W.size(); j++) {
		char cur = W[j];
		// reset the window
		if (cur != prev and (next[prev] != cur or W[i] != 'a')) {
			i = j;
			count.clear();
		}

		count[cur]++;
		if (count.size() == 5)
			ans = max(ans, j - i + 1);

		// update prev char
		prev = cur;
	}

	return ans;
}