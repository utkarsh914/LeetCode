
// https://leetcode.com/problems/restore-ip-addresses/

/*
Given a string s containing only digits, return all possible valid IP addresses that can be obtained from s.
You can return them in any order.
A valid IP address consists of exactly four integers, each integer is between 0 and 255,
separated by single dots and cannot have leading zeros.
For example, "0.1.2.201" and "192.168.1.1" are valid IP addresses and
"0.011.255.245", "192.168.1.312" and "192.168@1.1" are invalid IP addresses. 

Example 1:

Input: s = "25525511135"
Output: ["255.255.11.135","255.255.111.35"]
Example 2:

Input: s = "0000"
Output: ["0.0.0.0"]
Example 3:

Input: s = "1111"
Output: ["1.1.1.1"]
Example 4:

Input: s = "010010"
Output: ["0.10.0.10","0.100.1.0"]
Example 5:

Input: s = "101023"
Output: ["1.0.10.23","1.0.102.3","10.1.0.23","10.10.2.3","101.0.2.3"]

Constraints:
0 <= s.length <= 3000
s consists of digits only.
*/

// *********** backtracking **************
class Solution {
	
	vector<string> ans;
	vector<string> curr;
	
	void split(string& s, int start, int part) {
		
		if (start == s.length()) {
			if (part==0) {
				string temp;
				for (auto& c:curr) temp += c + ".";
				temp.pop_back(); // remove last '.'
				ans.push_back(temp);
				return;
			}
			else return;
		}
		
		if (s[start] == '0') { // if curr char is 0, then it can't include any other numbers after it
			curr.push_back("0");
			split(s,start+1,part-1);
			curr.pop_back();
			return;
		}
		
		string temp;
		for (int i=start; i<s.length() && i<=start+2; i++) {
			temp.push_back(s[i]);
			if (stoi(temp) > 255)
				continue;
			curr.push_back(temp);
			split(s, i+1, part-1);
			curr.pop_back();
		}

	}
	
public:
	vector<string> restoreIpAddresses(string& s) {
		if (s.length() > 12) return ans;
		split(s,0,4);
		return ans;
	}
};








// *********** alternative **************

class Solution {
public:
	vector<string> restoreIpAddresses(string s) {
		vector<string> ret;
		string ans;
		
		for (int a=1; a<=3; a++)
		for (int b=1; b<=3; b++)
		for (int c=1; c<=3; c++)
		for (int d=1; d<=3; d++)
			if (a+b+c+d == s.length()) {
				int A = stoi(s.substr(0, a));
				int B = stoi(s.substr(a, b));
				int C = stoi(s.substr(a+b, c));
				int D = stoi(s.substr(a+b+c, d));
				if (A<=255 && B<=255 && C<=255 && D<=255)
					if ( (ans=to_string(A)+"."+to_string(B)+"."+to_string(C)+"."+to_string(D)).length() == s.length()+3)
						ret.push_back(ans);
			}	
		
		return ret;
	}