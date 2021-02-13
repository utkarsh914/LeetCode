// https://leetcode.com/problems/kth-smallest-element-in-a-sorted-matrix/


/*
Given a n x n matrix where each of the rows and columns are sorted in ascending order,
find the kth smallest element in the matrix.
Note that it is the kth smallest element in the sorted order, not the kth distinct element.

Example:

matrix = [
   [ 1,  5,  9],
   [10, 11, 13],
   [12, 13, 15]
],
k = 8,

return 13.
*/




/*
The key point for any binary search is to figure out the "Search Space".
For me, I think there are two kind of "Search Space" -- index and range(the range from the smallest number
to the biggest number). Most usually, when the array is sorted in one direction, we can use index as "search space",
when the array is unsorted and we are going to find a specific number, we can use "range".

Let me give you two examples of these two "search space"
index -- A bunch of examples -- https://leetcode.com/problems/find-minimum-in-rotated-sorted-array/ ( the array is sorted)
range -- https://leetcode.com/problems/find-the-duplicate-number/ (Unsorted Array)

The reason why we did not use index as "search space" for this problem is the matrix is sorted in two directions,
we can not find a linear way to map the number and its index.
*/

// using binary search O(log(X) * nlog(n)) where X is highest element
class Solution {
public:
	int kthSmallest(vector<vector<int>>& m, int k) {

		int n = m.size();
		int lo = m[0][0], hi = m[n-1][n-1];

		// make sure to handle duplicates too
		while (lo <= hi) {
			int mid = lo + (hi-lo)/2;
			int count = countLessThanEqual(m, mid);
			if (count < k) lo = mid+1;
			else hi = mid-1;
		}

		return lo; // lo is always an ele from array
	}

	// counts in log(n) time
	int countLessThanEqual(vector<vector<int>>& m, int x) {
		int count = 0, j = m[0].size()-1;
		for (int i=0; i<m.size(); i++) {
			while (j>=0 && m[i][j]>x) j--;
			count += j+1;
		}
		return count;
	}

	// counts in nlog(n) time
	int countLessThanEqual_(vector<vector<int>>& m, int x) {
		int count = 0;
		for (int i=0; i<m.size(); i++) {
			auto itr = upper_bound(m[i].begin(), m[i].end(), x);
			count += itr - m[i].begin();
		}
		return count;
	}
};
/*
 If mid is an int, then after several times of back and forth, it will finally stop at an element in that matrix,
 otherwise the mid calculation will keep going.
*/






// same as: 373. find-k-pairs-with-smallest-sums (for approach 1, using min heap)
// see sol of 373 for detailed explanation of algo

class Solution {
public:
	int kthSmallest(vector<vector<int>>& m, int k) {

		priority_queue<array<int,3>, vector<array<int,3>>, greater<array<int,3>> > pq;
		int result = m[0][0];

		// push first ele of first row
		pq.push({m[0][0], 0, 0});

		while (!pq.empty() && k--) {
			auto& top = pq.top();
			int i = top[1], j = top[2];
			result = m[i][j];
			pq.pop();

			// push next element of curr row
			if (j+1 < m[0].size())
				pq.push({ m[i][j+1], i, j+1});
			// if curr ele is the first from its row, push first ele of next row too
			if (j==0 && i+1<m.size()) 
				pq.push({ m[i+1][j], i+1, j});
		}

		return result;
	}
};