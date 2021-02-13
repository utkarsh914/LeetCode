// https://leetcode.com/problems/number-of-atoms/
/*
Example 1:

Input: formula = "H2O"
Output: "H2O"
Explanation: The count of elements are {'H': 2, 'O': 1}.
Example 2:

Input: formula = "Mg(OH)2"
Output: "H2MgO2"
Explanation: The count of elements are {'H': 2, 'Mg': 1, 'O': 2}.
Example 3:

Input: formula = "K4(ON(SO3)2)2"
Output: "K4N2O14S4"
Explanation: The count of elements are {'K': 4, 'N': 2, 'O': 14, 'S': 4}.
Example 4:

Input: formula = "Be32"
Output: "Be32"
*/

class Solution {
public:
	string countOfAtoms(string formula);
	map<string, int> count(string& s, int& i);
};

map<string, int> Solution::count(string& s, int& i) {
	map<string, int> subcounts;
	while (i<s.length() and s[i]!=')') {
		if (s[i]=='(') {
			i++; // for '('
			map<string, int> temp = count(s, i);
			i++; // for ')'
			int n = 0;
			while (i<s.length() && isdigit(s[i]))
				n = n*10 + s[i++] -'0';
			if (n==0) n=1;
			// fill counts in map
			for (auto k: temp)
				subcounts[k.first] += k.second*n;
		}
		else if (s[i]>='A' && s[i]<='Z') {
			string element;
			element.push_back(s[i++]);
			while (i<s.length() && s[i]>='a' && s[i]<='z')
				element.push_back(s[i++]);
			int n = 0;
			while (i<s.length() && isdigit(s[i]))
				n = n*10 + s[i++] -'0';
			if (n==0) n=1;
			subcounts[element] += n;
		}
	}
	return subcounts;
}

string Solution::countOfAtoms(string formula) {
	int index = 0;
	map<string, int> mp = count(formula, index);
	string ans;
	for (auto i=mp.begin(); i!=mp.end(); i++) {
		ans += i->first;
		if (i->second > 1) ans += to_string(i->second);
	}
	return ans;
}