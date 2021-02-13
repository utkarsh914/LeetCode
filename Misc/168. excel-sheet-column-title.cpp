// https://leetcode.com/problems/excel-sheet-column-title/


string convertToTitle(int n) {
	if (n == 0) return "";
	return convertToTitle((n - 1) / 26) + (char) ((n - 1) % 26 + 'A');
}


string convertToTitle(int n) {
	string s;
	while (n) {
		char c = (n-1) % 26 + 'A';
		s = c + s;
		n = (n-1) / 26;
	}
	return s;
}


class Solution {
public:
	string convertToTitle(int n) {
		string s;

		while (n) {
			char c;
			if (n % 26 == 0) {
				c = 'Z';
				n = n/26 - 1;
			} else {
				c = (n % 26) + 'A' - 1;
				n = n/26;
			}
			s.push_back( c );
		}

		reverse(s.begin(), s.end());
		return s;
	}
};


/*
The problem originates from here:
It is a 26-nary system, but without the '0'.
A typical 26-nary system would be:

0 -> A
25 -> Z
26 -> BA
However, the excel system actually behaves differently:

1 -> A
26 -> Z
27 -> AA
You could think it for a while and then get the idea why this excel system is actually behaving quite strangly. It is like in a number system in which after 9 it is 00 instead of 10; or like a system without zero: starting with 1, 2.. and after 9 it is 11.
Although the code is quite short and simple, I DO think it is hard to fully understand how this system behaves.

Now, how to solve it:

Equation relationships will help us through the process, and It it not very difficult to derive them. With equations we can understand how to get the n-1 at first of the loop.
The relationship between the string and number is:

for String ABZ and its corresponding number n:
n = (A+1) * 26^2 + (B+1) * 26^1 + (Z+1) * 26^0
Why (A+1)? Because in char system 'A' is 0, but in excel system 'A' is one. Every char get an extra one.

Inorder to get Z, or whatever char is at Z, we will first do a minus 1 on both sides:

both sides -1
n-1 = (A+1) * 26^2 + (B+1) * 26^1 + Z
Then do a %26 we will get Z.

(n-1)%26 =  Z                                                  (1)
(n-1)/26 = (A+1) * 26^1 + (B+1) * 26^0                         (2)
With the above equations, we can understand why we need the n-- at first of every loop:
For each loop, we use (1) to obtain what the current char is.
And we divide n-1 by 26 to get (2), in preparation for the next loop.

Java:

class Solution {
    public String convertToTitle(int n) {
        StringBuilder sb = new StringBuilder();
        while(n > 0){
            n--;
            int curr = n%26;
            n /= 26;
            sb.append((char)(curr+'A'));
        }
        return sb.reverse().toString();
    }
}


*/