// https://leetcode.com/problems/number-of-longest-increasing-subsequence/

/*
Given an integer array nums, return the number of longest increasing subsequences.
Notice that the sequence has to be strictly increasing.

Example 1:

Input: nums = [1,3,5,4,7]
Output: 2
Explanation: The two longest increasing subsequences are [1, 3, 4, 7] and [1, 3, 5, 7].
*/


class Solution {
public:
	int findNumberOfLIS(vector<int>& nums) {

		// freq[k] is total number of longest subsequence ending with nums[k];
		// len[k] is the length of longest subsequence ending with nums[k];

		vector<int> len (nums.size(), 1);
		vector<int> freq(nums.size(), 1);
		int maxLen=0, ans=0;

		for (int i=0; i<nums.size(); i++) {
			for (int j=0; j<i; j++) {
				if (nums[i] > nums[j]) {
					if (1+len[j] > len[i])
						len[i] = 1+len[j], freq[i] = freq[j];
					else if (1+len[j] == len[i])
						freq[i] += freq[j];
				}
			}
			// count total freq of current max length subsequence
			if (len[i] == maxLen)
				ans += freq[i];
			else if (len[i] > maxLen)
				maxLen = len[i], ans = freq[i];
		}

		return ans;
	}
};






// ******** using binary search ********* 
// ref: https://leetcode.com/problems/number-of-longest-increasing-subsequence/discuss/107295/9ms-C%2B%2B-Explanation%3A-DP-%2B-Binary-search-%2B-prefix-sums-O(NlogN)-time-O(N)-space
class Solution {
public:
	int findNumberOfLIS(vector<int>& nums) {
		if (nums.empty())
			return 0;
		
		vector<vector<pair<int, int>>> dyn(nums.size() + 1);
		int max_so_far = 0;

		for (int i = 0; i < nums.size(); ++i) {
			// bsearch insertion point
			int l = 0, r = max_so_far;
			while (l < r) {
				int mid = l + (r - l) / 2;
				if (dyn[mid].back().first < nums[i]) {
					l = mid + 1;
				} else {
					r = mid;
				}
			}
			
			// bsearch number of options
			int options = 1;
			int row = l - 1;
			if (row >= 0) {
				int l1 = 0, r1 = dyn[row].size();
				while (l1 < r1) {
					int mid = l1 + (r1 - l1) / 2;
					if (dyn[row][mid].first < nums[i]) {
						r1 = mid;
					} else {
						l1 = mid + 1;
					}
				}
				
				options = dyn[row].back().second;
				options -= (l1 == 0) ? 0 : dyn[row][l1 - 1].second;
			}
			
			
			dyn[l].push_back({nums[i], (dyn[l].empty() ? options : dyn[l].back().second + options)});
			if (l == max_so_far) {
				max_so_far++;
			}
		}
		
		return dyn[max_so_far-1].back().second;
		
	}
};



// ************** wrong ans ****************
class Solution {
public:
	int findNumberOfLIS(vector<int>& nums) {
		int size = nums.size();
		if (size == 1) return 1;
		vector<int> freq(size+1, 0); // subseq_length -> freq
		freq[0]=1;
		vector<int> res;
		for (int n: nums) {
			auto itr = lower_bound(res.begin(), res.end(), n);
			if (itr == res.end()) {
				res.push_back(n);
				freq[res.size()] += freq[res.size()-1];
			} else if (*itr == n) {
				freq[itr-res.begin()+1] += freq[itr-res.begin()];
			} else {
				*itr = n;
				freq[itr-res.begin()+1]++;
			}
		}
		return freq[res.size()];
	}
};