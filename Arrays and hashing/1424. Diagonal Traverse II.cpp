// https://leetcode.com/problems/diagonal-traverse-ii/

/*
Given a list of lists of integers, nums,
return all elements of nums in diagonal order as shown in the below images.

Example 1:

Input: nums = [[1,2,3],[4,5,6],[7,8,9]]
Output: [1,4,2,7,5,3,8,6,9]

Example 2:

Input: nums = [[1,2,3,4,5],[6,7],[8],[9,10,11],[12,13,14,15,16]]
Output: [1,6,2,8,7,3,9,4,12,10,5,13,11,14,15,16]

Example 3:

Input: nums = [[1,2,3],[4],[5,6,7],[8],[9,10,11]]
Output: [1,4,2,5,3,8,6,9,7,10,11]

Example 4:

Input: nums = [[1,2,3,4,5,6]]
Output: [1,2,3,4,5,6]
 

Constraints:

1 <= nums.length <= 10^5
1 <= nums[i].length <= 10^5
1 <= nums[i][j] <= 10^9
There at most 10^5 elements in nums.
*/









/*
Notice that numbers with equal sums of row and column indexes belong to the same diagonal.
Store them in tuples (sum, row, val), sort them, and then regroup the answer.
*/
class Solution {
public:
	vector<int> findDiagonalOrder(vector<vector<int>>& A) {
		vector<int> ans; ans.reserve(100001);
		// array -> { sum(i+j), row, val }
		vector<array<int,3>> map; map.reserve(100001);

		for (int i = A.size()-1; i >= 0; --i)
			for (int j = A[i].size()-1; j >= 0; --j)
				map.push_back({ i+j, i, A[i][j]});

		sort(map.begin(), map.end(), [](auto& a, auto& b) {
			return a[0] == b[0] ? a[1] > b[1] : a[0] < b[0];
		});

		for (auto& p : map) ans.push_back(p[2]);
		return ans;
	}
};



/*
use map instead of sorting

traverse matrix from bottom -> top, right -> left
(it keeps elements of same i+j in order so we can directly add them to result, w/o sort)
*/
class Solution {
public:
	vector<int> findDiagonalOrder(vector<vector<int>>& A) {
		vector<int> ans; ans.reserve(100001);
		map<int, vector<int>> map;

		for (int i = A.size()-1; i >= 0; --i)
			for (int j = A[i].size()-1; j >= 0; --j)
				map[i+j].push_back(A[i][j]);

		for (auto& p : map)
			move(p.second.begin(), p.second.end(),
				std::back_inserter(ans));

		return ans;
	}
};







// #############  TLE  ############
class Solution {
public:
	vector<int> findDiagonalOrder(vector<vector<int>>& A) {
		vector<int> ans; ans.reserve(100001);
		int R = A.size(), C = 0;
		for (auto& r : A) C = max(C, r.size());

		for (int x = 0; x < R; x++) {
			for (int i = x, j = 0; i >= 0 and j < C; i--, j++) {
				if (j < A[i].size())
					ans.push_back(A[i][j]);
			}
		}

		for (int x = 1; x < C; x++) {
			for (int i = R-1, j = x; i >= 0 and j < C; i--, j++) {
				if (j < A[i].size())
					ans.push_back(A[i][j]);
			}
		}

		return ans;
	}
	
	int max(int x, int y) {return x>y ? x : y;}
};