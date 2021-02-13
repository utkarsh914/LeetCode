// https://leetcode.com/problems/132-pattern/

class Solution {
public:
	bool find132pattern(vector<int>& n) {
		vector<int> s;
		int prev = INT_MIN;

		for (int i=n.size()-1; i>=0; i--) {
			if (n[i] < prev) {
				return true;
			}
			while (!s.empty() && s.back()<n[i]) {
				prev = s.back();
				s.pop_back();
			}
			s.push_back(n[i]);
		}
		
		return false;
	}
};