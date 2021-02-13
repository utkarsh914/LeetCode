// https://leetcode.com/problems/decode-string/

/*
Example 1:

Input: s = "3[a]2[bc]"
Output: "aaabcbc"
Example 2:

Input: s = "3[a2[c]]"
Output: "accaccacc"
Example 3:

Input: s = "2[abc]3[cd]ef"
Output: "abcabccdcdcdef"
*/

class Solution {
public:
	string decode(string& s, int& i) {
		string ans;
		while (i<s.length() and s[i]!=']') {
			if (!isdigit(s[i])) {
				ans.push_back(s[i++]);
				continue;
			}
			int n=0;
			while (i<s.length() && isdigit(s[i]))
				n = n*10 + s[i++] - '0';
			i++; // for '['
			string subdecoded = decode(s, i);
			i++; // for ']'
			while (n--)
				ans += subdecoded;
		}
		return ans;
	}

	string decodeString(string s) {
		int i=0;
		return decode(s, i);
	}
};


/*
***************** LESS CLEANER ****************

class Solution {
public:
	string decodeString(string s) {

		if (s.length()==0 or s.length()==1)
			return s;

		stack<int> stk;
		string mul, sub, ans, decoded_sub;
		int check = s.length()-1;

		for (int i=0; i<s.length(); i++) {
			char c = s[i];
			if (c=='[')
				stk.push(i);
			else if (c==']') {
				sub = s.substr(stk.top()+1, i-stk.top()-1);
				stk.pop();
				if (stk.empty()) {check=i; break;}
			}
			else if (c-'0'>=0 and c-'0'<10 && stk.empty())
				mul.push_back(c);
			else if (c>='a' and c<='z' && stk.empty())
				ans.push_back(c);
		}

		decoded_sub = decodeString(sub);

		int timesRepeat = (mul.length()>0) ? stoi(mul) : 1;
		for (int i=0; i<timesRepeat; i++)
			ans += decoded_sub;
		if (check+1<s.length())
	  	ans += decodeString(s.substr(check+1, s.length()-check));
	
		return ans;
	}
};

*/