// https://leetcode.com/problems/maximum-swap/

/*
You are given an integer num.
You can swap two digits at most once
to get the maximum valued number.

Return the maximum valued number you can get.

Example 1:

Input: num = 2736
Output: 7236
Explanation: Swap the number 2 and the number 7.

Example 2:

Input: num = 9973
Output: 9973
Explanation: No swap.
 

Constraints:

0 <= num <= 108
*/





class Solution {
public:
	int maximumSwap(int num) {
		string n = to_string(num);

		unordered_map<char, int> map;
		for (int i = 0; i < n.size(); i++)
			map[n[i]] = i;

		string s = n;
		sort(s.rbegin(), s.rend());
		
		// if mismatched, swap it with the correct number
		// in case correct num has freq > 1, we use the one
		// that is present after i (storing indices in map taken care of it)
		for (int i = 0, swaps = 0; i < n.size() and swaps == 0; i++) {
			if (n[i] != s[i]) {
				swap(n[i], n[map[s[i]]]);
				swaps++;
			}
		}
		
		return stoi(n);
	}
};
/*
98368
98863

988
*/