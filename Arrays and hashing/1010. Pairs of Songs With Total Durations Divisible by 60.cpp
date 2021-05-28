// https://leetcode.com/problems/pairs-of-songs-with-total-durations-divisible-by-60/

/*
You are given a list of songs
where the ith song has a duration of time[i] seconds.

Return the number of pairs of songs for which their total duration
in seconds is divisible by 60.
Formally, we want the number of indices i, j
such that i < j with (time[i] + time[j]) % 60 == 0.

 

Example 1:

Input: time = [30,20,150,100,40]
Output: 3
Explanation: Three pairs have a total duration divisible by 60:
(time[0] = 30, time[2] = 150): total duration 180
(time[1] = 20, time[3] = 100): total duration 120
(time[1] = 20, time[4] = 40): total duration 60
*/







class Solution {
public:
	int numPairsDivisibleBy60(vector<int>& time) {
		// unordered_map<int, int> m;
		vector<int> m(60);

		int count = 0;
		for (int n : time) {
			n = n % 60;
			if (n == 0) count += m[0];
			else count += m[60 - n];
			m[n]++;
		}

		return count;
	}
};