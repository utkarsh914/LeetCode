// https://leetcode.com/problems/minimum-difference-between-largest-and-smallest-value-in-three-moves/

/*
Given an array nums, you are allowed to choose one element of nums
and change it by any value in one move.

Return the minimum difference between the largest and smallest
value of nums after perfoming at most 3 moves.


Example 1:

Input: nums = [5,3,2,4]
Output: 0
Explanation: Change the array [5,3,2,4] to [2,2,2,2].
The difference between the maximum and minimum is 2-2 = 0.
Example 2:

Input: nums = [1,5,0,10,14]
Output: 1
Explanation: Change the array [1,5,0,10,14] to [1,1,0,1,1]. 
The difference between the maximum and minimum is 1-0 = 1.
*/








/*
Intuition
If we can do 0 move, return max(A) - min(A)
If we can do 1 move, return min(the second max(A) - min(A), the max(A) - second min(A))
and so on.


Explanation
We have 4 plans:

kill 3 biggest elements
kill 2 biggest elements + 1 smallest elements
kill 1 biggest elements + 2 smallest elements
kill 3 smallest elements
*/
class Solution {
public:
	int minDifference(vector<int>& A) {
		int n = A.size();
		if (n < 5) return 0;
		sort(A.begin(), A.end());
		return min({A[n-1] - A[3], A[n-2] - A[2], A[n-3] - A[1], A[n-4] - A[0]});
	}
};




int minDifference(vector<int>& A) {
	int n = A.size();
	if (n < 5) return 0;
	partial_sort(A.begin(), A.begin() + 4, A.end());
	nth_element(A.begin() + 4, A.end() - 4, A.end());
	sort(A.end() - 4, A.end());
	return min({A[n-1] - A[3], A[n-2] - A[2], A[n-3] - A[1], A[n-4] - A[0]});
}
