// https://leetcode.com/problems/task-scheduler/

/*
Given a characters array tasks, representing the tasks a CPU needs to do,
where each letter represents a different task. Tasks could be done in any order.
Each task is done in one unit of time.
For each unit of time, the CPU could complete either one task or just be idle.

However, there is a non-negative integer n that represents
the cooldown period between two same tasks (the same letter in the array),
that is that there must be at least n units of time between any two same tasks.

Return the least number of units of times that
the CPU will take to finish all the given tasks.

 

Example 1:

Input: tasks = ["A","A","A","B","B","B"], n = 2
Output: 8
Explanation: 
A -> B -> idle -> A -> B -> idle -> A -> B
There is at least 2 units of time between any two same tasks.

Example 2:

Input: tasks = ["A","A","A","B","B","B"], n = 0
Output: 6
Explanation: On this case any permutation of size 6 would work since n = 0.
["A","A","A","B","B","B"]
["A","B","A","B","A","B"]
["B","B","B","A","A","A"]
...
And so on.

Example 3:

Input: tasks = ["A","A","A","A","A","A","B","C","D","E","F","G"], n = 2
Output: 16
Explanation: 
One possible solution is
A -> B -> C -> A -> D -> E -> A -> F -> G -> A -> idle -> idle -> A -> idle -> idle -> A
 

Constraints:

1 <= task.length <= 104
tasks[i] is upper-case English letter.
The integer n is in the range [0, 100].
*/








/*
**** O(N) time, O(1) space *****

detailed explanation: https://leetcode.com/problems/task-scheduler/discuss/104500/Java-O(n)-time-O(1)-space-1-pass-no-sorting-solution-with-detailed-explanation
*/
class Solution {
public:
	int leastInterval(vector<char>& tasks, int n) {

		// count freq of chars
		int f[26] = {};
		for (char& c : tasks) f[c-'A']++;

		int maxF = *max_element(f, f+26);
		int maxF_count = count(f, f+26, maxF);

		int parts = maxF - 1;
		int emptySlots = parts * (n - (maxF_count - 1));
		int availableTasks = tasks.size() - maxF * maxF_count;
		int idles = max(0, emptySlots - availableTasks);
		int result = tasks.size() + idles;

		return result;
	}
};









/*
use a pq to get the element which should be placed at current position.

we'll place an element and keep track of the index where it can be placed again.
*/
class Solution {
public:
	int leastInterval(vector<char>& tasks, int n) {
		/*
		array -> {char, amount, index}

		first priority -> smallest index should pop first
		if index equal, -> greatest amount first
		*/
		auto comp = [](array<int,3>& a, array<int,3>& b) {
			if (a[2] == b[2]) return a[1] < b[1];
			return a[2] > b[2];
		};

		priority_queue<array<int,3>, vector<array<int,3>>,
			decltype(comp)> pq(comp);

		// count freq of chars
		int f[26] = {};
		for (char& c : tasks) f[c-'A']++;

		// push to pq
		for (int i = 0; i < 26; i++)
			if (f[i] > 0) pq.push({ i, f[i], 0 });

		// build the schedule
		int i = 0;
		while (!pq.empty()) {
			if (pq.top()[2] <= i) {
				auto cur = pq.top(); pq.pop();
				cur[1]--, cur[2] += (n+1);
				if (cur[1] > 0) pq.push(cur);
			}
			i++;
		}

		return i;
	}
};

// cout << cur[0] << " " << cur[1] << " " << cur[2] << endl;







/*
in above solution
actually we don't need to store the char in the pq
just tracking amount and index does the job
*/
class Solution {
public:
	int leastInterval(vector<char>& tasks, int n) {
		/*
		array -> {char, amount, index}

		first priority -> smallest index
		if index equal, -> greatest amount first
		*/
		auto comp = [](array<int,2>& a, array<int,2>& b) {
			if (a[1] == b[1]) return a[0] < b[0];
			return a[1] > b[1];
		};

		priority_queue<array<int,2>, vector<array<int,2>>,
			decltype(comp)> pq(comp);

		// count freq of chars
		int f[26] = {};
		for (char& c : tasks) f[c-'A']++;

		// push to pq
		for (int i = 0; i < 26; i++)
			if (f[i] > 0) pq.push({ f[i], 0 });

		// build the schedule
		int i = 0;
		while (!pq.empty()) {
			if (pq.top()[1] <= i) {
				auto cur = pq.top(); pq.pop();
				cur[0]--, cur[1] += (n+1);
				if (cur[0] > 0) pq.push(cur);
			}
			i++;
		}

		return i;
	}
};