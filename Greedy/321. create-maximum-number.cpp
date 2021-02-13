// https://leetcode.com/problems/create-maximum-number/

// ref: https://web.archive.org/web/20160120093629/http://algobox.org/create-maximum-number/

/*
Many of the posts have the same algorithm. In short we can first solve 2 simpler problem

Create the maximum number of one array
Create the maximum number of two array using all of their digits.
For an long and detailed explanation see my blog here.

The algorithm is O((m+n)^3) in the worst case. It runs in 22 ms.
*/

class Solution {
	// create max number of length k from num (k <= nums.size);
	vector<int> maxArray(vector<int>& nums, int k) {
		if (k == nums.size()) return nums;
		int canDelete = nums.size()-k;
		vector<int> stk;
		for (int n:nums) {
			while (!stk.empty() && n>stk.back() && canDelete>0) {
				canDelete--;
				stk.pop_back();
			}
			stk.push_back(n);
		}
		return vector<int> (stk.begin(), stk.begin()+k);
	}

	// create largest number of length l1+l2 from both arrays
	vector<int> merge(vector<int>& nums1, vector<int>& nums2) {
		int s1=nums1.size(), s2=nums2.size();
		vector<int> ans(s1+s2);
		for (int i=0,j=0,k=0; k<s1+s2; k++)
			ans[k] = greater(nums1, i, nums2, j) ? nums1[i++] : nums2[j++];
		return ans;
	}

	// if true, take from nums1 else from nums2
	// (returns true if nums1 is lexicographically greater)
	bool greater(vector<int>& nums1, int i, vector<int>& nums2, int j) {
		int s1=nums1.size(), s2=nums2.size();
		while (i<s1 && j<s2 && nums1[i]==nums2[j])
			i++, j++;
		if (j == s2) return true;
		return i<s1 && nums1[i]>nums2[j];
	}

public:
	vector<int> maxNumber(vector<int>& nums1, vector<int>& nums2, int k) {
		int s1=nums1.size(), s2=nums2.size();
		vector<int> ans;
		for (int i=0; i<=k; i++) {
			int len1 = i, len2 = k-i;
			if (len1>s1 or len2>s2) continue;
			vector<int> firstNum  = maxArray(nums1, len1);
			vector<int> secondNum = maxArray(nums2, len2);
			vector<int> candidate = merge(firstNum, secondNum);
			if (greater(candidate, 0, ans, 0))
				ans = candidate;
		}
		return ans;
	}
};