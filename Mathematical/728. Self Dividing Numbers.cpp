// https://leetcode.com/problems/self-dividing-numbers/

class Solution {
public:
	vector<int> selfDividingNumbers(int left, int right) {
		vector<int> ans;
		for (int n = left; n <= right; n++)
			if (isSelfDividing(n)) ans.push_back(n);
		return ans;
	}

	bool isSelfDividing(int N) {
		int x = N;
		while (x) {
			int d = x % 10;
			if (d == 0 or (N % d != 0))
				return false;
			x /= 10;
		}
		return true;
	}

};