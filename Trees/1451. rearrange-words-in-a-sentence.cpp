// https://leetcode.com/problems/rearrange-words-in-a-sentence/

class Solution {
public:
	string arrangeWords(string& text) {
		stringstream ss(text);
		string word;
		vector<string> words;
		while (ss >> word) {
			word[0] = tolower(word[0]);
			words.push_back(word);
		}

		stable_sort(words.begin(), words.end(), [](const string& s1, const string& s2) {return s2.length() > s1.length();});
		string ans; ans.reserve(text.length()+1);
		for (auto& word:words) {
			ans += word + " ";
		}
		ans[0] = toupper(ans[0]);
		ans.pop_back();
		return ans;
	}
};


// or use map<int,string> (no need of stable sort then)
class Solution { // Map bucket solution
public: // Time/Space: O(NlogN); N:=|text|
	string arrangeWords(string& text) {
		
		text[0] = tolower(text[0]);
		stringstream ss(text);
		string word;
		
		map<int, string> m;
		while (ss >> word) m[word.size()] += word + " ";
		
		string result; result.reserve(text.size()+1);
		for (auto& s: m)
			result += s.second;
		
		result.pop_back();
		result[0] = toupper(result[0]);
		return result;
	}
};