// https://leetcode.com/problems/last-moment-before-all-ants-fall-out-of-a-plank/

/*
We have a wooden plank of the length n units. Some ants are walking on the plank, each ant moves with speed 1 unit per second. Some of the ants move to the left, the other move to the right.

When two ants moving in two different directions meet at some point, they change their directions and continue moving again. Assume changing directions doesn't take any additional time.

When an ant reaches one end of the plank at a time t, it falls out of the plank imediately.

Given an integer n and two integer arrays left and right, the positions of the ants moving to the left and the right. Return the moment when the last ant(s) fall out of the plank.

*/





/*
If two ants bump into each other and change directions,
it's the same as if these ants continue as nothing happens.

So, we can think about that plank as a two-way street.
So, find the maximum units that any ant needs to travel.

I got this intuition by manually solving few test cases.
My first idea was simulation, but the implementation seemed too complex.
So, I was already looking for ways to simplify it.

For me, during the contest and the interview,
finding few good test cases and solving them manually is the way to unstuck.
*/
class Solution {
public:
	int getLastMoment(int n, vector<int>& left, vector<int>& right) {
		int ld = 0, rd = 0;
		for (int p : left)
			ld = max(ld, p);
		for (int p : right)
			rd = max(rd, n-p);
		return max(ld, rd);
	}
};