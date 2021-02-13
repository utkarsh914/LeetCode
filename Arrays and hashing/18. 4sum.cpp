// https://leetcode.com/problems/4sum/



/*
 ------- make a k-sum template -------
used recursion to break k-sum to 2-sum problem
*/

class Solution {
public:
	vector<vector<int>> fourSum(vector<int>& n, int target) {
		vector<vector<int>> ans;
		if (n.size() < 4) return ans;

		sort(n.begin(), n.end());
		return k_Sum(n, 0, target, 4);
	}


	vector<vector<int>> k_Sum(vector<int>& n, int start, int target, int k) {
		if (k == 2) return two_Sum(n, start, target);

		vector<vector<int>> ans;

		for (int i=start; i+k-1 < n.size(); i++) {
			if (i>start && n[i]==n[i-1]) continue;
			vector<vector<int>> subAns = k_Sum(n, i+1, target-n[i], k-1);
			for (auto& v:subAns) {
				v.push_back(n[i]);
				ans.push_back(v);
			}
		}

		return ans;
	}


	vector<vector<int>> two_Sum(vector<int>& n, int start, int target) {
		vector<vector<int>> ans;
		int lo = start, hi = n.size()-1;
		
		while (lo < hi) {
			int sum = n[lo] + n[hi];
			if (sum == target) {
				ans.push_back({ n[lo], n[hi] });
				while (lo<hi && n[lo]==n[lo+1]) lo++;
				while (lo<hi && n[hi]==n[hi-1]) hi--;
				lo++, hi--;
			}
			else if (sum > target)
				hi--;
			else
				lo++;
		}
		return ans;
	}
};





/*
or essentially the same idea as 3-sum.
take a number, find its next 3sum target. if got it, push to ans.
*/

class Solution {
public:
	vector<vector<int>> fourSum(vector<int>& n, int target) {
		vector<vector<int>> ans;
		if (n.size() < 4) return ans;

		sort(n.begin(), n.end());
		for (int i=0; i+3<n.size(); i++) {
			if (i>0 && n[i]==n[i-1]) continue;
			int target2 = target - n[i];
			vector<vector<int>> subAns = threeSum(n, i+1, target2);
			for (auto& v:subAns) {
				v.insert(v.begin(), n[i]);
				ans.push_back(v);
			}
		}

		return ans;
	}


	vector<vector<int>> threeSum(vector<int>& n, int start, int target) {
		vector<vector<int>> ans;

		for (int i=start; i<n.size(); i++) {
			if (i>start && n[i]==n[i-1]) continue;

			int target2 = target - n[i];
			int lo = i+1, hi = n.size()-1;

			while (lo < hi) {
				if (n[lo] + n[hi] == target2) {
					ans.push_back({ n[i], n[lo], n[hi] });
					while (lo<hi && n[lo]==n[lo+1]) lo++;
					while (lo<hi && n[hi]==n[hi-1]) hi--;
					lo++, hi--;
					/*
					--------- alternatively --------
					lo = upper_bound(n.begin()+lo, n.begin()+hi, n[lo]) - n.begin();
					hi = lower_bound(n.begin()+lo, n.begin()+hi, n[hi]) - n.begin() - 1;
					*/
				} else if (n[lo] + n[hi] > target2) {
					hi--;
				} else {
					lo++;
				}
			}
		}

		return ans;
	}
};

