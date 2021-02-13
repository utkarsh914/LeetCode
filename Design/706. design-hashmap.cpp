// https://leetcode.com/problems/design-hashmap/

class MyHashMap {
	int prime;
	vector<list<pair<int,int>>> table;

	int hash(int key) {
		return key % prime;
	}

	list<pair<int,int>>::iterator search(int key) {
		int h = hash(key);
		for (auto it = table[h].begin(); it != table[h].end(); it++) {
			if (it->first == key)
				return it;
		}
		return table[h].end();
	}

public:
	/** Initialize your data structure here. */
	MyHashMap() : prime(10007), table(prime) {}
	
	/** value will always be non-negative. */
	void put(int key, int value) {
		int h = hash(key);
		auto it = search(key);
		if (it == table[h].end())
			table[h].push_back({key, value});
		else it->second = value;
	}
	
	/** Returns the value to which the specified key is mapped, or -1 if this map contains no mapping for the key */
	int get(int key) {
		int h = hash(key);
		auto it = search(key);
		return (it != table[h].end()) ? it->second : -1;
	}
	
	/** Removes the mapping of the specified value key if this map contains a mapping for the key */
	void remove(int key) {
		int h = hash(key);
		auto it = search(key);
		if (it != table[h].end())
			table[h].erase(it);
	}
};


/**
 * Your MyHashMap object will be instantiated and called as such:
 * MyHashMap* obj = new MyHashMap();
 * obj->put(key,value);
 * int param_2 = obj->get(key);
 * obj->remove(key);
 */