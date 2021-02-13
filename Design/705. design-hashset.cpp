// https://leetcode.com/problems/design-hashset/




class MyHashSet {
private:
	int prime;
	vector<list<int>> table;

	int hash(int key) {
		return key % prime;
	}

	list<int>::iterator search(int key) {
		int h = hash(key);
		return find(table[h].begin(), table[h].end(), key);
	}

public:
	MyHashSet() : prime(10007), table(prime) {}
	
	void add(int key) {
		int h = hash(key);
		if (!contains(key))
			table[h].push_back(key);
	}
	
	void remove(int key) {
		int h = hash(key);
		auto it = search(key);
		if (it != table[h].end())
			table[h].erase(it);
	}
	
	bool contains(int key) {
		int h = hash(key);
		return search(key) != table[h].end();
	}
};










// *********** remove key operation causes error in this implementation *******
class MyHashSet {
	vector<int> set;
	int M, maxSize;
public:
	/** Initialize your data structure here. */
	MyHashSet() {
		set.resize(10001, -1);
		this->M = 9973;
		this->maxSize = 10001;
	}
	
	void add(int key) {
		int i = key % M;
		while (true) {
			if (set[i]==-1 or set[i]==key) {
				set[i] = key;
				return;
			}
			if (++i == maxSize)
				i = 0;
		}
	}
	
	void remove(int key) {
		int i = key % M;
		while (true) {
			if (set[i]==-1 or set[i]==key) {
				set[i] = -1;
				return;
			}
			if (++i == maxSize)
				i = 0;
		}
	}
	
	/** Returns true if this set contains the specified element */
	bool contains(int key) {
		int i = key % M;
		while (true) {
			if (set[i]==-1) {
				return false;
			} else if (set[i]==key) {
				return true;
			}
			if (++i == maxSize)
				i = 0;
		}
		return false;
	}
};

/**
 * Your MyHashSet object will be instantiated and called as such:
 * MyHashSet* obj = new MyHashSet();
 * obj->add(key);
 * obj->remove(key);
 * bool param_3 = obj->contains(key);
 */