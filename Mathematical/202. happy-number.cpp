// https://leetcode.com/problems/happy-number/

/*
Write an algorithm to determine if a number n is happy.

A happy number is a number defined by the following process:

Starting with any positive integer, replace the number by the sum of the squares of its digits.
Repeat the process until the number equals 1 (where it will stay), or it loops endlessly in a cycle which does not include 1.
Those numbers for which this process ends in 1 are happy.
Return true if n is a happy number, and false if not.

 

Example 1:

Input: n = 19
Output: true
Explanation:
12 + 92 = 82
82 + 22 = 68
62 + 82 = 100
12 + 02 + 02 = 1
*/


// use floyd's cycle detection algo to find the cycle
class Solution {
public:
	bool isHappy(int n) {
		
		int slow = n;
		int fast = getSum(getSum(n));
		
		while (slow!=1 && fast!=1) {
			if (slow == fast) // cycle exists
				return false;
			slow = getSum(slow);
			fast = getSum(getSum(fast));
		}
		
		return true;
	}
	
	int getSum(int n) {
		int sum = 0;
		string s = to_string(n);
		for (char c : s)
			sum += (c-'0')*(c-'0');
		return sum;
	}
};


// use a map to store prev values, if a value repeats, there is a cycle
class Solution {
public:
	bool isHappy(int n) {

		unordered_set<int> s;
		
		while (true) {
			if (s.count(n)) return false;
			if (n == 1) return true;
			s.insert(n);
			n = getSum(n);
		}
		
		return false;
	}
	
	int getSum(int n) {
		int sum = 0;
		string s = to_string(n);
		for (char c : s)
			sum += (c-'0')*(c-'0');
		return sum;
	}
};