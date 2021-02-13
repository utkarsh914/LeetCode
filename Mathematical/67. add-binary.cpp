// https://leetcode.com/problems/add-binary/

/*
Given two binary strings a and b, return their sum as a binary string.

Example 1:

Input: a = "11", b = "1"
Output: "100"
Example 2:

Input: a = "1010", b = "1011"
Output: "10101"
*/



class Solution {
public:
	string addBinary(string& A, string& B) {
		
		string ans;
		int i = A.size()-1, j = B.size()-1, carry = 0;

		for ( ; i>=0 or j>=0 or carry>0; i--, j--) {
			int aVal = i>=0 ? A[i]-'0' : 0;
			int bVal = j>=0 ? B[j]-'0' : 0;
			ans = to_string((aVal + bVal + carry) % 2) + ans;
			carry = (aVal + bVal + carry) / 2;
		}
		
		return ans;
	}
};



class Solution {
public:
	string addBinary(string& a, string& b) {
		string& A = a.size()>=b.size() ? a : b;
		string& B = a.size()<b.size() ? a : b;
		reverse(A.begin(), A.end());
		reverse(B.begin(), B.end());
		
		string ans;
		char carry = 0;
		for (int i=0; i<A.size(); i++) {
			int na = A[i]-'0';
			int nb = i<B.size() ? B[i]-'0' : 0;
			ans.push_back('0' + (na+nb+carry)%2);
			carry = (na+nb+carry)/2;
		}
		if (carry) ans.push_back('0'+carry);
		reverse(ans.begin(), ans.end());
		return ans;
	}
};