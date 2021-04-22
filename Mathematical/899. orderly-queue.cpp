// https://leetcode.com/problems/orderly-queue/

/*
A string S of lowercase letters is given.  Then, we may make any number of moves.

In each move, we choose one of the first K letters (starting from the left), remove it, and place it at the end of the string.

Return the lexicographically smallest string we could have after any number of moves.

 

Example 1:

Input: S = "cba", K = 1
Output: "acb"
Explanation: 
In the first move, we move the 1st character ("c") to the end, obtaining the string "bac".
In the second move, we move the 1st character ("b") to the end, obtaining the final result "acb".
*/







/*
When k > 1 you can reorder any way you like [Proof]

For any String you can move any char to anywhere if you can swap adjacent characters
For any String xxx[ab]xxx you can always do

xxx[ab]xxx
[ab]xxxxxx
xxxxxx[ba]
xxx[ba]xxx

*/
class Solution {
public:
	string orderlyQueue(string S, int K) {
		if (K > 1) {
			sort(S.begin(), S.end());
			return S;
		}
		string res = S;
		for (int i = 1; i < S.length(); i++)
			res = min(res, S.substr(i) + S.substr(0, i));
		return res;
	}
};