
class WordDictionary {


class Trie {
	// custom node class (each node will contain a single character of word)
	class Node {
		char data;
		bool complete;
		int children;
	public:
		vector<Node*> next;
		// constructor
		Node(char c='*', bool comp=false) {
			data=c, complete=comp, children=0;
			next.resize(26, NULL);
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
		void markComplete() {	complete = true; }
		bool isComplete() {	return complete; }
		int childCount() { return children;	}
	};

public:
	// root node of our trie
	Node* root;
	/** Initialize your data structure here. */
	Trie() {
		root = new Node('*', false);
	}
	/** Inserts a word into the trie. */
	void insert(string word) {
		Node* curr = root;
		for (auto c:word) {
			curr->addChild(c);
			curr = curr->address(c);
		}
		curr->markComplete();
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
	bool search(string word, int start=0, Node* curr=NULL) {
		if (!curr) curr=root;
		for (int i=start; i<word.length(); i++) {
			char c = word[i];
			if (c == '.') {
				for (auto j:curr->next)
					if (j!=NULL and search(word, i+1, j))
						return true;
				return false;
			}
			if (!curr->address(c))
				return false;
			curr = curr->address(c);
		}
		return (curr and curr->isComplete());
	}
	/** Returns if there is any word in the trie that starts with the given prefix. */
	bool startsWith(string prefix) {
		Node* curr = getTailNode(prefix);
		if (!curr) return false;
		return curr->isComplete() or curr->childCount()>0;
	}
};

/**
 * Your Trie object will be instantiated and called as such:
 * Trie* obj = new Trie();
 * obj->insert(word);
 * bool param_2 = obj->search(word);
 * bool param_3 = obj->startsWith(prefix);
 */
	
	Trie* t;

public:
	/** Initialize your data structure here. */
	WordDictionary() {
		this->t = new Trie();
	}
	void addWord(string word) {
		t->insert(word);
	}
	bool search(string word) {
		return t->search(word);
	}
};

/**
 * Your WordDictionary object will be instantiated and called as such:
 * WordDictionary* obj = new WordDictionary();
 * obj->addWord(word);
 * bool param_2 = obj->search(word);
 */