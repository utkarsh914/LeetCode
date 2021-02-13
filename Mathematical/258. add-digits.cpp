// https://leetcode.com/problems/add-digits/


class Solution {
public:
	int addDigits(int n) {
		return ((n-1) % 9) + 1;
	}
};



class Solution {
public:
	int addDigits(int n) {
		if (n == 0) return 0;
		return n % 9 == 0 ? 9 : n % 9;
	}
};



class Solution {
public:
	int addDigits(int n) {
		while (n >= 10)
			n = getSum(n);
		return n;
	}
	
	int getSum(int n) {
		int sum = 0;
		string s = to_string(n);
		for (char c : s)
			sum += (c-'0');
		return sum;
	}
};