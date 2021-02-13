/*
https://leetcode.com/problems/prefix-and-suffix-search/

Design a special dictionary which has some words and allows you to search the words in it by a prefix and a suffix.

Implement the WordFilter class:
WordFilter(string[] words) Initializes the object with the words in the dictionary.
f(string prefix, string suffix) Returns the index of the word in the dictionary which has the prefix prefix and the suffix suffix. If there is more than one valid index, return the largest of them. If there is no such word in the dictionary, return -1.

Example 1:

Input
["WordFilter", "f"]
[[["apple"]], ["a", "e"]]
Output
[null, 0]

Explanation
WordFilter wordFilter = new WordFilter(["apple"]);
wordFilter.f("a", "e"); // return 0, because the word at index 0 has prefix = "a" and suffix = 'e".

Constraints:
1 <= words.length <= 15000
1 <= words[i].length <= 10
1 <= prefix.length, suffix.length <= 10
words[i], prefix and suffix consist of lower-case English letters only.
At most 15000 calls will be made to the function f.
*/


/*
For a word like "test", consider "#test", "t#test", "st#test", "est#test", "test#test".
Then if we have a query like prefix = "te", suffix = "t", we can find it by searching for
something we've inserted starting with "t#te".

 OR USE TWO TRIES:
 One stores the words in normal order
 other stores in reversed order
*/


class Trie {
	// custom node class (each node will contain a single character of word)
	class Node {
		char data;
		int index;
		bool complete;
		int children;
	public:
		vector<Node*> next;
		// constructor
		Node(char c='*', bool comp=false) {
			data=c, index=-1, complete=comp, children=0;
			next.resize(27, NULL);
		}
		// adds a character to the node as child
		void addChild(char c) {
			if (!next[c-'a']) {
				next[c-'a'] = new Node(c);
				children++;
			}
		}
		// returns the pointer of the given children (else NULL)
		Node* address(char c) {	return next[c-'a'];	}
		// below functions are self explanatory
		void setIndex(int index) { this->index=index };
		int getIndex() { return index; }
		void markComplete() {	complete = true; }
		bool isComplete() {	return complete; }
		int childCount() { return children;	}
	};

	// root node of our trie
	Node* root;

public:

	/** Initialize your data structure here. */
	Trie() {
		root = new Node('*', false);
	}
	
	/** Inserts a word into the trie. */
	void insert(string word, int index) {
		Node* curr = root;
		for (auto c:word) {
			curr->addChild(c);
			curr = curr->address(c);
		}
		curr->markComplete();
		curr->setIndex(index);
	}

	/** Returns the pointer to node containing last character of word */
	Node* getTailNode(string word) {
		Node* curr = root;
		for (auto c:word) {
			if (!curr->address(c)) return NULL;
			curr = curr->address(c);
		}
		return curr;
	}
	
	/** Returns if the word is in the trie. */
	bool search(string word) {
		Node* curr = getTailNode(word);
		return (curr and curr->isComplete());
	}
	
	/** Returns if there is any word in the trie that starts with the given prefix. */
	bool startsWith(string prefix) {
		Node* curr = getTailNode(prefix);
		if (!curr) return false;
		// either this word should be complete in itself,
		// or it should have at least one child node.
		return curr->isComplete() or curr->childCount()>0;
	}

	int searchMaxIndexWithPrefixSuffix(string& prefix, string& suffix) {
		Node* curr = getTailNode(suffix + '{' + prefix);
		if (!curr->isComplete() and !curr->childCount())
			return -1;
		int maxIndex = 0;
		queue<Node*> q;
		q.push(curr);
		while (!q.empty()) {
			Node* cur = q.front(); q.pop();
			if (cur->isComplete() and cur->getIndex() > maxIndex)
				maxIndex = cur->getIndex();
			for (auto& n:cur->next)
				if (n!=NULL) q.push(n);
		}
		return maxIndex;
	}
};

/**
 * Your Trie object will be instantiated and called as such:
 * Trie* obj = new Trie();
 * obj->insert(word);
 * bool param_2 = obj->search(word);
 * bool param_3 = obj->startsWith(prefix);
 */


class WordFilter {
	Trie* t;
public:
	WordFilter(vector<string>& words) {
		t = new Trie();
		for (int i=0; i<words.size(); i++) {
			insertWithSuffixes(word[i], i);
		}
	}
	// insert with all possible suffixes in the trie
	void insertWithSuffixes(string& word, int index) {
		for (int i=0; i<=word.length(); i++)
			t->insert(word.substr(i) + "{" + word, index);
	}
	
	int f(string prefix, string suffix) {
		return t->searchMaxIndexWithPrefixSuffix(prefix, suffix);
	}
};

/**
 * Your WordFilter object will be instantiated and called as such:
 * WordFilter* obj = new WordFilter(words);
 * int param_1 = obj->f(prefix,suffix);
 */