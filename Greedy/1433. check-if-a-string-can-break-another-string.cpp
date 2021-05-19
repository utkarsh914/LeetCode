// https://leetcode.com/problems/check-if-a-string-can-break-another-string/

/*
Given two strings: s1 and s2 with the same size,
check if some permutation of string s1 can break some permutation of string s2 or vice-versa.
In other words s2 can break s1 or vice-versa.

A string x can break string y (both of size n)
if x[i] >= y[i] (in alphabetical order)for all i between 0 and n-1.


Example 1:

Input: s1 = "abc", s2 = "xya"
Output: true
Explanation: "ayx" is a permutation of s2="xya"
which can break to string "abc" which is a permutation of s1="abc".
*/






/*
Sort both strings and then check if one of them can break the other.
*/
class Solution {
public:
	bool checkIfCanBreak(string& s1, string& s2) {
		sort(s1.begin(), s1.end());
		sort(s2.begin(), s2.end());

		bool s1_can_break = true, s2_can_break = true;
		for (int i = 0; i < s1.size(); i++) {
			if (s1[i] < s2[i]) s1_can_break = false;
		}
		for (int i = 0; i < s1.size(); i++) {
			if (s1[i] > s2[i]) s2_can_break = false;
		}
		
		return s1_can_break or s2_can_break;
	}
};






/*
********* COUNT FREQENCY -> O(N) ********

At any point count1 > count2 means that s1 is broken by s2
but if s2 was previously broken by s1, it becomes contradictory
such scenario shouldn't occur. It means, both can't break each other
so, return false
*/
class Solution {
public:
	bool checkIfCanBreak(string& s1, string& s2) {
		int f1[26] = {}, f2[26] = {};
		// count freq
		for (char& c : s1) f1[c-'a']++;
		for (char& c : s2) f2[c-'a']++;

		int count1 = 0, count2 = 0;
		bool s1_is_broken = false, s2_is_broken = false;

		for (int i = 0; i < 26; i++) {
			count1 += f1[i], count2 += f2[i];
			if (count1 > count2) {
				if (s2_is_broken) return false;
				s1_is_broken = true;
			}
			else if (count2 > count1) {
				if (s1_is_broken) return false;
				s2_is_broken = true;
			}
		}
		
		return true;
	}
};
/*
1. We can go through the input and process it to be more useful.
Since order is not important, we can use a frequency table/map.

2. At each stage of the for loop (looping from 'a' - 'z'),
we compare the number of characters in each string s1, s2
which is lexographically less than the current character.
If count1 > count2, we know that there are more characters in s1
less than the cur character than s2 so when considering
all the characters from 'a' up to cur character, s2 must be able to break s1.
If we do this for all characters 'a' - 'z' then s2 breaks s1.
Similarly true for when count2 > count1 for all characters.

3. If count1 > count2 and then count2 > count1 or vice versa,
then intuitively return false.
*/



/*
The most straightforward intuition for solving this problem is
sorting both stringsand then comparing char by char
(to see if they abide by the "breaking" rules).
Your first thought is that this is O(nlogn + n) because:

Sort both inputs - O(nlogn)
Compare inputs - O(n)

However, considering that the input range is well defined
(i.e. letters between 'a' and 'z') we can use radixsort instead,
which uses buckets to store letter frequency
and then uses those buckets to create a sorted array/string.
This is done in O(n).

The only difference is the shared solution above
doesn't sort back the string but compares the buckets (frequencies) instead.
*/
