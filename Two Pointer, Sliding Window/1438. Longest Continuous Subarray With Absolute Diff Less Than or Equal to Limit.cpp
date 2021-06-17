// https://leetcode.com/problems/longest-continuous-subarray-with-absolute-diff-less-than-or-equal-to-limit/







/*
Use a sliding window approach keeping the maximum and minimum value
using a data structure like a multiset from STL in C++.

More specifically, use the two pointer technique,
moving the right pointer as far as possible to the right
until the subarray is not valid (maxValue - minValue > limit),
then moving the left pointer
until the subarray is valid again (maxValue - minValue <= limit).

Keep repeating this process.
*/
class Solution {
public:
	int longestSubarray(vector<int>& A, int limit) {
		map<int, int> mp;
		int ans = 1;

		for (int i = 0, j = 0; j < A.size(); j++) {
			mp[A[j]]++;
			while (mp.rbegin()->first - mp.begin()->first > limit and i < j) {
				// remove starting element from window
				if (--mp[A[i]] == 0) mp.erase(A[i]);
				i++;
			}
			ans = max(ans, j-i+1);
		}

		return ans;
	}
};




// using multiset
	int longestSubarray(vector<int>& A, int limit) {
		int ans = 1;
		multiset<int> m;
		for (int i = 0, j = 0; j < A.size(); ++j) {
			m.insert(A[j]);
			while (*m.rbegin() - *m.begin() > limit)
				m.erase(m.find(A[i++]));
			ans = max(ans, j-i+1);
		}
		return ans;
	}




// use 'if' instead of 'while' [LEE's way of sliding the window]
	int longestSubarray(vector<int>& A, int limit) {
		int i = 0, j;
		multiset<int> m;
		for (j = 0; j < A.size(); ++j) {
			m.insert(A[j]);
			if (*m.rbegin() - *m.begin() > limit)
				m.erase(m.find(A[i++]));
		}
		return j - i;
	}

/*
The lazy update using 'if' instead of 'while' is brilliant.

Once you reach a new better interval,
you just keep the current best interval between i and j and keep sliding,
even when it slides to a window that failed the limit requirement.
Later, when it slides to a better interval, no pop happens and i won't increase
but j will increase and you get a new better interval.

Finally, it slides to the end of the input vector, and j - i is exactly the answer we need.
*/






/*
---------- O(N) sliding window [Monotonic queue] --------

use 2 qeque to track max and min element
max_dq will be monotonic decreasing
min_dq will be monotonic increasing
*/
class Solution {
public:
	int longestSubarray(vector<int>& A, int limit) {
		deque<int> max_dq, min_dq;
		int ans = 1;

		for (int i = 0, j = 0; j < A.size(); j++) {
			// keep monotonic decreasing
			while (!max_dq.empty() and A[j] > max_dq.back())
				max_dq.pop_back();
			// keep monotonic increasing
			while (!min_dq.empty() and A[j] < min_dq.back())
				min_dq.pop_back();

			max_dq.push_back(A[j]);
			min_dq.push_back(A[j]);

			while (max_dq.front() - min_dq.front() > limit) {
				// remove A[i]. if it is in any dq, remove from those too
				if (A[i] == max_dq.front()) max_dq.pop_front();
				if (A[i] == min_dq.front()) min_dq.pop_front();
				i++;
			}

			ans = max(ans, j-i+1);
		}

		return ans;
	}
};
/*
# Why do we check only max_dq.front() / min_dq.front() to remove A[i]?
# Take max_dq as an example. In order for A[i] to be present in max_dq, 
# A[i] >= A[x], where x = i+1...j. In other words, it has to be the biggest element or 
# it would have already been removed. The biggest element would be in max_dq[0]. 
# Similar explanation applies for min_dq.



The 0 index of maxd is the maximum element, and the 0 index of mind is the minimum element.
When the maximum minus minimum exceeds the limit,
move the left boundary of the sliding window forward
and remove the corresponding element(s) from maxd and mind.
Repeat until under the limit.

if A[i] is neither equal to min_dq[0], not max_dq[0], it doesn't matter.
Nothing will be popped from either dq in this case
*/
