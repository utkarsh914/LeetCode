// https://leetcode.com/problems/reordered-power-of-2/

/*
Starting with a positive integer N, we reorder the digits in any order
(including the original order) such that the leading digit is not zero.
Return true if and only if we can do this in a way such that the resulting number is a power of 2.

Example 1:

Input: 1
Output: true
Example 2:

Input: 10
Output: false
Example 3:

Input: 16
Output: true
Example 4:

Input: 24
Output: false
Example 5:

Input: 46
Output: true

Note:

1 <= N <= 10^9
*/


class Solution {
public:
	bool reorderedPowerOf2(int N) {
		// store all powers of 2
		vector<int> powers;
		for (int i=0; i<31; i++)
			powers.push_back(1<<i);
		
		// stores the highest power of 2 of that specific size
		unordered_map<int, int> map;
		for (int p : powers) {
			int size = to_string(p).size();
			map[size] = max(map[size], p);
		}
		
		// pick the highest pow of 2 of the size eq to size of N
		int p = map[to_string(N).size()];
		string sn = to_string(N);
		sort(sn.begin(), sn.end());
		
		// keep checking if we can rearrange p to make N
		// if not, take next lower power of 2
		while (p >= 1) {
			string sp = to_string(p);
			sort(sp.begin(), sp.end());
			if (sp == sn)
				return true;
			p /= 2;
		}
		
		return false;
	}
};







/*
counter will counter the number of digits 9876543210 in the given number.
Then I just compare counter(N) with all counter(power of 2).
1 <= N <= 10^9, so up to 8 same digits.
If N > 10^9, we can use a hash map.
*/
class Solution {
public:
	bool reorderedPowerOf2(int N) {
		long c = counter(N);
		for (int i = 0; i < 32; i++)
			if (counter(1 << i) == c) return true;
		return false;
	}

	long counter(int N) {
		long res = 0;
		for (; N; N /= 10) res += pow(10, N % 10);
		return res;
	}
};