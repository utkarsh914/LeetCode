
// https://leetcode.com/problems/next-greater-element-ii/

class Solution {
public:
	vector<int> nextGreaterElements(vector<int>& nums) {
		stack<int> s;
		vector<int> ans(nums.size(), -1);
		for (int i=nums.size()-1; i>=0; i--) {
			int n = nums[i];
			while (!s.empty() && s.top()<=n)
				s.pop();
			ans[i] = !s.empty() ? s.top() : INT_MAX;
			s.push(n);
		}
		for (int i=nums.size()-1; i>=0; i--) {
			if (ans[i] != INT_MAX)
				continue;
			int n = nums[i];
			while (!s.empty() && s.top()<=n)
				s.pop();
			ans[i] = !s.empty() ? s.top() : -1;
		}
		return ans;
	}
};