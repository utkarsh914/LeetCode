// https://leetcode.com/problems/sum-of-mutated-array-closest-to-target/

/*
Given an integer array arr and a target value target,
return the integer value such that when we change all the integers
larger than value in the given array to be equal to value,
the sum of the array gets as close as possible (in absolute difference) to target.

In case of a tie, return the minimum such integer.

Notice that the answer is not neccesarilly a number from arr.

 

Example 1:

Input: arr = [4,9,3], target = 10
Output: 3
Explanation: When using 3 arr converts to [3, 3, 3] which sums 9
and that's the optimal answer.
Example 2:

Input: arr = [2,3,5], target = 10
Output: 5
Example 3:

Input: arr = [60864,25176,27249,21296,20204], target = 56803
Output: 11361
 

Constraints:

1 <= arr.length <= 104
1 <= arr[i], target <= 105
*/











/*
If you draw a graph with the value on one axis
and the absolute difference between the target and the array sum, what will you get?
That graph is uni-modal.
Use ternary search on that graph to find the best value.

the diff array for increasing value of val is
[5 4 3 2 1 2 3 4 5]

so, to find the min diff, we need to find the first point of valley in the mountain.
so, we BS and compare two adjacent diffs to check if it is the valley
let diff array is [5 4 3 2 0 0 2 3 4 5],
so we should return the index (val) of first '0'
*/
class Solution {
public:
	int findBestValue(vector<int>& A, int target) {
		int N = A.size(), ans = 0, diff = INT_MAX;
		sort(A.begin(), A.end());
		// prefix sum to find current mutated sum in lesser time
		vector<int> sum = A;
		for (int i = 1; i < N; i++)
			sum[i] += sum[i-1];

		int lo = 0, hi = *max_element(A.begin(), A.end());
		while (lo <= hi) {
			int m1 = lo + (hi - lo) / 2, m2 = m1+1;
			int diff1 = abs(target - getCurSum(A, sum, m1));
			int diff2 = abs(target - getCurSum(A, sum, m2));
			
			if (diff2 < diff1)
				ans = m2, lo = m2;
			else hi = m1 - 1;
		}

		return ans;
	}

	int getCurSum(vector<int>& A, vector<int>& sum, int k) {
		int ub = upper_bound(A.begin(), A.end(), k) - A.begin();
		int prevPreSum = ub > 0 ? sum[ub-1] : 0;
		int nextSum = k * (A.size() - ub);
		return prevPreSum + nextSum;
	}
};




// same as above. just don't sort the array, and no presum
class Solution {
public:
	int findBestValue(vector<int>& A, int target) {
		int N = A.size(), ans = 0, diff = INT_MAX;
		int lo = 0, hi = *max_element(A.begin(), A.end());

		// find the valley using BS
		while (lo <= hi) {
			int m1 = lo + (hi - lo) / 2;
			int m2 = m1 + 1;
			int diff1 = abs(target - getMutatedSum(A, m1));
			int diff2 = abs(target - getMutatedSum(A, m2));
			
			if (diff2 < diff1)
				ans = m2, lo = m2;
			else hi = m1 - 1;
		}

		return ans;
	}

	int getMutatedSum(vector<int>& A, int k) {
		int sum = 0;
		for (int a : A)
			sum += (a > k) ? k : a;
		return sum;
	}
};









// less intuitive but bit faster
class Solution {
public:
	int findBestValue(vector<int>& A, int target) {
		int sum = accumulate(A.begin(), A.end(), 0);
		int lo = 0, hi = *max_element(A.begin(), A.end());
		if (sum == target) return hi;

		int ans = 1, diff = INT_MAX;
		// The answer would lie between 0 and maximum value in the array.
		while (lo <= hi) {
			int mid = lo + (hi - lo) / 2;
			sum = getMutatedSum(A, mid);
			if (sum > target)
				hi = mid - 1;
			else
				lo = mid + 1;
			
			// If current difference is less than diff ||
			// current difference==diff but mid < ans.(choose the smaller one.)
			if (abs(sum - target) < diff or
				(abs(sum - target) == diff and mid < ans)) {
				ans = mid;
				diff = abs(sum - target);
			}
		}

		return ans;
	}

	int getMutatedSum(vector<int>& A, int k) {
		int sum = 0;
		for (int a : A)
			sum += (a > k) ? k : a;
		return sum;
	}
};
