/*
https://leetcode.com/problems/lfu-cache/

Design and implement a data structure for Least Frequently Used (LFU) cache.

Implement the LFUCache class:

LFUCache(int capacity) Initializes the object with the capacity of the data structure.
int get(int key) Gets the value of the key if the key exists in the cache. Otherwise, returns -1.
void put(int key, int value) Sets or inserts the value if the key is not already present. When the cache reaches its capacity, it should invalidate the least frequently used item before inserting a new item. For this problem, when there is a tie (i.e., two or more keys with the same frequency), the least recently used key would be evicted.
Notice that the number of times an item is used is the number of calls to the get and put functions for that item since it was inserted. This number is set to zero when the item is removed.

 

Example 1:

Input
["LFUCache", "put", "put", "get", "put", "get", "get", "put", "get", "get", "get"]
[[2], [1, 1], [2, 2], [1], [3, 3], [2], [3], [4, 4], [1], [3], [4]]
Output
[null, null, null, 1, null, -1, 3, null, -1, 3, 4]

Explanation
LFUCache lfu = new LFUCache(2);
lfu.put(1, 1);
lfu.put(2, 2);
lfu.get(1);	  // return 1
lfu.put(3, 3);   // evicts key 2
lfu.get(2);	  // return -1 (not found)
lfu.get(3);	  // return 3
lfu.put(4, 4);   // evicts key 1.
lfu.get(1);	  // return -1 (not found)
lfu.get(3);	  // return 3
lfu.get(4);	  // return 4
*/

class LFUCache {
	int Cap, minFreq; // we maintain minimum freq 
	unordered_map<int, list<int>> freqMap; // stores list of keys for all freq
	unordered_map<int, list<int>::iterator> itrMap; // pointers to all keys in lists above
	unordered_map<int, pair<int,int>> keyInfo; // stores value and freq corresponding to each key
	
public:
	
	LFUCache(int capacity) {
		Cap=capacity, minFreq=1;
	}
	
	void put(int key, int value) {
		if (Cap == 0) return;
		if (itrMap.count(key)) {
			int f = keyInfo[key].second;
			// delete from freq list
			freqMap[f].erase(itrMap[key]);
			// insert in f+1 list
			freqMap[f+1].push_front(key);
			// update maps
			itrMap[key] = freqMap[f+1].begin();
			keyInfo[key] = {value, f+1};
			// update min freq
			if (freqMap[minFreq].size() == 0) minFreq = f+1;
			minFreq = min (minFreq, f+1);
			return;
		}
		if (itrMap.size() == Cap) {
			// pop_back at minFreq list;
			int tempKey = freqMap[minFreq].back();
			freqMap[minFreq].pop_back();
			itrMap.erase(tempKey);
			keyInfo.erase(tempKey);
		}
		// insert in 1 list
		freqMap[1].push_front(key);
		// update maps
		itrMap[key] = freqMap[1].begin();
		keyInfo[key] = {value, 1};
		minFreq = 1;
	}
	
	int get(int key) {
		if (Cap==0 or !itrMap.count(key))
			return -1;
		
		int f = keyInfo[key].second;
		// delete from freq list
		freqMap[f].erase(itrMap[key]);
		// insert in f+1 list
		freqMap[f+1].push_front(key);
		// update maps
		itrMap[key] = freqMap[f+1].begin();
		keyInfo[key].second = f+1;
		
		// update min freq
		if (freqMap[minFreq].size() == 0) minFreq = f+1;
		else minFreq = min (minFreq, f+1);
		return keyInfo[key].first;
	}

};

/**
 * Your LFUCache object will be instantiated and called as such:
 * LFUCache* obj = new LFUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */