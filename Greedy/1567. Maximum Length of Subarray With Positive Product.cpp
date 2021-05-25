// https://leetcode.com/problems/maximum-length-of-subarray-with-positive-product/





/*
whenevr we encounter '0', we reset our values (new subarray starts after it)

we only need to know the index of first negative element,
and need to keep a running count of total
negative elements found in the current subarray.

if the count is count is even, we consider the whole subarray
i.e. length = i - start

else if count is odd, we remove the first negative element (firstNeg)
of cur subarray.
i.e. length = i - firstNeg;
*/
class Solution {
public:
	int getMaxLen(vector<int>& A) {
		int start = -1, firstNeg = -1, ans = 0;

		for (int i = 0, count = 0; i < A.size(); i++) {
			// reset values when '0' comes
			if (A[i] == 0) count = 0, start = firstNeg = i;
			else if (A[i] < 0) count++;

			if (count % 2 == 0) {
				ans = max(ans, i - start);
			} else {
				// if first negative hasn't been found yet
				if (firstNeg == start) firstNeg = i;
				ans = max(ans, i - firstNeg);
			}
		}

		return ans;
	}
};







class Solution {
public:
	int getMaxLen(vector<int>& A) {
		unordered_map<int, int> m;
		m[0] = -1;
		int ans = 0;

		for (int i = 0, neg = 0; i < A.size(); i++) {
			if (A[i] < 0) neg++;
			else if (A[i] == 0) {
				neg = 0;
				m.clear();
			}

			if (!m.count(neg)) m[neg] = i;

			if (neg % 2 == 0)
				ans = max(ans, i - m[0]);
			else
				ans = max(ans, i - m[1]);
		}

		return ans;
	}
};