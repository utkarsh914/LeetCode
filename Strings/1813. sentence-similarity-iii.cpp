// https://leetcode.com/problems/sentence-similarity-iii/

/*
One way to look at it is to find one sentence as a concatenation of a prefix and suffix from the other sentence.
Get the longest common prefix between them and the longest common suffix.
*/
class Solution {
public:
	bool areSentencesSimilar(string& s1, string& s2) {
		string& str1 = s1.size() >= s2.size() ? s1 : s2;
		string& str2 = s1.size() < s2.size() ? s1 : s2;
		vector<string> A, B;
		stringstream ss1(str1), ss2(str2);
		string word;
		while ((ss1 >> word)) A.push_back(word);
		while ((ss2 >> word)) B.push_back(word);

		vector<string> prefix = LongestCommonPrefix(A, B);
		vector<string> suffix = LongestCommonSuffix(A, B);
		if (prefix.size() == B.size()) suffix.clear();
			else if (suffix.size() == B.size()) prefix.clear();
		// append suff to pre -> prefix = prefix + suffix
		prefix.insert(prefix.end(), suffix.begin(), suffix.end());
		// check if prefix == B
		if (B.size() != prefix.size()) return false;
		for (int i=0; i < B.size(); i++)
			if (B[i] != prefix[i]) return false;
		return true;
	}

	vector<string> LongestCommonPrefix(vector<string>& A, vector<string>& B) {
		vector<string> prefix;
		for (int i=0; i < min(A.size(), B.size()); i++) {
			if (A[i] != B[i]) break;
			prefix.push_back(A[i]);
		}
		return prefix;
	}

	vector<string> LongestCommonSuffix(vector<string>& A, vector<string>& B) {
		vector<string> suffix;
		for (int i=A.size()-1, j=B.size()-1; i >= 0 and j >= 0; i--, j--) {
			if (A[i] != B[j]) break;
			suffix.push_back(A[i]);
		}
		reverse(suffix.begin(), suffix.end());
		return suffix;
	}
};







class Solution {
public:
	bool areSentencesSimilar(string& s1, string& s2) {

		stringstream ss1(s1), ss2(s2); string word;
		deque<string> a, b;

		while ((ss1 >> word)) a.push_back(word);
		while ((ss2 >> word)) b.push_back(word);
		
		// removing common from front
		while(!a.empty() && !b.empty() && (a.front() == b.front()))
			a.pop_front(), b.pop_front();
		//removing common from back
		while(!a.empty() && !b.empty() && (a.back() == b.back()))
			a.pop_back(), b.pop_back();

		return (a.empty() or b.empty());
	}
};