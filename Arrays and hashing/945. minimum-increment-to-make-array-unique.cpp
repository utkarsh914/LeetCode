// https://leetcode.com/problems/minimum-increment-to-make-array-unique/

/*
Given an array of integers A, a move consists of choosing any A[i], and incrementing it by 1.
Return the least number of moves to make every value in A unique.

Example 1:

Input: [1,2,2]
Output: 1
Explanation:  After 1 move, the array could be [1, 2, 3].
Example 2:

Input: [3,2,1,2,1,7]
Output: 6
Explanation:  After 6 moves, the array could be [3, 4, 1, 2, 5, 7].
It can be shown with 5 or less moves that it is impossible for the array to have all unique values.
*/




/*
Sort the input array.
Compared with previous number,
the current number need to be at least prev + 1.
*/
class Solution {
public:
	int minIncrementForUnique(vector<int>& A) {
		sort(A.begin(), A.end());
		int c = 0;
		for (int i=1; i<A.size(); i++) {
			if (A[i-1]>=A[i]) {
				c += A[i-1]-A[i]+1; // curr needs to be increased by diff+1 to become larger
				A[i] = A[i-1]+1; // make curr just greater than prev
			}
		}
		return c;
	}
};




/*
 ******** Union Find, O(N) *******
				Time: Amortized O(N)
						Space: O(N)
*/
class Solution {
	unordered_map<int, int> root;
public:
	int minIncrementForUnique(vector<int>& A) {
		int res = 0;
		for (int a : A)
			res += find(a) - a;
		return res;
	}
	
	int find(int x) {
		return root[x] = root.count(x) ? find(root[x] + 1) : x;
	}
};







class Solution {
public:
	int minIncrementForUnique(vector<int>& A) {
		vector<bool> s(50000, false);
		int c = 0;
		for (int n:A) {
			if (!s[n]) s[n]=true;
			else {
				int x = n+1;
				while (s[x]) x++;
				c += x-n;
				s[x] = true;
			}
		}
		return c;
	}
};