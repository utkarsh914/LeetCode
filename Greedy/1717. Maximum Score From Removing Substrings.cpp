// https://leetcode.com/problems/maximum-score-from-removing-substrings/

/*
You are given a string s and two integers x and y. You can perform two types of operations any number of times.

Remove substring "ab" and gain x points.
For example, when removing "ab" from "cabxbae" it becomes "cxbae".
Remove substring "ba" and gain y points.
For example, when removing "ba" from "cabxbae" it becomes "cabxe".
Return the maximum points you can gain after applying the above operations on s.

 

Example 1:

Input: s = "cdbcbbaaabab", x = 4, y = 5
Output: 19
Explanation:
- Remove the "ba" underlined in "cdbcbbaaabab". Now, s = "cdbcbbaaab" and 5 points are added to the score.
- Remove the "ab" underlined in "cdbcbbaaab". Now, s = "cdbcbbaa" and 4 points are added to the score.
- Remove the "ba" underlined in "cdbcbbaa". Now, s = "cdbcba" and 5 points are added to the score.
- Remove the "ba" underlined in "cdbcba". Now, s = "cdbc" and 5 points are added to the score.
Total score = 5 + 4 + 5 + 5 = 19.
Example 2:

Input: s = "aabbaaxybbaabb", x = 5, y = 4
Output: 20
 

Constraints:

1 <= s.length <= 105
1 <= x, y <= 104
s consists of lowercase English letters.
*/










/*
Solution 1. Greedy
We greedily remove the pattern with greater points, then remove the other pattern.

For removing the pattern string recursively, we can reuse the solution to 1003. Check If Word Is Valid After Substitutions (Medium)

// OJ: https://leetcode.com/problems/maximum-score-from-removing-substrings/
// Author: github.com/lzl124631x
// Time: O(N)
// Space: O(1)
*/
class Solution {
	int remove(string &s, string r, int x) {
		int i = 0, ans = 0; // `i` is write pointer, `j` is read pointer. 
		for (int j = 0; j < s.size(); ++j) {
			s[i++] = s[j];
			// We keep removing pattern string `r` when `r` shows up in the end of written part.
			if (i > 1 && s[i-2] == r[0] && s[i-1] == r[1])
				i -= 2, ans += x;
		}
		s.resize(i);
		return ans;
	}

public:
	int maximumGain(string s, int x, int y) {
		string a = "ab", b = "ba";
		if (x < y) swap(a, b), swap(x, y);
		return remove(s, a, x) + remove(s, b, y);
	}
};








/*
First remove the substrings with maximum gains,
and then remove the remaining with minimum gains.
*/
class Solution {
public:
	int maximumGain(string& s, int x, int y) {
		char A = x>y ? 'a' : 'b';
		char B = A=='a' ? 'b' : 'a';
		int maxScore = max(x, y), minScore = min(x, y);

		string stk1, stk2;
		int ab = 0, ba = 0;

		// first remove "ab"
		for (char& c : s) {
			if (!stk1.empty() and stk1.back() == A and c == B)
				stk1.pop_back(), ab++;
			else
				stk1.push_back(c);
		}
		// now remove "ba" (it is similar to removing "ab" on reversed string)
		reverse(stk1.begin(), stk1.end());
		for (char& c : stk1) {
			if (!stk2.empty() and stk2.back() == A and c == B)
				stk2.pop_back(), ba++;
			else
				stk2.push_back(c);
		}

		return maxScore * ab + minScore * ba;
	}
};











class Solution {
public:
	int maximumGain(string& s, int x, int y) {
		int AB = remove(s, x, y);
		reverse(s.begin(), s.end());
		int BA = remove(s, y, x);
		return max(AB, BA);
	}

	int remove(string& s, int x, int y) {
		// first remove "ab"
		string stk1, stk2;
		int ab = 0, ba = 0;
		for (char& c : s) {
			if (!stk1.empty() and stk1.back() == 'a' and c == 'b')
				stk1.pop_back(), ab++;
			else
				stk1.push_back(c);
		}
		// now remove "ba"
		reverse(stk1.begin(), stk1.end());
		for (char& c : stk1) {
			if (!stk2.empty() and stk2.back() == 'a' and c == 'b')
				stk2.pop_back(), ba++;
			else
				stk2.push_back(c);
		}

		return x*ab + y*ba;
	}
};











// https://leetcode.com/problems/maximum-score-from-removing-substrings/

class Solution {
public:
	int maximumGain(string& s, int x, int y) {
		vector<string> v;
		string temp;
		for (int i = 0; i < s.size(); i++) {
			if (s[i] == 'a' or s[i] == 'b')
				temp += s[i];
			else if (temp.size() != 0)
				v.push_back(temp), temp = "";
		}
		if (temp.size() != 0)
			v.push_back(temp);

		int ans = 0;
		for (auto& str : v) ans += solve(str, x, y);
		return ans;
	}

	int solve(string& s, int x, int y) {
		int removeAB = remove(s, x, y);
		reverse(s.begin(), s.end());
		int removeBA = remove(s, y, x);
		return max(removeAB, removeBA);
	}

	int remove(string& s, int x, int y) {
		// first remove "ab"
		string stk;
		int ab = 0, ba = 0;
		for (char& c : s) {
			if (c == 'a')
				stk.push_back(c);
			else if (stk.empty() or stk.back() == 'b')
				stk.push_back(c);
			else
				stk.pop_back(), ab++;
		}

		string stk2;
		reverse(stk.begin(), stk.end());
		for (char& c : stk) {
			if (c == 'a')
				stk2.push_back(c);
			else if (stk2.empty() or stk2.back() == 'b')
				stk2.push_back(c);
			else
				stk2.pop_back(), ba++;
		}

		return x*ab + y*ba;
	}
};

/*
bbaa abab
*/