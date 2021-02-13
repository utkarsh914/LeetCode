// https://leetcode.com/problems/find-k-pairs-with-smallest-sums/

// same as: 378. kth-smallest-element-in-a-sorted-matrix

/*
You are given two integer arrays nums1 and nums2 sorted in ascending order and an integer k.
Define a pair (u,v) which consists of one element from the first array and one element from the second array.
Find the k pairs (u1,v1),(u2,v2) ...(uk,vk) with the smallest sums.

Example 1:

Input: nums1 = [1,7,11], nums2 = [2,4,6], k = 3
Output: [[1,2],[1,4],[1,6]] 
Explanation: The first 3 pairs are returned from the sequence: 
			 [1,2],[1,4],[1,6],[7,2],[7,4],[11,2],[7,6],[11,4],[11,6]
*/






/*
m×n matrix of sums, for example for nums1=[1,7,11], and nums2=[2,4,6]:


      2   4   6
   +------------
 1 |  3   5   7
 7 |  9  11  13
11 | 13  15  17


The previous solution right away considered (the first pair of) all matrix rows (see visualization above).
This one doesn't. It starts off only with the very first pair at the top-left corner of the matrix,
and expands from there as needed. Whenever a pair is chosen into the output result,
the next pair in the row gets added to the priority queue of current options.
Also, if the chosen pair is the first one in its row, then the first pair in the next row is added to the queue.
Here's a visualization of a possible state:

# # # # # ? . .
# # # ? . . . .
# ? . . . . . .   "#" means pair already in the output
# ? . . . . . .   "?" means pair currently in the queue
# ? . . . . . .
? . . . . . . .
. . . . . . . .

As I mentioned in the comments, that could be further improved. Two of those ? don't actually need to be in the queue yet.
I'll leave that as an exercise for the reader :-)

*/


// *********** most efficient (stefanpochman's way) **********
class Solution {
public:
	vector<vector<int>> kSmallestPairs(vector<int>& nums1, vector<int>& nums2, int k) {
		
		vector<vector<int>> result;
		priority_queue<array<int,3>, vector<array<int,3>>, greater<array<int,3>> > pq;
		if (nums1.empty() or nums2.empty()) return result;

		// push first ele of first row
		pq.push({nums1[0] + nums2[0], 0, 0});

		while (!pq.empty() && k--) {
			auto& top = pq.top();
			int i = top[1], j = top[2];
			pq.pop();
			result.push_back({nums1[i], nums2[j]});

			// push next element of curr row
			if (j+1 < nums2.size())
				pq.push({ nums1[i]+nums2[j+1], i, j+1});
			// if curr ele is the first from its row, push first ele of next row too
			if (j==0 && i+1<nums1.size()) 
				pq.push({ nums1[i+1]+nums2[j], i+1, j});
		}

		return result;
	}
};
/*
 ***** MORE EXPLANATION ON WHY ADDING NEXT ROW'S ELE NEEDS TO BE DONE ONLY WHEN CUR ELE IS FIRST ELE OF CURR ROW *****

the problem can also be viewed as finding the kth smallest element from m sorted arrays.
The 'bubbling' down process in your solution 5 can also be seen as keeping track of the smallest element in each array.
The initialization of row 0 in your matrix is equivalent to getting the pointer set up for each array -- that explains
why you don't need to push (i+1, j ) into the heap for j > 0, because the smallest element in the j column is already
in the heap, and push (i+1, j) will cause redundancy

********* also *******

We know that each row and each column is sorted, and we want to expand to the right and down.
We only need to add the down (i + 1) element when j = 0, because once that is in the heap,
we know that that is the smallest element in the entire i+1th row. When popping off the heap,
if we still haven't popped that (i+1, j=0) element, we know we can just keep going rightward in the same ith row.
(The heap obviously guarantees that we only get the min element.)

It's impossible for sum(i + 1, j) < sum(i, j) or for sum(i + 1, j + 1) < sum(i + 1, j).
*/




// it is like merging some given sorted lists
// first push first ele of each row in heap.
// Pick min ele, push next ele of that row to heap
// when we got k number of elements, stop the while loop and done
class Solution {
public:
	vector<vector<int>> kSmallestPairs(vector<int>& nums1, vector<int>& nums2, int k) {
		
		vector<vector<int>> result;
		priority_queue<array<int,3>, vector<array<int,3>>, greater<array<int,3>> > pq;
		if (nums1.empty() or nums2.empty()) return result;

		// push first ele of all rows
		for (int i=0; i < nums1.size(); i++) {
			pq.push({nums1[i] + nums2[0], i, 0});
		}

		while (!pq.empty() && k--) {
			auto& top = pq.top();
			int i = top[1], j = top[2];
			pq.pop();
			result.push_back({nums1[i], nums2[j]});

			if (j+1 < nums2.size())
				pq.push({ nums1[i]+nums2[j+1], i, j+1});
		}

		return result;
	}
};






















// ********* generate all pairs, and get top k pairs from them ******
class Solution {
public:
	vector<vector<int>> kSmallestPairs(vector<int>& nums1, vector<int>& nums2, int k) {
		priority_queue<vector<int>> pq;
		for (int n1:nums1) {
			for (int n2:nums2) {
				pq.push({n1+n2, n1, n2});
				if (pq.size() > k) pq.pop();
			}
		}

		vector<vector<int>> result;
		while (!pq.empty()) {
			auto& top = pq.top();
			result.push_back({top[1],top[2]});
			pq.pop();
		}
		return result;
	}
};