/*
https://leetcode.com/problems/k-similar-strings/

Strings A and B are K-similar (for some non-negative integer K) if we can swap the positions
of two letters in Aexactly K times so that the resulting string equals B.
Given two anagrams A and B, return the smallest K for which A and B are K-similar.

Example 1:
Input: A = "ab", B = "ba"
Output: 1

Example 2:
Input: A = "abc", B = "bca"
Output: 2

Example 3:
Input: A = "abac", B = "baca"
Output: 2

Example 4:
Input: A = "aabc", B = "abca"
Output: 2

Note:
1 <= A.length == B.length <= 20
A and B contain only lowercase letters from the set {'a', 'b', 'c', 'd', 'e', 'f'}
*/

/*

Logical Thinking
In fact, the essence of the problem is to get the minimum number of swaps A needs to make itself equal to B.

It is a shortest-path problem so we can utilize BFS.
The graph we build sets all possible strings that can be swapped from A as nodes,
and an edge exists if one string can be transformed into the other by one swap.
We start at A, and target at B.
However, that will cause TLE.

We set all possible strings that can be formed by swapping the positions of two letters in A' one time as neighbours of A',
however, only those can make A and B differ less are meaningful neighbours. That is, if A'[i] != B[i] but A'[j] == B[i],
the string formed by swap(A, i, j) is a meaningful neighbour of A'.
Please note that we just need to swap the first pair (A'[i], A'[j]) we meet because the order of swap doesn't matter.
*/
class Solution {
public:

int kSimilarity(string A, string B) {
	queue<string> q;
	unordered_set<string> vis;
	q.push(A); vis.insert(A);
	int steps=0;
	while (!q.empty()) {
		int size = q.size();
		while (size--) {
			string curr = q.front(); q.pop();
			if (curr == B) return steps;
			// push neighbors of curr (those having just one swap from curr)
			for (auto& s:getNeighbors(curr, B)) {
				if (!vis.count(s))
					q.push(s), vis.insert(s);
			}
		}
		steps++;
	}
	return -1;
}

vector<string> getNeighbors(string& A, string& B) {
	vector<string> neighbors;
	int i=0;
	while (A[i]==B[i]) i++;
	for (int j=i+1; j<A.length(); j++) {
		if (B[j] == A[i]) {
			swap(A[i], A[j]);
			neighbors.push_back(A);
			swap(A[i], A[j]); // restore previous swap
		}
	}
	return neighbors;
}};