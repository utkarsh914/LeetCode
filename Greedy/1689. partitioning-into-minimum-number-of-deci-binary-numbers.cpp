// https://leetcode.com/problems/partitioning-into-minimum-number-of-deci-binary-numbers/

/*
A decimal number is called deci-binary if each of its digits is either 0 or 1 without any leading zeros. For example, 101 and 1100 are deci-binary, while 112 and 3001 are not.

Given a string n that represents a positive decimal integer, return the minimum number of positive deci-binary numbers needed so that they sum up to n.

Example 1:

Input: n = "32"
Output: 3
Explanation: 10 + 11 + 11 = 32
Example 2:

Input: n = "82734"
Output: 8
Example 3:

Input: n = "27346209830709182346"
Output: 9
*/



// ans is the max digit contained in the given number
class Solution {
public:
	int minPartitions(string& n) {
		int ans = 0;
		for (auto& c : n)
			ans = max(ans, c-'0');
		return ans;
	}
};
/*
82374 ->

72163
60512
50401
40300
30200
20100
10000
00000 = 8 steps


32 ->

21
10
00 = 3 steps



 ******** PROOF *******

Assume max digit in n is x.
Because deci-binary only contains 0 and 1,
we need at least x numbers to sum up a digit x.

Now we contruct an answer,
Take n = 135 as an example,
we initilize 5 deci-binary number with lengh = 3,
a1 = 000
a2 = 000
a3 = 000
a4 = 000
a5 = 000

For the first digit, we fill the first n[0] number with 1
For the second digit, we fill the first n[1] number with 1
For the third digit, we fill the first n[2] number with 1

So we have
a1 = 111
a2 = 011
a3 = 011
a4 = 001
a5 = 001

Finally, we have 111+11+11+1+1=135.
*/