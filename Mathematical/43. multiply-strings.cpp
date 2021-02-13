// https://leetcode.com/problems/multiply-strings/



class Solution {
public:
	string multiply(string& A, string& B) {
		int m = A.size(), n = B.size();
		vector<int> arr(m+n, 0);
		
		for (int i=m-1; i>=0; i--) {
			for (int j=n-1; j>=0; j--) {
				int mul = (A[i]-'0') * (B[j]-'0');
				int pos1 = i+j, pos2 = i+j+1;
				int sum = mul + arr[pos2];
				
				arr[pos2] = sum % 10;
				arr[pos1] += sum / 10;
			}
		}

		string s;
		int i=0; while (i<arr.size() && arr[i]==0) i++;
		while (i < arr.size())
			s.push_back(arr[i++] + '0');

		return s.empty() ? "0" : s;
	}
};



class Solution {
public:
	string multiply(string a, string b) {
		string& A = a.size()>=b.size() ? a : b;
		string& B = a.size()<b.size() ? a : b;
		
		string prev = "0";
		for (int i=B.size()-1; i>=0; i--) {
			string cur;
			char carry = 0;
			for (int j=A.size()-1; j>=0; j--) {
				int na = A[j]-'0', nb = B[i]-'0';
				cur.push_back('0' + (na*nb+carry)%10);
				carry = (na*nb+carry)/10;
			}
			if (carry) cur.push_back('0'+carry);
			reverse(cur.begin(), cur.end());
			
			for (int k=1; k<=B.size()-i-1; k++)
				cur.push_back('0');
			prev = addStrings(prev, cur);
		}
		
		while (prev.size()>1 && prev[0]=='0')
			prev.erase(prev.begin());

		return prev;
	}
	
	string addStrings(string& A, string& B) {
		string ans;
		int i = A.size()-1, j = B.size()-1, carry = 0;
		for ( ; i>=0 or j>=0 or carry>0; i--, j--) {
			int aVal = i>=0 ? A[i]-'0' : 0;
			int bVal = j>=0 ? B[j]-'0' : 0;
			ans.push_back('0' + (aVal + bVal + carry) % 10);
			carry = (aVal + bVal + carry) / 10;
		}
		reverse(ans.begin(), ans.end());
		return ans;
	}
};