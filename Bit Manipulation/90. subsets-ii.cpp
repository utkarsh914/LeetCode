/*
https://leetcode.com/problems/subsets-ii/

Given a collection of integers that might contain duplicates, nums, return all possible subsets (the power set).

Note: The solution set must not contain duplicate subsets.

Example:

Input: [1,2,2]
Output:
[
  [2],
  [1],
  [1,2,2],
  [2,2],
  [1,2],
  []
]

********* SOLUTION *********
We can treat duplicate element as a spacial element. For example, if we have duplicate elements (5, 5),
instead of treating them as two elements that are duplicate, we can treat it as one special element 5,
but this element has more than two choices:
you can either NOT put it into the subset, or put ONE 5 into the subset, or put TWO 5s into the subset.
Therefore, we are given an array (a1, a2, a3, ..., an) with each of them appearing (k1, k2, k3, ..., kn) times,
the number of subset is (k1+1)(k2+1)...(kn+1).

So, start by pushing an empty set.
Then iterate over the given array, and push the current element in all the existing sets in ans matrix,
and push those sets again into the answer matrix.
*/

class Solution {
public:
	vector<vector<int>> subsetsWithDup(vector<int>& A) {
		vector<vector<int>> ans = {{}};
		sort(A.begin(), A.end());
		for (int i=0; i<A.size();) {
			int count = 0;
			while (i+count<A.size() && A[i+count]==A[i]) count++;
			int prevN = ans.size();
			for (int j=0; j<prevN; j++) {
				vector<int> setWithoutCurrent = ans[j];
				for (int k=0; k<count; k++) {
					setWithoutCurrent.push_back(A[i]);
					ans.push_back(setWithoutCurrent);
				}
			}
			i += count;
		}
		return ans;
	}
};

/*
don't have to count the duplicated elements.

vector<vector<int>> subsetsWithDup(vector<int>& nums) {
	sort(nums.begin(), nums.end());
	vector<vector<int>> result = {{}};
	int start;
	for(int i=0; i<nums.size(); i++) {
		if(i==0 || nums[i] != nums[i-1]) start = 0;
		for(int end=result.size(); start<end; start++){
			vector<int> clone = result[start];
			clone.push_back(nums[i]);
			result.push_back(clone);
		}
	}
	return result;
}
	
*/