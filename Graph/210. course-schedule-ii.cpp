/*
https://leetcode.com/problems/course-schedule-ii/

There are a total of n courses you have to take labelled from 0 to n - 1.

Some courses may have prerequisites, for example, if prerequisites[i] = [ai, bi] this means you must take the course bi before the course ai.

Given the total number of courses numCourses and a list of the prerequisite pairs, return the ordering of courses you should take to finish all courses.

If there are many valid answers, return any of them. If it is impossible to finish all courses, return an empty array.

 

Example 1:

Input: numCourses = 2, prerequisites = [[1,0]]
Output: [0,1]
Explanation: There are a total of 2 courses to take. To take course 1 you should have finished course 0. So the correct course order is [0,1].
Example 2:

Input: numCourses = 4, prerequisites = [[1,0],[2,0],[3,1],[3,2]]
Output: [0,2,1,3]
Explanation: There are a total of 4 courses to take. To take course 3 you should have finished both courses 1 and 2. Both courses 1 and 2 should be taken after you finished course 0.
So one correct course order is [0,1,2,3]. Another correct ordering is [0,2,1,3].
Example 3:

Input: numCourses = 1, prerequisites = []
Output: [0]

*/

class Solution {
public:
	vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites);
};

vector<int> Solution::findOrder(int N, vector<vector<int>>& pre) {

	vector<vector<int>> graph(N, vector<int>());
	for (auto i: pre)
		graph[i[1]].push_back(i[0]);

	// run Kahn's algo for topsort to find the order to enroll
	vector<int> indegree(N, 0);
	// compute indegree of all nodes
	for (auto adj: graph)
		for (auto i: adj)
			indegree[i]++;
	// push all nodes with 0 indeg to queue
	queue<int> q;
	for (int i=0; i<N; i++)
		if (indegree[i]==0) q.push(i);
	// pop and decrease indeg of neighboring nodes
	// and if indeg becomes 0, add it too
	int visited = 0;
	vector<int> topOrder; topOrder.reserve(N);

	while (!q.empty()) {
		int curr = q.front(); q.pop();
		visited++;
		topOrder.push_back(curr);
		// decrease indeg of neighboring nodes
		for (int i=0; i<graph[curr].size(); i++)
			if (--indegree[graph[curr][i]] == 0)
				q.push(graph[curr][i]);
	}

	// check if there was a cycle, empty the array
	if (visited != N)
		topOrder.clear();
	return topOrder;
}

static auto _______ = [](){
	std::ios::sync_with_stdio(false);
	std::cin.tie(NULL);
	std::cout.tie(NULL);
	return 0;
}();