/*
https://leetcode.com/problems/letter-combinations-of-a-phone-number/
*/

class Solution {
public:
	vector<string> letterCombinations(string digits) {
		unordered_map<char, string> m;
		m['2']="abc";
		m['3']="def";
		m['4']="ghi";
		m['5']="jkl";
		m['6']="mno";
		m['7']="pqrs";
		m['8']="tuv";
		m['9']="wxyz";
		
		vector<string> result;
		if(digits.empty()) return result;
		
		result.push_back("");
		
		for (int i=0; i<digits.size(); i++) {
			const string& candidate = m[digits[i]];
			vector<string> temp;
			for (int j=0; j<candidate.size(); j++) {
				for (int k=0; k<result.size(); k++) {
					temp.push_back(result[k]+candidate[j]);
				}
			}
			result.swap(temp);
		}
		
		return result;
	}
};