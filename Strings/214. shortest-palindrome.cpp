/*
https://leetcode.com/problems/shortest-palindrome/

Given a string s, you can convert it to a palindrome by adding characters in front of it. Find and return the shortest palindrome you can find by performing this transformation.

Example 1:

Input: s = "aacecaaa"
Output: "aaacecaaa"
Example 2:

Input: s = "abcd"
Output: "dcbabcd"
*/

class Solution {
public:
	string shortestPalindrome(string s) {
		string temp = s + "#" + string(s.rbegin(),s.rend());
		// build kmp table on temp;
		vector<int> kmp(temp.length(), 0);
		int i=0, j=1;
		while (j<temp.length()) {
			if (temp[i]==temp[j]) kmp[j]=i+1, i++, j++;
			else if (i > 0) i=kmp[i-1];
			else i=0, j++;
		}
		// for (auto i: kmp) cout << i << " ";
		return string(s.rbegin(), s.rbegin()+s.length()-kmp.back()) + s;
	}
};

static auto _______ = [](){
	std::ios::sync_with_stdio(false);
	std::cin.tie(NULL);
	std::cout.tie(NULL);
	return 0;
}();