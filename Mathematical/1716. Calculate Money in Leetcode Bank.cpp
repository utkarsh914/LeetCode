// https://leetcode.com/problems/calculate-money-in-leetcode-bank/

/*
Hercy wants to save money for his first car.
He puts money in the Leetcode bank every day.

He starts by putting in $1 on Monday, the first day.
Every day from Tuesday to Sunday, he will put in $1 more than the day before.
On every subsequent Monday, he will put in $1 more than the previous Monday.
Given n, return the total amount of money he will have in the Leetcode bank
at the end of the nth day.

 

Example 1:

Input: n = 4
Output: 10
Explanation: After the 4th day, the total is 1 + 2 + 3 + 4 = 10.

Example 2:

Input: n = 10
Output: 37
Explanation: After the 10th day,
the total is (1 + 2 + 3 + 4 + 5 + 6 + 7) + (2 + 3 + 4) = 37.
Notice that on the 2nd Monday, Hercy only puts in $2.

*/





class Solution {
public:
	int totalMoney(int n) {
		int q = n / 7, rem = n % 7;
		int ans = 0, prev = 1;
		while (q--) {
			ans += ((prev + prev+6) * 7) / 2;
			prev++;
		}
		ans += ((prev + prev+rem-1) * rem) / 2;
		return ans;
	}
};






class Solution {
public:
	int totalMoney(int n) {
		int m=n/7;  //(no.of full weeks)
		// first week  1 2 3 4 5 6 7 (sum is 28 i.e. 7*(i+3) if i=1)
		// second week  2 3 4 5 6 7 8 (sum is 35 i.e. 7*(i+3) if i=2)
		//.... so on
		int res=0; //for result
		//calculating full weeks
		for(int i=1;i<=m;i++){
			res+=7*(i+3);
		}
		//calculating left days
		for(int i=7*m;i<n;i++){
			res+=++m;
		}
		return res;
	}
};