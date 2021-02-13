// https://leetcode.com/problems/split-array-largest-sum/

class Solution {
	bool isPossible(vector<int>& A, int k, int maxSum) {
		if (A.size() < k) return false;
		int sum=0, partitions=1;
		for (int i=0; i<A.size(); i++) {
			if (A[i] > maxSum) return false;
			sum += A[i];
			if (sum > maxSum)	partitions++, sum=A[i];
			if (partitions > k)	return false;
		}
		return true;
	}
	
public:
	int splitArray(vector<int>& A, int k) {
		int lo = *max_element(A.begin(), A.end());
		int hi = accumulate(A.begin(), A.end(), 0);
		int ans = -1;
		while (lo <= hi) {
			int mid = lo + (hi-lo)/2;
			if (isPossible(A, k, mid))
				ans=mid, hi = mid-1;
			else
				lo = mid+1;
		}
		return ans;
	}
};