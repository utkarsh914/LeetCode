// https://leetcode.com/problems/roman-to-integer/

class Solution {
public:
	int romanToInt(string& s) {
		int ans = val(s.back()), prev = ans;
		for (int i = s.size()-2; i >= 0; i--) {
			int v = val(s[i]);
			if (v >= prev)
				ans += v, prev = v;
			else
				ans -= v;
		}
		return ans;
	}

	int val(char c) {
		switch (c) {
			case 'M': return 1000;
			case 'D': return 500;
			case 'C': return 100;
			case 'L': return 50;
			case 'X': return 10;
			case 'V': return 5;
			case 'I': return 1;
			default: return 0;
		}
		return 0;
	}
};