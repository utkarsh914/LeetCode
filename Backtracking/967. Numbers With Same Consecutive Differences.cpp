// https://leetcode.com/problems/numbers-with-same-consecutive-differences/

class Solution {
	vector<int> ans;
	string cur;
public:
	vector<int> numsSameConsecDiff(int n, int k) {
		for (int i = 1; i <= 9; i++) {
			cur = to_string(i);
			recur(n-1, k);
		}
		return ans;
	}

	void recur(int n, int k) {
		if (n == 0) {
			ans.push_back(stoi(cur));
			return;
		}

		if (k == 0) {
			cur += cur.back();
			recur(n-1, k);
			cur.pop_back();
		}
		else {
			if (cur.back() + k <= '9') {
				cur += char(cur.back() + k);
				recur(n-1, k);
				cur.pop_back();
			}
			if (cur.back() - k >= '0') {
				cur += char(cur.back() - k);
				recur(n-1, k);
				cur.pop_back();
			}
		}
	}

};