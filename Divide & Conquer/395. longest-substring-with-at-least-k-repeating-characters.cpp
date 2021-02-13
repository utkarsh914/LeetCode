
// https://leetcode.com/problems/longest-substring-with-at-least-k-repeating-characters/

// *************** USING DIVIDE AND CONQUER (cleaner but slow) *****************
class Solution {
public:
int longestSubstring(string s, int k) {
	if (s.length()==0) return 0;
	vector<int> count(26,0);
	for (char c:s) count[c-'a']++;
	for (int i=0; i<s.length(); i++) {
		if (count[s[i]-'a'] >= k) continue;
		int left = longestSubstring(s.substr(0,i), k);
		int right = longestSubstring(s.substr(i+1), k);
		return max(left, right);
	}
	return s.length();
}};



// *************** USING TWO POINTER *****************
class Solution {
public:
int longestSubstring(string s, int k) {
	int maxL=0;
	for (int h=1; h<=26; h++) {
		vector<int> count(26,0);
		int i=0, j=0, unique=0, greaterThanK=0;
		while (j < s.length()) {
			if (unique <= h) {
				int idx = s[j]-'a';
				if (count[idx] == 0) unique++;
				if (++count[idx] == k) greaterThanK++;
				j++;
			}	else {
				int idx = s[i]-'a';
				if (count[idx] == k) greaterThanK--;
				if (--count[idx] == 0) unique--;
				i++;
			}
			if (unique == h and unique == greaterThanK)
				maxL = max(maxL, j-i);
		}
	}
	return maxL;
}};