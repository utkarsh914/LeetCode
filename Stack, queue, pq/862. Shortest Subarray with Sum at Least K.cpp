// https://leetcode.com/problems/shortest-subarray-with-sum-at-least-k/

/*
Given an integer array nums and an integer k,
return the length of the shortest non-empty subarray of nums
with a sum of at least k. If there is no such subarray, return -1.

A subarray is a contiguous part of an array.

Example 1:

Input: nums = [1], k = 1
Output: 1

Example 2:

Input: nums = [1,2], k = 4
Output: -1

Example 3:

Input: nums = [2,-1,2], k = 3
Output: 3 

Constraints:

1 <= nums.length <= 105
-105 <= nums[i] <= 105
1 <= k <= 109
*/






/*
first calculate a presum array
then keep these presums in strict monotonic increasing order
and binary search the required value (cur_presum - k)
and update the ans
*/
class Solution {
public:
	int shortestSubarray(vector<int>& nums, int k) {
		vector<int> sum {0};
		for (int n : nums)
			sum.push_back(sum.back() + n);
		
		vector<pair<int,int>> v;
		int ans = INT_MAX;
		
		for (int i = 0; i <= nums.size(); i++) {
			pair<int,int> p = { sum[i] - k, i };
			auto ub = upper_bound(v.begin(), v.end(), p);
			if (ub != v.begin()) {
				--ub;
				ans = min(ans, i - ub->second);
			}
			while (!v.empty() and v.back().first >= sum[i])
				v.pop_back();
			v.push_back({ sum[i], i });
		}
		
		return ans == INT_MAX ? -1 : ans;
	}
};








// reference: https://1e9.medium.com/monotonic-queue-notes-980a019d5793
#define ff first
#define ss second

class Solution {
public:
	int shortestSubarray(vector<int>& A, int K) {

		int minL = INT_MAX;
		deque<pair<int,int>> mq; // pair<index, value>

		mq.push_back({-1, 0});

		for (int i=0; i < A.size(); i++) {
			// overwrite A as presum
			A[i] += i==0 ? 0 : A[i-1];

			// removing not needed elements
			while (!mq.empty() && A[i] < mq.back().ss)
				mq.pop_back();

			// shrinking a window by moving left pointer and updating result
			while (!mq.empty() && A[i]-mq.front().ss >= K) {
				minL = min(minL, i-mq.front().ff);
				mq.pop_front();
			}

			mq.push_back({i, A[i]});
		}

		return minL == INT_MAX ? -1 : minL;
	}
};









class Solution {
public:
	int shortestSubarray(vector<int>& A, int K) {

		int minL = INT_MAX;
		deque<int> mq; // stores indices

		for (int i = 0; i < A.size(); i++) {
			// overwrite A as presum
			A[i] += i==0 ? 0 : A[i-1];
			
			// in case mq is empty (for index 0)
			if (A[i] >= K) minL = min( minL, i+1 );

			// removing not needed elements
			while (!mq.empty() && A[i] <= A[mq.back()])
				mq.pop_back();

			// shrinking a window by moving left pointer and updating result
			while (!mq.empty() && A[i] - A[mq.front()] >= K) {
				minL = min(minL, i - mq.front() );
				mq.pop_front();
			}

			mq.push_back(i);
		}

		return minL == INT_MAX ? -1 : minL;
	}
};
/*
Q: Why keep the deque increase?
A: If B[i] <= B[d.back()] and moreover we already know that i > d.back(), it means that compared with d.back(),
B[i] can help us make the subarray length shorter and sum bigger. So no need to keep d.back() in our deque.

More detailed on this, we always add at the LAST position
B[d.back] <- B[i] <- ... <- B[future id]
B[future id] - B[d.back()] >= k && B[d.back()] >= B[i]
B[future id] - B[i] >= k too

so no need to keep B[d.back()]
*/