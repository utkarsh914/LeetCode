// https://leetcode.com/problems/reduce-array-size-to-the-half/


class Solution {
public:
	int minSetSize(vector<int>& A) {
		unordered_map<int, int> f;
		for (int n : A) f[n]++;

		vector<pair<int,int>> v(f.begin(), f.end());
		for (auto& p : v) p = {p.second, p.first};
		sort(v.rbegin(), v.rend());

		int total = A.size(), remain = A.size(), ans = 0;
		for (auto& p : v) {
			ans++;
			remain -= p.first;
			if (remain <= total/2)
				break;
		}

		return ans;
	}
};




/*
******** BUCKET SORT O(N) ********

1. Count the numbers' frequency
2. Create an array B which contains how many elements have freq i(index)
3. Count backwards, return once half size is reached.
*/
class Solution {
public:
	int minSetSize(vector<int>& A) {
		unordered_map<int, int> f;
		for (int n : A) f[n]++;

		vector<int> B(A.size()+1);
		for (auto& p : f) B[p.second]++;

		int total = A.size(), remain = A.size(), ans = 0;
		bool ansFound = false;

		for (int i = B.size()-1; i > 0 && !ansFound; i--) {
			for (int j = 0; j < B[i] && !ansFound; j++) {
				ans++;
				remain -= i;
				if (remain <= total/2)
					ansFound = true;
			}
		}

		return ans;
	}
};