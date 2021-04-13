// https://leetcode.com/problems/best-sightseeing-pair/

/*
You are given an integer array values where values[i] represents the value of the ith sightseeing spot.
Two sightseeing spots i and j have a distance j - i between them.

The score of a pair (i < j) of sightseeing spots is values[i] + values[j] + i - j:
the sum of the values of the sightseeing spots, minus the distance between them.

Return the maximum score of a pair of sightseeing spots.

Example 1:

Input: values = [8,1,5,2,6]
Output: 11
Explanation: i = 0, j = 2, values[i] + values[j] + i - j = 8 + 5 + 0 - 2 = 11
*/

class Solution {
public:
	int maxScoreSightseeingPair(vector<int>& v) {
		int prev = v[0], ans = v[0]+v[1]-1;
		for (int i=1; i < v.size(); i++) {
			ans = max(ans, prev + v[i] - i);
			prev = max(prev, v[i] + i);
		}
		return ans;
	}
};




/*
Count the current best score in all previous sightseeing spot.
Note that, as we go further, the score of previous spot decrement.

cur will record the best score that we have met.
We iterate each value a in the array A,
update res by max(res, cur + a)

Also we can update cur by max(cur, a).
Note that when we move forward,
all sightseeing spot we have seen will be 1 distance further.

So for the next sightseeing spot cur = Math.max(cur, a) - 1

There is a feeling that,
"A near neighbor is better than a distant cousin."
*/
class Solution {
public:
	int maxScoreSightseeingPair(vector<int>& A) {
		int res = 0, cur = 0;
		for (int a: A) {
			res = max(res, cur + a);
			cur = max(cur, a) - 1;
		}
		return res;
	}
};




/*
Intuition
It's similar to Best Time to Buy and Sell Stock, but instead of min price, we track max value, and our max value decays every step due to the distance penalty.

Solution
Track the maximum value of A[i] as max_i.
Every turn, decrement max_ito account for j - i.
Track and return the maximum score.
*/

int maxScoreSightseeingPair(vector<int>& A, int res = 0) {
  for (auto j = 1, max_i = A[0] - 1; j < A.size(); ++j) {
		res = max(res, A[j] + max_i);
		max_i = max(max_i, A[j]);
		max_i--;
  }
  return res;
}