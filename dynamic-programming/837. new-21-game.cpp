// https://leetcode.com/problems/new-21-game/

/*
Alice plays the following game, loosely based on the card game "21".

Alice starts with 0 points, and draws numbers while she has less than K points.
During each draw, she gains an integer number of points randomly from the range [1, W],
where W is an integer.
Each draw is independent and the outcomes have equal probabilities.

Alice stops drawing numbers when she gets K or more points.
What is the probability that she has N or less points?

Example 1:

Input: N = 10, K = 1, W = 10
Output: 1.00000
Explanation:  Alice gets a single card, then stops.
Example 2:

Input: N = 6, K = 1, W = 10
Output: 0.60000
Explanation:  Alice gets a single card, then stops.
In 6 out of W = 10 possibilities, she is at or below N = 6 points.
Example 3:

Input: N = 21, K = 17, W = 10
Output: 0.73278
Note:

0 <= K <= N <= 10000
1 <= W <= 10000
Answers will be accepted as correct if they are within 10^-5 of the correct answer.
The judging time limit has been reduced for this question.
*/








/*
Game rule is as follows

point 0 initially
while (point < K) {
    draw w  from [1, W] randomly 
    point += w
}
probability(point <= N) ?
Let's observe that

point total range [0, K + W - 1]
we define probability[i] as probability to get i points
since all start with point 0 => probability[0] = 1

Probability transition:

Before we reach point `i`, we draw `w`, i.e., our last point is `i - w` 

probability to get i points = sum(probability to get i - w points * 1 / W) for w can be any of [1, W]
where 0 <= i - w < K
target probability = sum of prabability to get points [K, N]
*/
class Solution {
public:
	double new21Game(int N, int K, int W) {
		if (K == 0) return 1;

		int maxPoints = K - 1 + W;
		vector<double> dp(maxPoints + 1, 0);
		dp[0] = 1;

		for (int sum = 1; sum <= maxPoints; sum++) {
			for (int w = 1; w <= W; w++) {
				if (sum - w >= 0 and sum - w < K)
					dp[sum] += (dp[sum - w]) * (1.0 / W);
			}
		}

		double ans = 0;
		for (int i = K; i <= N; i++)
			ans += dp[i];

		return ans;
	}
};










/*
Intuition:
The same problems as "Climbing Stairs" or "Fibo Sequence".

Explanation:
dp[i] is the probability that we get points i at some moment.
In another word:
1 - dp[i]is the probability that we skip the points i.

The do equation is that:
dp[i] = sum(last W dp values) / W

To get Wsum = sum(last W dp values),
we can maintain a sliding window with size at most W.


Time Complexity:
Time O(N)
Space O(N), can be improve to O(W)
*/
class Solution {
public:
	double new21Game(int N, int K, int W) {
		if (K == 0) return 1;

		int maxPoints = K - 1 + W;
		vector<double> dp(maxPoints + 1, 0);
		dp[0] = 1;

		double windowSum = 1.0, ans = 0.0;

		for (int sum = 1; sum <= maxPoints; sum++) {
			dp[sum] = windowSum * (1.0 / W);
			if (sum < K) windowSum += dp[sum];
			if (sum - W >= 0) windowSum -= dp[sum - W];
		}

		for (int i = K; i <= N; i++)
			ans += dp[i];

		return ans;
	}
};