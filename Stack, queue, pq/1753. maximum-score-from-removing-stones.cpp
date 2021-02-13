// https://leetcode.com/problems/maximum-score-from-removing-stones/

/*
You are playing a solitaire game with three piles of stones of sizes a​​​​​​, b,​​​​​​ and c​​​​​​ respectively.
Each turn you choose two different non-empty piles, take one stone from each, and add 1 point to your score.
The game stops when there are fewer than two non-empty piles (meaning there are no more available moves).
Given three integers a​​​​​, b,​​​​​ and c​​​​​, return the maximum score you can get.

Example 1:

Input: a = 2, b = 4, c = 6
Output: 6
Explanation: The starting state is (2, 4, 6). One optimal set of moves is:
- Take from 1st and 3rd piles, state is now (1, 4, 5)
- Take from 1st and 3rd piles, state is now (0, 4, 4)
- Take from 2nd and 3rd piles, state is now (0, 3, 3)
- Take from 2nd and 3rd piles, state is now (0, 2, 2)
- Take from 2nd and 3rd piles, state is now (0, 1, 1)
- Take from 2nd and 3rd piles, state is now (0, 0, 0)
There are fewer than two non-empty piles, so the game ends. Total: 6 points.
*/

class Solution {
public:
	int maximumScore(int a, int b, int c) {
		priority_queue<int> pq;
		pq.push(a), pq.push(b), pq.push(c);
		
		int score = 0;
		while (true) {
			int x = pq.top(); pq.pop();
			int y = pq.top(); pq.pop();
			if (x==0 || y==0) break;
			score++;
			pq.push(x-1); pq.push(y-1);
		}
		
		return score;
	}
};