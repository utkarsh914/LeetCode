/*
N couples sit in 2N seats arranged in a row and want to hold hands. We want to know the minimum number of swaps so that every couple is sitting side by side. A swap consists of choosing any two people, then they stand up and switch seats.

The people and seats are represented by an integer from 0 to 2N-1, the couples are numbered in order, the first couple being (0, 1), the second couple being (2, 3), and so on with the last couple being (2N-2, 2N-1).

The couples' initial seating is given by row[i] being the value of the person who is initially sitting in the i-th seat.

Example 1:

Input: row = [0, 2, 1, 3]
Output: 1
Explanation: We only need to swap the second (row[1]) and third (row[2]) person.
Example 2:

Input: row = [3, 2, 0, 1]
Output: 0
Explanation: All couples are already seated side by side.
*/



// Say there are N two-seat couches. For each couple,
// draw an edge from the couch of one partner to the couch of the other partner.
// simply count the number of joins needed to group all the couples
// or even simply return (N - number of connected components)
// source: https://leetcode.com/problems/couples-holding-hands/discuss/117520/Java-union-find-easy-to-understand-5-ms

class Solution {
public:
class UnionFind {
	// vector<int> p;
	int* p;
public:
	UnionFind(int n) {
		// p.resize(n+1,0);
		p = new int[n+1];
		for (int i=0; i<=n; i++) p[i]=i;
	}
	int find(int x) {
		if (p[x]==x) return p[x];
		return	p[x]=find(p[x]);
	}
	bool join(int x, int y) {
		x=find(x), y=find(y);
		if (x!=y)	{p[y]=x; return true;}
		return false;
	}
};

int minSwapsCouples(vector<int>& row) {
	UnionFind uf(row.size()/2);
	int count=0;
	unordered_map<int,int> ind;
	for (int i=0; i<row.size(); i++) {
		ind[row[i]] = i;
	}
	// create unions
	for (int i=0; i<row.size(); i+=2) {
		int a=row[i], b=row[i+1];
		int pair_a = (a%2==1) ? ind[a-1] : ind[a+1];
		int pair_b = (b%2==1) ? ind[b-1] : ind[b+1];
		count += uf.join(i/2,pair_a/2); //for first person
		count += uf.join(i/2,pair_b/2); //for second person
	}
	return count;
}};