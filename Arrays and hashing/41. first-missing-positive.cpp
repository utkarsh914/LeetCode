// https://leetcode.com/problems/first-missing-positive/

// ********** naive *********
class Solution {
public:
	int firstMissingPositive(vector<int>& nums) {
		if (nums.empty()) return 1;
		unordered_set<int> set(nums.begin(), nums.end());
		int max_ = *max_element(nums.begin(), nums.end());
		max_ = max(max_, 1);
		for (int i=1; i<=max_; i++)
			if (!set.count(i))
				return i;
		return max_+1;
	}
};









/*
Store nums in indices by making val at that index as –ve.

One main thing is to get rid of all –ve nums at first.
So, make all n <= 0 as size+1

Then iterate over array, and make A[abs(A[i])-1] as negative.
At last scan the array. If A[i] is +ve, it means i+1 is the answer.

*/

class Solution {
public:
	int firstMissingPositive(vector<int>& A) {
		int N = A.size();
		for (int& x : A)
			if (x <= 0) x = N+1;
		
		for (int i = 0; i < N; i++) {
			if (abs(A[i]) > N) continue;
			int n = abs(A[i]) - 1;
			if (A[n] > 0) A[n] *= -1;
		}
		
		for (int i = 0; i < N; i++)
			if (A[i] > 0) return i+1;
		return N+1;
	}
};









// ******** O(n) time, O(1) space *******
class Solution {
public:
	int firstMissingPositive(vector<int>& nums) {
		
		if (nums.empty()) return 1;
		int maxNum = nums.size()+1;
		// ignore negative and greater nums
		for (int& n:nums) {
			if (n<=0 or n>=maxNum)
				n = 0;
		}

		for (int& n : nums) {
			int val = n % maxNum;
			if (val == 0) continue;
			nums[val-1] += maxNum;
		}

		for (int i = 0; i < nums.size(); i++) {
			if (nums[i] < maxNum)
				return i+1;
		}
		
		return maxNum;
	}
};









class Solution {
public:
	int firstMissingPositive(vector<int>& nums) {
		int i = 0, n = nums.size();

		while (i < n) {
			if (nums[i] > 0 && nums[i] <= n && nums[nums[i] - 1] != nums[i])
				swap(nums[i], nums[nums[i]-1]);
			else
				i++;
		}

		for (i = 0; i < n; ++i)
			if (nums[i] != (i+1))
				return i+1;

		return n+1;
	}
}