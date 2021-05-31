// https://leetcode.com/problems/minimum-operations-to-make-a-subsequence/

/*
You are given an array target that consists of distinct integers
and another integer array arr that can have duplicates.

In one operation, you can insert any integer at any position in arr.
For example, if arr = [1,4,1,2], you can add 3 in the middle
and make it [1,4,3,1,2]. Note that you can insert the integer
at the very beginning or end of the array.

Return the minimum number of operations needed to make target a subsequence of arr.

A subsequence of an array is a new array generated from the original array
by deleting some elements (possibly none) without changing the
remaining elements' relative order.
For example, [2,7,4] is a subsequence of [4,2,3,7,2,1,4] (the underlined elements),
while [2,4,2] is not.

 

Example 1:

Input: target = [5,1,3], arr = [9,4,2,3,4]
Output: 2
Explanation: You can add 5 and 1 in such a way that makes arr = [5,9,4,1,2,3,4],
then target will be a subsequence of arr.
Example 2:

Input: target = [6,4,8,1,3,2], arr = [4,7,6,2,3,8,6,1]
Output: 3
 

Constraints:

1 <= target.length, arr.length <= 105
1 <= target[i], arr[i] <= 109
target contains no duplicates.
*/










/*
The problem can be reduced to computing Longest Common Subsequence between both arrays.

Since one of the arrays has distinct elements,
we can consider that these elements describe an arrangement of numbers,
and we can replace each element in the other array
with the index it appeared at in the first array.

Then the problem is converted to finding Longest Increasing Subsequence
in the second array, which can be done in O(n log n).

Note: We don't consider the elements of arr which don't appear in target.
*/
class Solution {
public:
	int minOperations(vector<int>& target, vector<int>& A) {
		unordered_map<int, int> map;
		for (int i = 0; i < target.size(); i++)
			map[target[i]] = i;

		vector<int> B;
		for (int& n : A)
			if (map.count(n))
				B.push_back(map[n]);

		// find LIS now
		vector<int> temp;
		for (int& n : B) {
			auto i = lower_bound(temp.begin(), temp.end(), n);
			if (i == temp.end()) temp.push_back(n);
			else *i = n;
		}

		return target.size() - temp.size();
	}
};





// optimized space
// don't create a duplicate B array, modify A only
class Solution {
public:
	int minOperations(vector<int>& target, vector<int>& A) {
		unordered_map<int, int> map;
		for (int i = 0; i < target.size(); i++)
			map[target[i]] = i;

		int ind = 0;
		for (int& n : A)
			if (map.count(n))
				A[ind++] = map[n];

		// find LIS now
		vector<int> temp;
		for (int i = 0; i < ind; i++) {
			auto itr = lower_bound(temp.begin(), temp.end(), A[i]);
			if (itr == temp.end()) temp.push_back(A[i]);
			else *itr = A[i];
		}

		return target.size() - temp.size();
	}
};





// no need to modify arr even.
class Solution {
public:
	int minOperations(vector<int>& target, vector<int>& A) {
		unordered_map<int, int> map;
		for (int i = 0; i < target.size(); i++)
			map[target[i]] = i;

		// find LIS now
		vector<int> temp;
		for (int n : A) {
			if (!map.count(n)) continue;
			n = map[n];
			auto itr = lower_bound(temp.begin(), temp.end(), n);
			if (itr == temp.end()) temp.push_back(n);
			else *itr = n;
		}

		return target.size() - temp.size();
	}
};