// https://leetcode.com/problems/find-minimum-time-to-finish-all-jobs/




/*
backtracking - TLE

I assign every task to one of the k workers
and find the answer to current state when all tasks are assigned.
*/
class Solution {
	int time[12] = {};
	int ans;

public:
	int minimumTimeRequired(vector<int>& jobs, int k) {
		ans = INT_MAX;
		memset(time, 0, sizeof(time));
		backtrack(jobs, k, 0);
		return ans;
	}
	
	void backtrack(vector<int>& jobs, int K, int i) {
		if (i == jobs.size()) {
			ans = min(ans, *max_element(time, time+K));
			return;
		}
		for (int k = 0; k < K; k++) {
			time[k] += jobs[i];
			backtrack(jobs, K, i+1);
			time[k] -= jobs[i];
		}
	}
};






/*
------- DP ---------

assign a subset of the jobs to every worker

# each worker gets a subset of tasks
# remaining subproblem = bitmask of remaining tasks, k-1
# enumerate all subsets for each worker
# make sure no intersection with already selected
*/
class Solution {
	int sum[1 << 12] = {};
	int dp[1 << 12][12+1];

public:
	int minimumTimeRequired(vector<int>& jobs, int k) {
		int N = jobs.size();
		// find sum of all the possible subsets
		for (int i = 0; i < (1 << N); i++)
			for (int j = 0; j < N; j++)
				if (i & (1 << j))
					sum[i] += jobs[j];
		
		memset(dp, -1, sizeof(dp));
		return assignJobs(N, 0, k);
	}
	
	int assignJobs(int N, int mask, int k) {
		if (mask+1 == (1 << N) and k == 0) return 0;
		if (mask+1 == (1 << N)  or k == 0) return INT_MAX;
		if (dp[mask][k] != -1) return dp[mask][k];

		int ans = INT_MAX;
		for (int subset = 0; subset < (1<<N); subset++) {
			if (subset & mask) continue;
			int curAns = max(sum[subset], assignJobs(N, mask | subset, k-1));
			ans = min(ans, curAns);
		}

		return dp[mask][k] = ans;
	}
};