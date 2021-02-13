// https://leetcode.com/problems/find-the-most-competitive-subsequence/

// same as 402. remove-k-digits

class Solution {
public:
	vector<int> mostCompetitive(vector<int>& nums, int k) {
		int canDelete = nums.size()-k;
		vector<int> s;
		for (int n: nums) {
			while (s.size() && n<s.back() && canDelete>0) {
				s.pop_back();
				canDelete--;
			}
			s.push_back(n);
		}
		return vector<int> (s.begin(), s.begin()+k);
	}
};