// https://leetcode.com/problems/distinct-subsequences-ii/

/*
Given a string s, return the number of distinct non-empty subsequences of s. Since the answer may be very large, return it modulo 109 + 7.

A subsequence of a string is a new string that is formed from the original string by deleting some (can be none) of the characters without disturbing the relative positions of the remaining characters. (i.e., "ace" is a subsequence of "abcde" while "aec" is not.
 

Example 1:

Input: s = "abc"
Output: 7
Explanation: The 7 distinct subsequences are "a", "b", "c", "ab", "ac", "bc", and "abc".
Example 2:

Input: s = "aba"
Output: 6
Explanation: The 7 distinct subsequences are "a", "b", "c", "ab", "ac", "bc", and "abc".
Example 3:

Input: s = "aaa"
Output: 3
Explanation: The 3 distinct subsequences are "a", "aa" and "aaa".
 

Constraints:

1 <= s.length <= 2000
s consists of lowercase English letters.
*/






/*
Explanation
Init an array endswith[26]
endswith[i] to count how many sub sequence that ends with ith character.

Now we have N = sum(endswith) different sub sequence,
add a new character c to each of them,
then we have N different sub sequence that ends with c.

With this idea, we loop on the whole string S,
and we update end[c] = sum(end) + 1 for each character.

We need to plus one here, because "c" itself is also a sub sequence.

Example
Input: "aba"
Current parsed: "ab"

endswith 'a': ["a"]
endswith 'b': ["ab","b"]

"a" -> "aa"
"ab" -> "aba"
"b" -> "ba"
"" -> "a"

endswith 'a': ["aa","aba","ba","a"]
endswith 'b': ["ab","b"]
result: 6

Complexity
Time O(26N), Space O(1).
*/
int distinctSubseqII(string& S) {
	long endsWith[26] = {}, mod = 1e9 + 7;
	for (char c : S) {
		endsWith[c - 'a'] = accumulate(endsWith, endsWith+26, 1L) % mod;
	}
	return accumulate(endsWith, endsWith+26, 0L) % mod;
}








/*
The idea is that the next character doubles the running count.
If it's a repeated character,
we also need to substract the previous count for that character.
*/
int distinctSubseqII(string& s) {
	long endsWith[128] = {}, dp[N];
	long N = s.size(), mod = 1e9+7;
	dp[0] = 1;
	endsWith[s[0]] = 1;
	
	for (int i = 1; i < N; i++) {
		dp[i] = dp[i-1] * 2L + 1L; // find all subseq using prev state
		dp[i] -= endsWith[s[i]]; // subtract duplicate subsequences
		if (dp[i] < 0) dp[i] += mod;
		dp[i] %= mod;
		// no. of subseq which were extended by ch to end with ch
		endsWith[s[i]] = (1L + dp[i-1]) % mod;
	}
	
	return dp[N-1];
}