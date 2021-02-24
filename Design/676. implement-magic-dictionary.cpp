// https://leetcode.com/problems/implement-magic-dictionary/

/*
Design a data structure that is initialized with a list of different words.
Provided a string, you should determine if you can change exactly one character
in this stringto match any word in the data structure.

Implement the MagicDictionary class:

MagicDictionary() Initializes the object.
void buildDict(String[] dictionary) Sets the data structure with an array of distinct strings dictionary.
bool search(String searchWord) Returns true if you can change exactly one character
in searchWord to match any string in the data structure, otherwise returns false.
*/

class MagicDictionary {
	unordered_set<string> set;
public:
	/** Initialize your data structure here. */
	MagicDictionary() {}
	
	void buildDict(vector<string> dictionary) {
		for (auto& w : dictionary)
			set.insert(w);
	}
	
	bool search(string word) {
		for (int i=0; i < word.size(); i++) {
			char backup = word[i];
			for (char c = 'a'; c <= 'z'; c++) {
				if (c == backup) continue;
				word[i] = c;
				if (set.count(word))
					return true;
			}
			word[i] = backup;
		}
		return false;
	}
};

/**
 * Your MagicDictionary object will be instantiated and called as such:
 * MagicDictionary* obj = new MagicDictionary();
 * obj->buildDict(dictionary);
 * bool param_2 = obj->search(searchWord);
 */