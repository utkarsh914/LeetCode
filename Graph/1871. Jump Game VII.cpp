// https://leetcode.com/problems/jump-game-vii/

/*
You are given a 0-indexed binary string s and two integers minJump and maxJump. In the beginning, you are standing at index 0, which is equal to '0'. You can move from index i to index j if the following conditions are fulfilled:

i + minJump <= j <= min(i + maxJump, s.length - 1), and
s[j] == '0'.
Return true if you can reach index s.length - 1 in s, or false otherwise.

 

Example 1:

Input: s = "011010", minJump = 2, maxJump = 3
Output: true
Explanation:
In the first step, move from index 0 to index 3. 
In the second step, move from index 3 to index 5.

Example 2:

Input: s = "01101110", minJump = 2, maxJump = 3
Output: false
 

Constraints:

2 <= s.length <= 105
s[i] is either '0' or '1'.
s[0] == '0'
1 <= minJump <= maxJump < s.length
*/











/*
problem can be solved using BFS.
there is an edge from index i to every index j in range
[i+minJ, i+maxJ], if s[j] == '0'.

doing regular BFS leads to TLE, as it'll lead to same indices
being pushed multiple times.

to optimize, we'll push each index only once to the queue.
can use a visited array to check if already pushed.

or even better, use an int max_reached,
which says all the indices in range [0, max_reached]
have been pushed.
so, for cur node, start pushing cur's children in range
[max_reached + 1, cur + maxJump]

*/
class Solution {
	int min(int x, int y) { return x < y ? x : y; }
	int max(int x, int y) { return x > y ? x : y; }
public:
	bool canReach(string& s, int minJump, int maxJump) {
		if (s.back() != '0') return false;
		int N = s.size(), max_reached = 0;
		queue<int> q;
		q.push(0);
		
		while (!q.empty()) {
			int cur = q.front(); q.pop();
			if (cur == N-1)
				return true;
			// push the children which hav not been pushed yet
			int start = max(cur + minJump, max_reached + 1);
			int end = min(cur + maxJump, N-1);
			for (int i = start; i <= end; i++) {
				if (s[i] == '0')
					q.push(i);
			}
			// we have pushed all indices that are in range
			// [cur+minJ, cur+maxJ], and weren't pushed before
			max_reached = cur + maxJump;
		}
		
		return false;
	}
};