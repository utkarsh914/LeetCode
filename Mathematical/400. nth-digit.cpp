// https://leetcode.com/problems/nth-digit/

/*
Given an integer n, return the nth digit of the infinite integer sequence [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, ...].

 

Example 1:

Input: n = 3
Output: 3
Example 2:

Input: n = 11
Output: 0
Explanation: The 11th digit of the sequence 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, ... is a 0, which is part of the number 10.
*/

class Solution {
public:
	int findNthDigit(long n) {
		long len = 1, nine = 9, last = 0;
		
		while (n > nine*len) {
			n -= nine*len;
			last += nine;
			nine *= 10;
			len++;
		}
		
		long num = last + ceil(double(n)/len);
		return extractDigit(num, n % len);
	}
	
	int extractDigit(long num, long i) {
		string n = to_string(num);
		return i==0 ? n.back()-'0' : n[i-1]-'0';
	}
};