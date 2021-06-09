// https://leetcode.com/problems/contains-duplicate-iii/

/*
Given an integer array nums and two integers k and t,
return true if there are two distinct indices i and j in the array such that
abs(nums[i] - nums[j]) <= t and abs(i - j) <= k.


Example 1:

Input: nums = [1,2,3,1], k = 3, t = 0
Output: true

Example 2:

Input: nums = [1,0,1,1], k = 1, t = 2
Output: true

Example 3:

Input: nums = [1,5,9,1,5,9], k = 2, t = 3
Output: false

Constraints:

0 <= nums.length <= 2 * 104
-231 <= nums[i] <= 231 - 1
0 <= k <= 104
0 <= t <= 231 - 1
*/








/*
Use already existing state to evaluate next state -
Like, a set of k sorted numbers are only needed to be tracked.
When we are processing the next number in array,
then we can utilize the existing sorted state and it is not necessary
to sort next overlapping set of k numbers again.



In my solution - 
I maintain a window of length (k+1)
for each element I find the lower bound of A[i]-t, A[i]+t

suppose A[i] = 5, t = 2

so, I search lower bound of 3. It'll give first ele >= 3
if it exists, I'll check the diff, and return if abs(diff) <= t

again, I search LB of 7. It'll give first ele >= 7
if it exists, I'll check the diff, and return if abs(diff) <= t
*/
class Solution {
public:
	bool containsNearbyAlmostDuplicate(vector<int>& A, int k, long t) {
		if (A.size() < 2 or k == 0) return false;

		set<long> s;
		s.insert(-1e15); s.insert(1e15);

		for (int i = 0; i < A.size(); i++) {
			auto lb1 = s.lower_bound(long(A[i]) - t);
			if (abs(A[i] - *lb1) <= t ) return true;
			auto lb2 = s.lower_bound(long(A[i] + t));
			if (abs(*lb2 - A[i]) <= t) return true;

			if (i >= k) s.erase(A[i-k]);
			s.insert(A[i]);
		}

		return false;
	}
};






class Solution {
	public:
	bool containsNearbyAlmostDuplicate(vector<int>& A, int k, int t) {
		vector< pair<long, int> > vec;
		for (int i = 0; i < A.size(); ++i)
			vec.push_back(make_pair(A[i], i));

		sort(vec.begin(), vec.end());

		for (int i = 0; i < A.size(); ++i) {
			int j = i + 1;
			while(j < A.size() && vec[j].first-vec[i].first <= t) {
				if (abs(vec[j].second-vec[i].second) <= k)
					return true;
				j++;
			}
		}

		return false;
	}
};