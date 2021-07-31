// https://leetcode.com/problems/all-oone-data-structure/

/*
Design a data structure to store the strings' count with the ability to return the strings with minimum and maximum counts.

Implement the AllOne class:

AllOne() Initializes the object of the data structure.
inc(String key) Increments the count of the string key by 1. If key does not exist in the data structure, insert it with count 1.
dec(String key) Decrements the count of the string key by 1. If the count of key is 0 after the decrement, remove it from the data structure. It is guaranteed that key exists in the data structure before the decrement.
getMaxKey() Returns one of the keys with the maximal count. If no element exists, return an empty string "".
getMinKey() Returns one of the keys with the minimum count. If no element exists, return an empty string "".
 

Example 1:

Input
["AllOne", "inc", "inc", "getMaxKey", "getMinKey", "inc", "getMaxKey", "getMinKey"]
[[], ["hello"], ["hello"], [], [], ["leet"], [], []]
Output
[null, null, null, "hello", "hello", null, "hello", "leet"]

Explanation
AllOne allOne = new AllOne();
allOne.inc("hello");
allOne.inc("hello");
allOne.getMaxKey(); // return "hello"
allOne.getMinKey(); // return "hello"
allOne.inc("leet");
allOne.getMaxKey(); // return "hello"
allOne.getMinKey(); // return "leet"
 

Constraints:

1 <= key.length <= 10
key consists of lowercase English letters.
It is guaranteed that for each call to dec, key is existing in the data structure.
At most 5 * 104 calls will be made to inc, dec, getMaxKey, and getMinKey.
*/









// use 2 maps, and keep them synced
class AllOne {
	unordered_map<string, multiset<pair<int, string>>::iterator > map1;
	multiset<pair<int, string>> map2;

public:
	/** Initialize your data structure here. */
	AllOne() {}
	
	/** Inserts a new key <Key> with value 1.
	Or increments an existing key by 1. */
	void inc(string key) {
		if (!map1.count(key)) {
			auto itr2 = map2.insert({ 1, key });
			map1[key] = itr2;
			return;
		}
		auto& itr2 = map1[key];
		pair<int,string> pair = { itr2->first + 1, itr2->second };
		map2.erase(itr2);
		itr2 = map2.insert(pair);
	}
	
	/** Decrements an existing key by 1.
	If Key's value is 1, remove it from the data structure. */
	void dec(string key) {
		if (!map1.count(key)) {
			return;
		}
		auto& itr2 = map1[key];
		pair<int,string> pair = { itr2->first - 1, itr2->second };
		map2.erase(itr2);
		if (pair.first == 0)
			map1.erase(key);
		else itr2 = map2.insert(pair);
	}
	
	/** Returns one of the keys with maximal value. */
	string getMaxKey() {
		if (map2.size() == 0) return "";
		return (--map2.end())->second;
	}
	
	/** Returns one of the keys with Minimal value. */
	string getMinKey() {
		if (map2.size() == 0) return "";
		return map2.begin()->second;
	}
};

/**
 * Your AllOne object will be instantiated and called as such:
 * AllOne* obj = new AllOne();
 * obj->inc(key);
 * obj->dec(key);
 * string param_3 = obj->getMaxKey();
 * string param_4 = obj->getMinKey();
 */