// https://leetcode.com/problems/maximum-width-ramp/






/*
reverse the array,
then find smaller ele farthest on the right for every ele
update the max diff accordingly at every step.

keep suffixes array.
suffixes[i] stores the min ele in [i, N-1]
so, suffixes arr is strictly non-decreasing
so, we can binary search the upper bound of A[i] in it, and we get our j.

[6,0,8,2,1,5]
[5 1 2 8 0 6]
[0 0 0 0 0 6]

*/
class Solution {
public:
	int maxWidthRamp(vector<int>& A) {
		reverse(A.begin(), A.end());
		// find smaller ele farthest on the right
		int N = A.size(), ans = 0;
		vector<int> suffixes = A;
		
		for (int i = N-2, mn = A[N-1]; i >= 0; i--) {
			suffixes[i] = min(A[i], suffixes[i+1]);
		}
		
		for (int i = 0; i < N-1; i++) {
			int ind = upper_bound(
				suffixes.begin()+i+1, suffixes.end(), A[i])
				- suffixes.begin() - 1;
			if (ind < N and ind > i) {
				ans = max(ans, ind - i);
			}
		}
		
		return ans;
	}
};





/*
------- no need to reverse A -------

need to write our own binary search fn, or use rbegin(), rend()
[9,8,1,0,1,9,4,0,4,1]
[9 9 9 9 9 9 4 4 4 1]
*/
class Solution {
public:
	int maxWidthRamp(vector<int>& A) {
		int N = A.size(), ans = 0;
		vector<int> suffixes = A;
		
		for (int i = N-2; i >= 0; i--) {
			suffixes[i] = max(A[i], suffixes[i+1]);
		}
		
		for (int i = 0; i < N-1; i++) {
			int lb = lower_bound(
				suffixes.rbegin(), suffixes.rbegin()+N-1-i, A[i])
				- suffixes.rbegin();
			int ind = N - 1 - lb;
			if (ind < N and ind > i)
				ans = max(ans, ind - i);
		}
		
		return ans;
	}
};








/*
------ using stack O(N log N) ------

We push elements into the stack in the decreasing order, tracking their indexes.
If A[i] is greater or equal than the top of the stack, we do not need to track it
(there is a better pair somewhere already).

Now, since elements in the stack are sorted,
we can use binary search to find the maximum element smaller or equal A[i].
That element is guaranteed to have a maximum distance from A[i].

Example: [9,8,1,0,1,9,4,0,4,1]
Our stack: [{9, 0}, {8, 1}, {1, 2}, {0, 3}]
For A[9], we will find {1, 2}, so the distance is 9 - 2 = 7.
*/
class Solution {
public:
	int maxWidthRamp(vector<int>& A) {
		int N = A.size(), ans = 0;
		vector<pair<int,int>> s;
		
		for (int i = 0; i < N; i++) {
			// make a strictly decreasing stack
			if (s.empty() or A[i] < s.back().first) {
				s.push_back({ A[i], i });
			}
			// use binary search to find the maximum element smaller or equal A[i]
			else {
				int ind = lower_bound(s.begin(), s.end(), make_pair(A[i], INT_MAX),
					greater<pair<int, int>>()) - s.begin();
				ans = max(ans, i - s[ind].second);
			}
		}
		
		return ans;
	}
};




/*
------ using stack O(N) ------

why are we checking elements left to right
while the maximum is likely to be on the far right side?

If we check elements right to left, we do not need to keep smaller elements in the stack.
So, we first populate the stack left to right with elements in decreasing order,
and then go right to left and pop all elements smaller than the current one.
This gives us O(n) runtime. One additional optimization is to populate stack
until the top <= A[A.size() - 1].
*/

int maxWidthRamp(vector<int>& A, int ans = 0) {
	vector<int> v = { 0 };

	for (int i = 1; A[v.back()] > A[A.size() - 1]; ++i)
		if (A[v.back()] > A[i]) v.push_back(i);

	for (int j = A.size() - 1; j > ans; --j) {
		while (!v.empty() && A[v.back()] <= A[j]) {
			ans = max(ans, j - v.back());
			v.pop_back();
		}
	}

	return ans;
}