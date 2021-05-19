// https://leetcode.com/problems/maximum-number-of-eaten-apples/

/*
There is a special kind of apple tree that grows apples every day for n days.
On the ith day, the tree grows apples[i] apples that will rot after days[i] days,
that is on day i + days[i] the apples will be rotten and cannot be eaten.
On some days, the apple tree does not grow any apples,
which are denoted by apples[i] == 0 and days[i] == 0.

You decided to eat at most one apple a day (to keep the doctors away).
Note that you can keep eating after the first n days.

Given two integer arrays days and apples of length n,
return the maximum number of apples you can eat.

Example 1:

Input: apples = [1,2,3,5,2], days = [3,2,1,4,2]
Output: 7
Explanation: You can eat 7 apples:
- On the first day, you eat an apple that grew on the first day.
- On the second day, you eat an apple that grew on the second day.
- On the third day, you eat an apple that grew on the second day.
	After this day, the apples that grew on the third day rot.
- On the fourth to the seventh days, you eat apples that grew on the fourth day.
*/



/*
It's optimal to finish the apples that will rot first before those that will rot last
You need a structure to keep the apples sorted by their finish time
*/
class Solution {
public:
	int eatenApples(vector<int>& A, vector<int>& D) {

		priority_queue<array<int,2>, vector<array<int,2>>,
			greater<array<int,2>>> pq;

		int eaten = 0, curDay = 0;
		
		for (int i = 0; i < A.size(); i++, curDay++) {
			if (A[i] > 0) pq.push({ i+D[i], A[i] });
			while (!pq.empty() && pq.top()[0] <= curDay) pq.pop();
			if (pq.empty()) continue;

			auto top = pq.top(); pq.pop();
			if (top[0] > curDay and --top[1] > 0) pq.push(top);
			eaten++;
		}
		
		for ( ; !pq.empty(); curDay++) {
			while (!pq.empty() && pq.top()[0] <= curDay) pq.pop();
			if (pq.empty()) continue;
			auto top = pq.top(); pq.pop();
			if (top[0] > curDay and --top[1] > 0) pq.push(top);
			eaten++;
		}
		
		return eaten;
	}
};










// https://leetcode.com/problems/maximum-number-of-eaten-apples/

class Solution {
public:
	int eatenApples(vector<int>& A, vector<int>& D) {

		priority_queue<array<int,2>, vector<array<int,2>>,
			greater<array<int,2>>> pq;

		int eaten = 0, curDay = 0;
		
		for (int i = 0; i < A.size() or !pq.empty(); i++, curDay++) {
			if (i < A.size() and A[i] > 0) pq.push({ i + D[i], A[i] });
			while (!pq.empty() && pq.top()[0] <= curDay) pq.pop();
			if (!pq.empty()) {
				auto top = pq.top(); pq.pop();
				if (top[0] > curDay and --top[1] > 0) pq.push(top);
				eaten++;
			}
		}

		return eaten;
	}
};





// https://leetcode.com/problems/maximum-number-of-eaten-apples/

class Solution {
public:
	int eatenApples(vector<int>& A, vector<int>& D) {

		priority_queue<array<int,2>, vector<array<int,2>>,
			greater<array<int,2>>> pq;

		int eaten = 0, curDay = 0;
		
		for (int i = 0; i < A.size() or !pq.empty(); i++, curDay++) {
			// if possible to push, push cur apple's expiry date, and its index
			if (i < A.size() and A[i] > 0) pq.push({ i + D[i], i });
			// remove rotten apples
			while (!pq.empty() && pq.top()[0] <= curDay) pq.pop();
			// if an apple can be eaten today, eat it
			// after eating, if any more apples are not left, remove from pq
			if (!pq.empty()) {
				if (--A[pq.top()[1]] == 0) pq.pop();
				eaten++;
			}
		}

		return eaten;
	}
};