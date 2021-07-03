// https://leetcode.com/problems/single-threaded-cpu/












/*
first sort the tasks by starting time

To simulate the problem we first need to note that
if at any point in time there are no enqueued tasks
we need to wait to the smallest enqueue time of a non-processed element.
for this, we'll jump directly to the time of next element to be pushed in the pq.

We need a data structure like a min-heap
to support choosing the task with the smallest processing time
from all the enqueued tasks.
*/
class Solution {
public:
	vector<int> getOrder(vector<vector<int>>& tasks) {
		for (int i = 0; i < tasks.size(); i++)
			tasks[i].push_back(i);
		sort(tasks.begin(), tasks.end());
		
		priority_queue<pair<int,int>, vector<pair<int,int>>,
			greater<pair<int,int>> > pq;
		
		vector<int> ans; ans.reserve(tasks.size());
		long i = 0, time = 0;

		while (ans.size() < tasks.size()) {
			if (pq.empty()) {
				time = max(time, (long) tasks[i][0]);
			}
			while (i < tasks.size() and tasks[i][0] <= time) {
				pq.push({ tasks[i][1], tasks[i][2] });
				i++;
			}
			auto [processingTime, taskID] = pq.top(); pq.pop();
			ans.push_back(taskID);
			time += processingTime;
		}
		
		return ans;
	}
};








// a bit lengthy and slow
class Solution {
public:
	vector<int> getOrder(vector<vector<int>>& tasks) {
		map<int,int> times;
		for (int i = 0; i < tasks.size(); i++) {
			tasks[i].push_back(i);
			times[tasks[i][0]]++;
		}
		sort(tasks.begin(), tasks.end());
		
		auto comp = [](auto& a, auto& b) {
			return a[1] == b[1] ? a[2] > b[2] : a[1] > b[1];
		};
		priority_queue<vector<int>, vector<vector<int>>,
			decltype(comp)> pq(comp);
		
		vector<int> ans; ans.reserve(tasks.size());
		long i = 0, time = tasks[0][0];

		while (ans.size() < tasks.size()) {
			while (i < tasks.size() and tasks[i][0] <= time)
				pq.push(tasks[i++]);
			if (pq.empty()) time = times.begin()->first;
			else {
				auto top = pq.top(); pq.pop();
				ans.push_back(top[2]);
				time += top[1];
				if (--times[top[0]] == 0)
					times.erase(top[0]);
			}
		}
		
		return ans;
	}
};