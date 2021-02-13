// https://leetcode.com/problems/course-schedule/
/*
There are a total of numCourses courses you have to take, labeled from 0 to numCourses-1.

Some courses may have prerequisites, for example to take course 0 you have to first take course 1, which is expressed as a pair: [0,1]

Given the total number of courses and a list of prerequisite pairs, is it possible for you to finish all courses?

 

Example 1:

Input: numCourses = 2, prerequisites = [[1,0]]
Output: true
Explanation: There are a total of 2 courses to take. 
			 To take course 1 you should have finished course 0. So it is possible.
Example 2:

Input: numCourses = 2, prerequisites = [[1,0],[0,1]]
Output: false
Explanation: There are a total of 2 courses to take. 
			 To take course 1 you should have finished course 0, and to take course 0 you should
			 also have finished course 1. So it is impossible.
 

Constraints:

The input prerequisites is a graph represented by a list of edges, not adjacency matrices. Read more about how a graph is represented.
You may assume that there are no duplicate edges in the input prerequisites.
1 <= numCourses <= 10^5
*/

class Solution {
public:
	vector<bool> visited;
	unordered_set<int> inStack;
	bool canFinish(int n, vector<vector<int>>& pre);
	bool isCyclic(int n, vector<vector<int>>& pre);
	bool dfs(int V, vector<vector<int>>& pre);
};

bool Solution::dfs(int V, vector<vector<int>>& pre) {
	if (visited[V] and inStack.count(V))
		return true;
	visited[V] = true;
	inStack.insert(V);
	for (auto i: pre[V])
		if (dfs(i,pre)) return true;
	inStack.erase(V);
	return false;
}

bool Solution::isCyclic(int N, vector<vector<int>>& pre) {
	visited = vector<bool> (N, false);
	for (int i=0; i<N; i++) {
		if (!visited[i]) {
			inStack.clear();
			if (dfs(i, pre))
				return true;
		}
	}
	return false;
}

bool Solution::canFinish(int N, vector<vector<int>>& pre) {
	vector<vector<int>> graph(N, vector<int>());
	for (auto i: pre)
		graph[i[0]].push_back(i[1]);
	return !isCyclic(N, graph);
}

static auto _______ = [](){
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);
	return 0;
}();