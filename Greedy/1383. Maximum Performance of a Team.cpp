// https://leetcode.com/problems/maximum-performance-of-a-team/

/*
You are given two integers n and k and two integer arrays speed and efficiency both of length n.
There are n engineers numbered from 1 to n.
speed[i] and efficiency[i] represent the speed and efficiency of the ith engineer respectively.

Choose at most k different engineers out of the n engineers to form a team
with the maximum performance.

The performance of a team is the sum of their engineers'speeds
multiplied by the minimum efficiency among their engineers.

Return the maximum performance of this team.
Since the answer can be a huge number, return it modulo 109 + 7.


Example 1:

Input: n = 6, speed = [2,10,3,1,5,8], efficiency = [5,4,3,9,7,2], k = 2
Output: 60
Explanation: 
We have the maximum performance of the team by selecting engineer 2
(with speed=10 and efficiency=4) and engineer 5 (with speed=5 and efficiency=7).
That is, performance = (10 + 5) * min(4, 7) = 60.
*/











class Solution {
public:
	int maxPerformance(int n, vector<int>& speed, vector<int>& efficiency, int k) {
		// array -> { efficiency, speed }
		// then sort in increasing order acc to efficiency
		vector<array<long, 2>> v(n);
		for (int i = 0; i < n; i++) {
			v[i] = { efficiency[i], speed[i] };
		}
		sort(v.begin(), v.end());

		// pq to keep track of minimum speed
		priority_queue<int, vector<int>, greater<int>> pq;
		// contains the sum of k-1 max speeds from [i, n-1]
		vector<long> fwdSum(n+1);

		long sum = 0, winsize = 0;
		for (int i = n-1; i >= 0; i--) {
			if (winsize < k-1) {
				sum += v[i][1]; // add speed to sum and pq
				pq.push(v[i][1]);
				winsize++;
			}
			// if min speed is less than cur person's speed, take cur person
			// and remove the min speed from sum and pq
			else if (!pq.empty() and pq.top() < v[i][1]) {
				sum -= pq.top(); pq.pop();
				sum += v[i][1];
				pq.push(v[i][1]);
			}
			fwdSum[i] = sum;
		}

		// calculate ans now
		long ans = 0, mod = 1e9+7;
		for (int i = 0; i < n; i++) {
			// take cur person as the person with min effi,
			// and pick k-1 persons from [i+1, n-1] having max sum of speeds
			// and their eff is obviously >= cur person's eff
			ans = max(ans, v[i][0] * (v[i][1] + fwdSum[i+1]));
		}

		return ans % mod;
	}
};







// cleaner
int maxPerformance(int n, vector<int>& speed, vector<int>& efficiency, int k) {
	vector<pair<int, int>> ess;
	for (int i = 0; i < n; ++i)
		ess.emplace_back(efficiency[i], speed[i]);
	sort(rbegin(ess), rend(ess));

	long sumS = 0, res = 0;
	priority_queue <int, vector<int>, greater<int>> pq; //min heap

	for(auto& [e, s]: ess){
		pq.emplace(s);
		sumS += s;
		if (pq.size() > k) {
			sumS -= pq.top();
			pq.pop();
		}
		res = max(res, sumS * e);
	}
	
	return res % (int)(1e9+7);
}