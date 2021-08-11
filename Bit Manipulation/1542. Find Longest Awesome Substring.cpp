// https://leetcode.com/problems/find-longest-awesome-substring/

/*
Given a string s. An awesome substring is a non-empty substring of s such that we can make any number of swaps in order to make it palindrome.

Return the length of the maximum length awesome substring of s.

 

Example 1:

Input: s = "3242415"
Output: 5
Explanation: "24241" is the longest awesome substring, we can form the palindrome "24142" with some swaps.
Example 2:

Input: s = "12345678"
Output: 1
Example 3:

Input: s = "213123"
Output: 6
Explanation: "213123" is the longest awesome substring, we can form the palindrome "231132" with some swaps.
Example 4:

Input: s = "00"
Output: 2
 

Constraints:

1 <= s.length <= 10^5
s consists only of digits.
*/













/*
This is similar to 1371. Find the Longest Substring Containing Vowels in Even Counts.

We can form a palindrome if the count of each included number (expcept maybe one) is even,
and this is the property of an awesome string.

A bit in our mask is 0 if the count for the corresponding number is even,
and 1 if it's odd. As we go through the string, we track odd/even counts in our mask.
If we see the same mask again, the subarray between first poistion (exclusive)
and the current position (inclusive) with the same mask has all numbers with the even count.

We will use the dp array to track the smallest (first) position of each mask.
We can get the size of the substring by substracting it from the current poisition.

Note that position for zero mask is -1, as we need to include the very first character.

Now, the difference from #1371 is that a palindrome can have
up to one number with the odd count.
Therefore, we need to also check all masks that are different
from the current one by one bit.
In other words, if two masks are different by one bit,
that means that there is one odd count in the substring.
*/
class Solution {
public:
	int longestAwesome(string& s) {
		unordered_map<int, int> index;
		int prev = 0, ans = 1;
		index[prev] = -1;
		
		for (int i = 0; i < s.size(); i++) {
			int c = s[i] - '0';
			// toggle cth bit in prev
			prev = prev ^ (1 << c);
			if (index.count(prev))
				ans = max(ans, i - index[prev]);
			else index[prev] = i;
			// check by toggling every bit now
			// (one odd freq allowed)
			for (int k = 0; k < 10; k++) {
				int cur = prev ^ (1 << k);
				if (index.count(cur))
					ans = max(ans, i - index[cur]);
			}
		}
		
		return ans;
	}
};




int longestAwesome(string s) {
	vector<int> dp(1024, s.size());
	int ans = 0, mask = 0;
	dp[0] = -1;

	for (int i = 0; i < s.size(); ++i) {
		mask ^= 1 << (s[i] - '0');
		ans = max(ans, i - dp[mask]);
		for (int j = 0; j <= 9; ++j) {
			ans = max(ans, i - dp[mask ^ (1 << j)]);
		}
		dp[mask] = min(dp[mask], i);
	}
	return ans;
}