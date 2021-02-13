// https://leetcode.com/problems/zigzag-conversion/

class Solution {
public:
	string convert(string& s, int rows) {
		if (rows==1) return s;

		int len = s.length();
		string ans; ans.reserve(len);
		int goBack = 0, skip = 2*(rows-1);

		for (int r=0; r<rows; r++, goBack+=2) {
			for (int i=r; ; i+=skip) {
				if (r!=0 && r!=rows-1 && i-goBack>=rows && i-goBack<len)
					ans.push_back(s[i-goBack]);
				if (i<len) ans.push_back(s[i]);
				else break;
			}
		}

		return ans;
	}
};




// ********** simpler to understand *********
class Solution {
public:
	string convert(string& s, int numRows) {
		if( numRows==1 ) return s;

		vector<string> res(numRows);
		int row=0, int increase=-1;

		for(int i=0; i<s.size(); ++i){
			// every time at turning point, we change the increase direction
			if(i%(numRows-1)==0) increase *= -1;
			res[row].push_back(s[i]);
			row += increase;
		}

		string ret;
		for(auto& str:res) ret += str;
		return ret;
	}
};



// ********* same idea as above ********
class Solution {
public:
	string convert(string s, int numRows) {
		vector<string> vs(numRows, "");
		int n = s.length(), i = 0;

		while (i < n) {
			for (int j = 0; j < numRows && i < n; j++)
				vs[j].push_back(s[i++]);
			for (int j = numRows - 2; j >= 1 && i < n; j--)
				vs[j].push_back(s[i++]);
		}
		
		string zigzag;
		for (string v : vs) zigzag += v;
		return zigzag;
	} 
};