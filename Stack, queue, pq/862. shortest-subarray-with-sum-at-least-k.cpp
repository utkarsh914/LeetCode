// https://leetcode.com/problems/shortest-subarray-with-sum-at-least-k/

// reference: https://1e9.medium.com/monotonic-queue-notes-980a019d5793


#define ff first
#define ss second

class Solution {
public:
	int shortestSubarray(vector<int>& A, int K) {

		int minL = INT_MAX;
		deque<pair<int,int>> mq; // pair<index, value>

		mq.push_back({-1, 0});

		for (int i=0; i<A.size(); i++) {

			A[i] += i==0 ? 0 : A[i-1]; // overwrite A as presum

			while (!mq.empty() && A[i] < mq.back().ss) // removing not needed elements
				mq.pop_back();

			while (!mq.empty() && A[i]-mq.front().ss >= K) {
				minL = min(minL, i-mq.front().ff); // shrinking a window by moving left pointer and updating result
				mq.pop_front();
			}

			mq.push_back({i, A[i]});
		}

		return minL==INT_MAX ? -1 : minL;
	}
};