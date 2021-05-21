// https://leetcode.com/problems/convert-to-base-2/

/*
Given a number n, return a string consisting of "0"s and "1"s
that represents its value in base -2 (negative two).

The returned string must have no leading zeroes, unless the string is "0". 

Example 1:

Input: n = 2
Output: "110"
Explantion: (-2) ^ 2 + (-2) ^ 1 = 2
Example 2:

Input: n = 3
Output: "111"
Explantion: (-2) ^ 2 + (-2) ^ 1 + (-2) ^ 0 = 3
Example 3:

Input: n = 4
Output: "100"
Explantion: (-2) ^ 2 = 4
*/





/*
We can solve this problem similar to solving problem with
positive bases but one important thing to remember is,
remainder will always be positive whether we work with
positive base or negative base but in most compilers,
the result of dividing a negative number by a negative number
is rounded towards 0, usually leaving a negative remainder.


So when we will get negative remainder, we will make it positive
by adding absolute value of base to it and adding 1 to our quotient.
*/

string baseNeg2(int N, string res = "") {
  while (N != 0) {
	int rem = N % -2;
	N /= -2;
	if (rem < 0) rem += 2, N += 1;
	res = to_string(rem) + res;
  }
  return max(string("0"), res);
}



// Method to convert n to base negBase
string toNegativeBase(int n, int negBase)
{
	//  If n is zero then in any base it will be 0 only
	if (n == 0)
		return "0";
  
	string converted = "";
	while (n != 0)
	{
		// Get remainder by negative base, it can be
		// negative also
		int remainder = n % negBase;
		n /= negBase;
  
		// if remainder is negative, add abs(base) to
		// it and add 1 to n
		if (remainder < 0)
		{
			remainder += (-negBase);
			n += 1;
		}
  
		// convert remainder to string add into the result
		converted = toString(remainder) + converted;
	}
  
	return converted;
}