// https://leetcode.com/problems/advantage-shuffle/

/*
Given two arrays A and B of equal size,
the advantage of A with respect to B is the number of indices i for which A[i] > B[i].
Return any permutation of A that maximizes its advantage with respect to B.

Example 1:

Input: A = [2,7,11,15], B = [1,10,4,11]
Output: [2,11,7,15]
*/

class Solution {
public:
	vector<int> advantageCount(vector<int>& A, vector<int>& Bvec) {
		vector<array<int,3>> B(Bvec.size());
		for (int i=0; i < Bvec.size(); i++) {
			B[i] = {Bvec[i], i, -1};
		}
		// sort A, B
		sort(A.begin(), A.end());
		sort(B.begin(), B.end());

		vector<bool> taken(A.size(), false);
		int i=A.size()-1, j=i;

		while (i>=0 && j>=0) {
			while (j >= 0 && A[i] <= B[j][0]) j--;
			if (j < 0) break;
			B[j][2] = A[i];
			taken[i] = true;
			i--, j--;
		}

		for (int i=0, j=0; i < taken.size(); i++) {
			if (taken[i]) continue;
			while (B[j][2] != -1) j++;
			B[j][2] = A[i];
		}

		vector<int> ans(A.size());
		for (auto& a : B) {
			ans[a[1]] = a[2];
		}

		return ans;
	}
};







/*
For each B[i], we select the smallest number in A that is greater than B[i].
If there are no such number, we select the smalest number in A.

I am usign multiset to sort and keep track of numbers in A.
After a number is selected, we need to remove it from the multiset
(erase by iterator takes a constant time).
*/

vector<int> advantageCount(vector<int>& A, vector<int>& B) {
	multiset<int> s(begin(A), end(A));
	for (auto i = 0; i < B.size(); ++i) {
		auto p = s.upper_bound(B[i]);
		if(p == s.end()) p =s.begin();
		A[i] = *p;
		s.erase(p);
	}
	return A;
}