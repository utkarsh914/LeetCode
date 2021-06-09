// https://leetcode.com/problems/number-of-ways-to-split-a-string/

/*
Given a binary string s (a string consisting only of '0's and '1's),
we can split s into 3 non-empty strings s1, s2, s3 (s1+ s2+ s3 = s).

Return the number of ways s can be split such that the number of characters '1'
is the same in s1, s2, and s3.

Since the answer may be too large, return it modulo 10^9 + 7.

 

Example 1:

Input: s = "10101"
Output: 4
Explanation: There are four ways to split s in 3 parts
where each part contain the same number of letters '1'.

"1|010|1"
"1|01|01"
"10|10|1"
"10|1|01"
Example 2:

Input: s = "1001"
Output: 0

Example 3:

Input: s = "0000"
Output: 3
Explanation: There are three ways to split s in 3 parts.

"0|0|00"
"0|00|0"
"00|0|0"

Example 4:

Input: s = "100100010100110"
Output: 12
 

Constraints:

3 <= s.length <= 10^5
s[i] is '0' or '1'.
*/
















/*
Approach to the solution

Following three cases arise

1. If the number of 1's is not divisible by 3
2. If the number of 1's is zero
3. If the number of 1's is divisble by 3

Case 1:
Since 1's cannot be dividede into three parts return 0;

Case 2:
Min length of array should be one, therfore number of places to cut the string is N-1,
where n is the length of the string.
Now the problem is reduced to combinations (n C r).

suppose we have to chose 2 things out of x things.
so, # of ways to chose are x C 2. [C here means combinations]
similarly, we have to chose 2 split positions out of N-1.
so ans is (N-1 C 2) = (N-1)*(N-2)/2

Alternatively,
Number of ways to keep two identical balls from N-1 different places= (N-1)*(N-2)/2;
Choose for first from n-1 and then for second we have n-2 choices.
Since objects are identical divide it by 2!. (2 = number of identical objects).
Also don't forget to mod at every step to keep it to int.

Case3:
Let number of 1's be 6;
then we divide them into 3 parts of two 1's.
Example
1 1 0 0 1 0 1 0 0 0 1 1
take cumulative freq of 1's
1 2 2 2 3 3 4 4 4 4 5 6

we want to split into 3 parts
so, first part can end at any '2',
and for every first part, 2nd part can end at any 4

here, # count of 2 = 3, # count of 4 = 4
so, total ways are the # of ways are #2 * #4 = 3*4 = 12



alternatively,
Let number of 1's be 6;
then we divide them into 3 parts of two 1's.
Example 1 1 0 0 1 0 1 0 0 0 1 1
first part can end (and second part start) from i=1 to i=3 (Why? think yourself).....section 1
similarly second part can end from (and third part start) from i=5 to i=8.....section 2
so in section 1 we have three places to partition
and in second section we have four place to partition
therefore the answer is 3*4;
*/
class Solution {
public:
	int numWays(string& s) {
		long n = s.size(), mod = 1e9+7;
		long c = count(s.begin(), s.end(), '1');
		if (c % 3 != 0) return 0;
		if (c == 0) // (n-1) C (2) [combination]
			return (((n-1)*(n-2)) / 2L) % mod;

		long first_can_end = 0, second_can_end = 0, curCount = 0;
		for (char& ch : s) {
			if (ch == '1') curCount++;
			if (curCount == c/3) first_can_end++;
			else if (curCount == (2*c)/3) second_can_end++;
		}
		return (first_can_end * second_can_end) % mod;
	}
};