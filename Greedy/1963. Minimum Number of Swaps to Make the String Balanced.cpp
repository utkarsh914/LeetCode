// https://leetcode.com/problems/minimum-number-of-swaps-to-make-the-string-balanced/

/*
You are given a 0-indexed string s of even length n. The string consists of exactly n / 2 opening brackets '[' and n / 2 closing brackets ']'.

A string is called balanced if and only if:

It is the empty string, or
It can be written as AB, where both A and B are balanced strings, or
It can be written as [C], where C is a balanced string.
You may swap the brackets at any two indices any number of times.

Return the minimum number of swaps to make s balanced.

 

Example 1:

Input: s = "][]["
Output: 1
Explanation: You can make the string balanced by swapping index 0 with index 3.
The resulting string is "[[]]".
Example 2:

Input: s = "]]][[["
Output: 2
Explanation: You can do the following to make the string balanced:
- Swap index 0 with index 4. s = "[]][[]".
- Swap index 1 with index 5. s = "[[][]]".
The resulting string is "[[][]]".
Example 3:

Input: s = "[]"
Output: 0
Explanation: The string is already balanced.
 

Constraints:

n == s.length
2 <= n <= 106
n is even.
s[i] is either '[' or ']'.
The number of opening brackets '[' equals n / 2, and the number of closing brackets ']' equals n / 2.
*/





/*
Intuition:

We can remove the balanced components from our input string
as they will not matter in balancing the string.
Now, after removing them,
we will find that all the unbalanced brackets look like this:

]]]]]…..[[[[[…..

Now, since we can swap any brackets,
the optimal approach is to balance 2 sets of brackets at a time.
Take this for example:

        ] ] ] ] ] ] [ [ [ [ [ [
swap1:  ] ] ] ] [ ] [ ] [ [ [ [
swap2:  ] ] [ ] [ ] [ ] [ ] [ [
swap3:  [ ] [ ] [ ] [ ] [ ] [ ]

So, following this, we will notice a pattern:

swaps :     0,1,1,2,2,3,3,4...
mismatches: 0,1,2,3,4,5,6,7...

So, our result = (mismatches + 1) / 2

The key here is to start balancing from the middle.
*/
class Solution {
public:
	int minSwaps(string s) {
		int stack = 0, mismatch = 0;

		for(int i = 0; i < s.size(); i++) {
			if(s[i] == '[') stack++;
			else if (stack > 0) stack--;
			else mismatch++;
		}

		return (mismatch + 1) / 2;
	}
};
/*
Traverse the input s, remove all [] and the remaining must be ]]]...[[[. Otherwise, there would be [] among them.

For every 2 pairs of square brackets, a swap will make them balanced;
If only 1 pair not in balance, we need a swap.
Therefore, we need at least (pairs + 1) / 2 swaps
*/








//  --------- my solution -----------
/*
we validate from the end, and whenever there is a misplaced bracket,
we stop. (i.e. our 'r' variable always points the the index
with which we can swap the next mismatch which we find from the beginning)

we start checking from the beginning, in case of a mismatch,
we swap it from 'r', then again we validate from right side
until we find another misplaced bracker, and r stops at it.

In place of stack, I have used lStack and rStack variables to simulate
left and right stacks and keep the space complexity constant.
*/


	int minSwaps(string s) {
		int lStack = 0, rStack = 0, swaps = 0;
		int l = 0, r = s.size()-1;
		while (r >= 0) {
			if (s[r] == ']') rStack++;
			else if (rStack > 0) rStack--;
			else if (rStack == 0) break;
			r--;
		}
		
		for (l = 0; l < s.size(); l++) {
			if (s[l] == '[') lStack++;
			else if (lStack > 0) lStack--;
			else if (lStack == 0) {
				swap(s[l], s[r]);
				swaps++;
				lStack++;
				while (r >= 0) {
					if (s[r] == ']') rStack++;
					else if (rStack > 0) rStack--;
					else if (rStack == 0) break;
					r--;
				}
			}
		}
		
		return swaps;
	}