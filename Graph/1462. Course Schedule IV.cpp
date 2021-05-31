// https://leetcode.com/problems/course-schedule-iv/

/*
There are a total of numCourses courses you have to take, labeled from 0 to numCourses - 1.
You are given an array prerequisites where prerequisites[i] = [ai, bi]
indicates that you must take course bi first if you want to take course ai.

For example, the pair [0, 1], indicates that to take course 0 you have to first take course 1.
You are also given an array queries where queries[j] = [uj, vj]. For the jth query,
you should answer whether the course uj is a prerequisite of the course vj or not.
Note that if course a is a prerequisite of course b and course b is a prerequisite of course c,
then, course a is a prerequisite of course c.

Return a boolean array answer, where answer[j] is the answer of the jth query.

 

Example 1:


Input: numCourses = 2, prerequisites = [[1,0]], queries = [[0,1],[1,0]]
Output: [false,true]
Explanation: course 0 is not a prerequisite of course 1 but the opposite is true.
*/











// use Floyd Warshall to find evry node to every node shortest path
// for query [a, b] if path from a->b is infinite, means not a prerequisite

/*
------ alternate ----
Imagine if the courses are nodes of a graph. We need to build an array isReachable[i][j].
Start a bfs from each course i and assign for each course j you visit isReachable[i][j] = True.
Answer the queries from the isReachable array.

code in python file
*/
class Solution {
public:
	vector<bool> checkIfPrerequisite(int N,
		vector<vector<int>>& P, vector<vector<int>>& Q) {
		// initialize dp table
		vector<vector<int>> dp(N, vector<int> (N, 10000));
		for (auto& e : P)
			dp[e[0]][e[1]] = 1;

		for (int i = 0; i < N; i++)
			dp[i][i] = 0;

		// fill dp table
		for (int k = 0; k < N; k++)
			for (int i = 0; i < N; i++)
				for (int j = 0; j < N; j++)
					dp[i][j] = min(dp[i][j], dp[i][k] + dp[k][j]);
		
		vector<bool> ans(Q.size());
		for (int i = 0; i < Q.size(); i++) {
			int u = Q[0], v = Q[1];
			ans[i] = dp[u][v] < 10000;
		}

		return ans;
	}
};