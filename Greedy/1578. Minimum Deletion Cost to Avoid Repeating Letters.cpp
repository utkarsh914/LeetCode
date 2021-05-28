// https://leetcode.com/problems/minimum-deletion-cost-to-avoid-repeating-letters/

/*
Given a string s and an array of integers cost
where cost[i] is the cost of deleting the ith character in s.

Return the minimum cost of deletions such that
there areno two identical letters next to each other.

Notice that you will delete the chosen characters at the same time,
in other words, after deleting a character,
the costs of deleting other characters will not change.


Example 1:

Input: s = "abaac", cost = [1,2,3,4,5]
Output: 3
Explanation: Delete the letter "a" with cost 3 to get "abac"
(String without two identical letters next to each other).
*/






/*
track trails of consecutive same characters

keep a sum of whole trail, and the max cost in that trail
when trail ends, we can keep the char having max cost,
and delete others.

I use a bool to keep track if the trail has started.
*/
class Solution {
public:
	int minCost(string& s, vector<int>& cost) {
		int max_ = 0, sum = 0, ans = 0;
		bool started = false;

		for (int i = 1; i < s.size(); i++) {
			if (s[i] == s[i-1]) {
				if (started == false) {
					started = true;
					max_ = max(cost[i], cost[i-1]);
					sum = cost[i] + cost[i-1];
				} else {
					max_ = max(max_, cost[i]);
					sum += cost[i];
				}
			}
			else {
				ans += sum - max_;
				max_ = sum = 0;
				started = false;
			}
		}

		ans += sum - max_;
		return ans;
	}
};




/* using two pointers
same as above
just keep finding trail in every iteration of for loop
if trail length > 1, update the ans
*/
class Solution {
public:
	int minCost(string& s, vector<int>& cost) {
		int ans = 0;

		for (int i = 0; i < s.size(); ) {
			int max_ = 0, sum = 0, j = i;
			while (s[j] == s[i]) {
				max_ = max(max_, cost[j]);
				sum += cost[j];
				j++;
			}
			if (j - i > 1) ans += sum - max_;
			i = j;
		}

		return ans;
	}
};