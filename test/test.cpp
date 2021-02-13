// { Driver Code Starts
#include <bits/stdc++.h>
using namespace std;
 // } Driver Code Ends

class Solution {
public:
	vector<string> generateParenthesis(int n) {
		unordered_set<string> ans;
		if (n==0) return vector<string>();
		if (n==1) return vector<string>(1, "()");
		vector<string> smaller = generateParenthesis(n-1);
		for (int i=0; i<smaller.size(); i++) {
			ans.insert("(" + smaller[i] + ")");
			ans.insert("()" + smaller[i]);
			ans.insert(smaller[i] + "()");
		}
		vector<string> result;
		for (auto i=ans.begin(); i!=ans.end(); i++)
			result.push_back(*i);
		return result;
	}
};


// { Driver Code Starts.

int main() {
	int t;
	cin >> t;
	while (t--) {
		int n;
		cin >> n;
		Solution s;
		vector<string> ans = s.generateParenthesis(n);
		for (int i=0; i<ans.size(); i++)
			cout << ans[i] << " ";
		cout << "\n";
	}
	return 0;
}  // } Driver Code Ends