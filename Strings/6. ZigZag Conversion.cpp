// https://leetcode.com/problems/zigzag-conversion/

/*
The string "PAYPALISHIRING" is written in a zigzag pattern on a given number of rows like this: (you may want to display this pattern in a fixed font for better legibility)

P   A   H   N
A P L S I I G
Y   I   R
And then read line by line: "PAHNAPLSIIGYIR"

Write the code that will take a string and make this conversion given a number of rows:

string convert(string s, int numRows);
 

Example 1:

Input: s = "PAYPALISHIRING", numRows = 3
Output: "PAHNAPLSIIGYIR"
*/


class Solution {
public:
	string convert(string& s, int rows) {
		if (rows==1) return s;
		int l = s.length();
		string ans; ans.reserve(l);
		int goback = 0, skip = 2*(rows-1);
		for (int r=0; r<rows; r++, goback+=2) {
			for (int i=r; ; i+=skip) {
				if (r!=0 && r!=rows-1 && i-goback>=0 && i-goback<l)
					ans.push_back(s[i-goback]);
				if (i<l) ans.push_back(s[i]);
				else break;
			}
		}
		return ans;
	}
};






class Solution {
public:
	string convert(string s, int numRows) {

		if (numRows == 1) return s;

		vector<string> rows(min(numRows, int(s.size())));
		int curRow = 0;
		bool goingDown = false;

		for (char c : s) {
			rows[curRow] += c;
			if (curRow == 0 || curRow == numRows - 1) goingDown = !goingDown;
			curRow += goingDown ? 1 : -1;
		}

		string ret;
		for (string row : rows) ret += row;
		return ret;
	}
};