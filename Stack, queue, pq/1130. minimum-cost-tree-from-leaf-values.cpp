
// https://leetcode.com/problems/minimum-cost-tree-from-leaf-values/

/*
Given an array arr of positive integers, consider all binary trees such that:

Each node has either 0 or 2 children;
The values of arr correspond to the values of each leaf in an in-order traversal of the tree.  (Recall that a node is a leaf if and only if it has 0 children.)
The value of each non-leaf node is equal to the product of the largest leaf value in its left and right subtree respectively.
Among all possible binary trees considered, return the smallest possible sum of the values of each non-leaf node.  It is guaranteed this sum fits into a 32-bit integer.

Example 1:

Input: arr = [6,2,4]
Output: 32
Explanation:
There are two possible trees.  The first has non-leaf node sum 36, and the second has non-leaf node sum 32.

	24			24
   /  \		  /  \
  12   4		6	8
 /  \			   / \
6	2			 2   4

Constraints:
2 <= arr.length <= 40
1 <= arr[i] <= 15
It is guaranteed that the answer fits into a 32-bit signed integer (ie. it is less than 2^31).
*/

/*
This is not a dp problem at all.

Because dp solution test all ways to build up the tree,
including many unnecessay tries.
Honestly speaking, it's kinda of brute force.
Yes, brute force testing, with memorization.


Intuition
Let's review the problem again.

When we build a node in the tree, we compared the two numbers a and b.
In this process,
the smaller one is removed and we won't use it anymore,
and the bigger one actually stays.

The problem can translated as following:
Given an array A, choose two neighbors in the array a and b,
we can remove the smaller one min(a,b) and the cost is a * b.
What is the minimum cost to remove the whole array until only one left?

To remove a number a, it needs a cost a * b, where b >= a.
So a has to be removed by a bigger number.
We want minimize this cost, so we need to minimize b.

b has two candidates, the first bigger number on the left,
the first bigger number on the right.

The cost to remove a is a * min(left, right).


Solution 1
With the intuition above in mind,
the explanation is short to go.

We remove the element form the smallest to bigger.
We check the min(left, right),
For each element a, cost = min(left, right) * a

Time O(N^2)
Space O(N)

Python

	def mctFromLeafValues(self, A):
		res = 0
		while len(A) > 1:
			i = A.index(min(A))
			res += min(A[i - 1:i] + A[i + 1:i + 2]) * A.pop(i)
		return res

Solution 2: Stack Soluton
we decompose a hard problem into reasonable easy one:
Just find the next greater element in the array, on the left and one right.
Refer to the problem 503. Next Greater Element II


Time O(N) for one pass
Space O(N) for stack in the worst cases
stack is monotonic decreasing (strictly)
*/

class Solution {
public:
	int mctFromLeafValues(vector<int>& arr) {
		vector<int> s = {INT_MAX};
		int cost=0;
		for (int n:arr) {
			while (s.back()<=n) {
				int m = s.back();
				s.pop_back();
				cost += m * min(s.back(), n);
			}
			s.push_back(n);
		}
		for (int i=2; i<s.size(); i++)
			cost += s[i-1]*s[i];
		return cost;
	}
};