
// https://leetcode.com/problems/next-greater-element-i/

/*
You are given two integer arrays nums1 and nums2 both of unique elements, where nums1 is a subset of nums2.
Find all the next greater numbers for nums1's elements in the corresponding places of nums2.
The Next Greater Number of a number x in nums1 is the first greater number to its right in nums2. If it does not exist, return -1 for this number.

Example 1:

Input: nums1 = [4,1,2], nums2 = [1,3,4,2]
Output: [-1,3,-1]
Explanation:
For number 4 in the first array, you cannot find the next greater number for it in the second array, so output -1.
For number 1 in the first array, the next greater number for it in the second array is 3.
For number 2 in the first array, there is no next greater number for it in the second array, so output -1.
*/

class Solution {
public:
	vector<int> nextGreaterElement(vector<int>& nums1, vector<int>& n2) {
		vector<int> n1(10001, -1);
		for (int i=0; i<nums1.size(); i++)
			n1[nums1[i]] = i;
		
		vector<int> ans(nums1.size(), -1);
		stack<int> s;
		for (int i=n2.size()-1; i>=0; i--) {
			int n = n2[i];
			while (!s.empty() && s.top()<=n)
				s.pop();
			if (n1[n] != -1) {
				ans[n1[n]] = !s.empty() ? s.top() : -1;
			}
			s.push(n);
		}
		return ans;
	}
};