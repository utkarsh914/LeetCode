/*
https://leetcode.com/problems/course-schedule-iii/

There are n different online courses numbered from 1 to n. Each course has some duration(course length) t and closed on dth day. A course should be taken continuously for t days and must be finished before or on the dth day. You will start at the 1st day.

Given n online courses represented by pairs (t,d), your task is to find the maximal number of courses that can be taken.

Exapqle:

Input: [[100, 200], [200, 1300], [1000, 1250], [2000, 3200]]
Output: 3
Explanation: 
There're totally 4 courses, but you can take 3 courses at most:
First, take the 1st course, it costs 100 days so you will finish it on the 100th day, and ready to take the next course on the 101st day.
Second, take the 3rd course, it costs 1000 days so you will finish it on the 1100th day, and ready to take the next course on the 1101st day. 
Third, take the 2nd course, it costs 200 days so you will finish it on the 1300th day. 
The 4th course cannot be taken now, since you will finish it on the 3300th day, which exceeds the closed date.
*/

bool mycomp(vector<int>& v1, vector<int>& v2) {
	return (v1[1] < v2[1]);
}

class Solution {
public:
	int scheduleCourse(vector<vector<int>>& courses) {
		sort(courses.begin(), courses.end(), mycomp);
		int timeSpent=0;
		priority_queue<int> pq;
		for (int i=0; i<courses.size(); i++) {
			int duration = courses[i][0];
			int deadline = courses[i][1];
			if (duration > deadline) continue;
			if (timeSpent+duration <= deadline) {
				timeSpent += duration;
				pq.push(duration);
			}
			else if (pq.top() > duration) {
				timeSpent = timeSpent - pq.top() + duration;
				pq.pop();
				pq.push(duration);
			}
		}
		return pq.size();
	}
};

static auto _______ = [](){
	std::ios::sync_with_stdio(false);
	std::cin.tie(NULL);
	std::cout.tie(NULL);
	return 0;
}();