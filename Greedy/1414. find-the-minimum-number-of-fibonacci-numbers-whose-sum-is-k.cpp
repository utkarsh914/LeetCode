// https://leetcode.com/problems/find-the-minimum-number-of-fibonacci-numbers-whose-sum-is-k/

class Solution {
public:
	int findMinFibonacciNumbers(int k) {
		vector<int> fibs {1};
		int prev = 1, cur = 1;
		while (cur <= k) {
			fibs.push_back(cur);
			int temp = cur;
			cur = cur + prev;
			prev = temp;
		}
		fibs.push_back(cur);

		int count = 0;
		while (k > 0) {
			auto itr = upper_bound(fibs.begin(), fibs.end(), k);
			k -= *(--itr);
			count++;
		}
		
		return count;
	}
};




	int findMinFibonacciNumbers(int k) {
		if (k < 2) return k;
		int a = 1, b = 1;
		while (b <= k) {
			swap(a, b);
			b += a;
		}
		return 1 + findMinFibonacciNumbers(k - a);
	}