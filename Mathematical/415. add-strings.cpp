// https://leetcode.com/problems/add-strings/

/*
Given two non-negative integers num1 and num2 represented as string, return the sum of num1 and num2.
*/



class Solution {
public:
	string addStrings(string& A, string& B) {
		
		string ans;
		int i = A.size()-1, j = B.size()-1, carry = 0;

		for ( ; i>=0 or j>=0 or carry>0; i--, j--) {
			int aVal = i>=0 ? A[i]-'0' : 0;
			int bVal = j>=0 ? B[j]-'0' : 0;
			ans.push_back('0' + (aVal + bVal + carry) % 10); // <---
			carry = (aVal + bVal + carry) / 10;
		}
		
		reverse(ans.begin(), ans.end()); // <---
		return ans;
	}
};


// adding to string in every iteration is slower than 
// pushing back and reversing at the end (first solution)
class Solution {
public:
	string addStrings(string& A, string& B) {
		
		string ans;
		int i = A.size()-1, j = B.size()-1, carry = 0;

		for ( ; i>=0 or j>=0 or carry>0; i--, j--) {
			int aVal = i>=0 ? A[i]-'0' : 0;
			int bVal = j>=0 ? B[j]-'0' : 0;
			ans = to_string((aVal + bVal + carry) % 10) + ans; // <---
			carry = (aVal + bVal + carry) / 10;
		}
		
		return ans;
	}
};



class Solution {
public:
	string addStrings(string& a, string& b) {
		string& A = a.size()>=b.size() ? a : b;
		string& B = a.size()<b.size() ? a : b;
		reverse(A.begin(), A.end());
		reverse(B.begin(), B.end());
		
		string ans;
		char carry = 0;
		for (int i=0; i<A.size(); i++) {
			int na = A[i]-'0';
			int nb = i<B.size() ? B[i]-'0' : 0;
			ans.push_back('0' + (na+nb+carry)%10);
			carry = (na+nb+carry)/10;
		}
		if (carry) ans.push_back('0'+carry);
		reverse(ans.begin(), ans.end());
		return ans;
	}
};