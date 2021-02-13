
/*
https://leetcode.com/problems/beautiful-array/
*/

class Solution {
public:
	vector<int> beautifulArray(int N) {
		vector<int> v = {1};
		while (v.size() < N) {
			vector<int> temp;
			for (int i:v) temp.push_back(2*i-1);
			for (int i:v) temp.push_back(2*i);
			v = temp;
		}
		vector<int> temp;
		for (int i:v) if (i<=N) temp.push_back(i);
		return temp;
	}
};

/*
******************** EXPLANATION ******************

Intuition:
Try to divide and conquer,
so we have left part, right part.

One way is to divide into [1, N / 2] and [N / 2 + 1, N].
But it will cause problems when we merge them.

Another way is to divide into odds part and evens part.
So there is no k with A[k] * 2 = odd + even

I brute force all permutations when N = 5:
20 beautiful array found,
only 4 don't fit odd + even pattern:
[2, 1, 4, 5, 3]
[3, 1, 2, 5, 4]
[3, 5, 4, 1, 2]
[4, 5, 2, 1, 3]


Beautiful Array Properties
Saying that an array is beautiful,
there is no i < k < j,
such that A[k] * 2 = A[i] + A[j]

Apply these 3 following changes a beautiful array,
we can get a new beautiful array


1. Deletion
Easy to prove.

2. Addition
If we have A[k] * 2 != A[i] + A[j],
(A[k] + x) * 2 = A[k] * 2 + 2x != A[i] + A[j] + 2x = (A[i] + x) + (A[j] + x)

E.g: [1,3,2] + 1 = [2,4,3].

3. Multiplication
If we have A[k] * 2 != A[i] + A[j],
for any x != 0,
(A[k] * x) * 2 = A[k] * 2 * x != (A[i] + A[j]) * x = (A[i] * x) + (A[j] * x)

E.g: [1,3,2] * 2 = [2,6,4]


Explanation
With the observations above, we can easily construct any beautiful array.
Assume we have a beautiful array A with length N

A1 = A * 2 - 1 is beautiful with only odds from 1 to N * 2 -1
A2 = A * 2 is beautiful with only even from 2 to N * 2
B = A1 + A2 beautiful array with length N * 2

E.g:

A = [2, 1, 4, 5, 3]
A1 = [3, 1, 7, 9, 5]
A2 = [4, 2, 8, 10, 6]
B = A1 + A2 = [3, 1, 7, 9, 5, 4, 2, 8, 10, 6]

Time Complexity:
I have iteration version here O(N)
Naive recursion is O(NlogN)
Recursion with one call or with cache is O(N)
*/