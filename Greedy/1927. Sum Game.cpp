// https://leetcode.com/problems/sum-game/

/*
Alice and Bob take turns playing a game, with Alice starting first.

You are given a string num of even length consisting of digits and '?' characters. On each turn, a player will do the following if there is still at least one '?' in num:

Choose an index i where num[i] == '?'.
Replace num[i] with any digit between '0' and '9'.
The game ends when there are no more '?' characters in num.

For Bob to win, the sum of the digits in the first half of num must be equal to the sum of the digits in the second half. For Alice to win, the sums must not be equal.

For example, if the game ended with num = "243801", then Bob wins because 2+4+3 = 8+0+1. If the game ended with num = "243803", then Alice wins because 2+4+3 != 8+0+3.
Assuming Alice and Bob play optimally, return true if Alice will win and false if Bob will win.

 

Example 1:

Input: num = "5023"
Output: false
Explanation: There are no moves to be made.
The sum of the first half is equal to the sum of the second half: 5 + 0 = 2 + 3.
Example 2:

Input: num = "25??"
Output: true
Explanation: Alice can replace one of the '?'s with '9' and it will be impossible for Bob to make the sums equal.
Example 3:

Input: num = "?3295???"
Output: false
Explanation: It can be proven that Bob will always win. One possible outcome is:
- Alice replaces the first '?' with '9'. num = "93295???".
- Bob replaces one of the '?' in the right half with '9'. num = "932959??".
- Alice replaces one of the '?' in the right half with '2'. num = "9329592?".
- Bob replaces the last '?' in the right half with '7'. num = "93295927".
Bob wins because 9 + 3 + 2 + 9 = 5 + 9 + 2 + 7.
 

Constraints:

2 <= num.length <= 105
num.length is even.
num consists of only digits and '?'.
*/







// the difference between the number of question marks
// on the left and right side matter

class Solution {
public:
	bool sumGame(string& s) {
		// count sum, number of '?' on left and right sides
		int left_sum = 0, left_q = 0, right_sum = 0, right_q = 0;

		for (int i = 0; i < s.size()/2; i++) {
			if (s[i] == '?') left_q++;
			else left_sum += (s[i] - '0');
		}
		for (int i = s.size()/2; i < s.size(); i++) {
			if (s[i] == '?') right_q++;
			else right_sum += (s[i] - '0');
		}
		
		// get the difference of sums and count of '?' of both sides
		int d = left_sum - right_sum, q = left_q - right_q;
		if (q == 0) return d != 0;
		
		/*
		if same side has larger sum and more number of '?'
		then it is impossible to reduce the difference
		*/
		if (d > 0 == q > 0) return true;
		
		d = abs(d), q = abs(q);
		/*
		bob can win only if diff is a multiple of 9,
		and there are enough '?' to let him increase the sum to required.
		
		AND, Alice should NOT get more turns than bob.
		i.e. q should be even (bcz Alice starts first)
		*/
		if (d % 9 == 0 and d/9 == q/2 and q % 2 == 0)
			return false;
		// bob wins otherwise
		else return true;
	}
};