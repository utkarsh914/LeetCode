// https://leetcode.com/problems/insert-delete-getrandom-o1-duplicates-allowed/

/*
Implement the RandomizedCollection class:

RandomizedCollection() Initializes the RandomizedCollection object.
bool insert(int val) Inserts an item val into the multiset if not present. Returns true if the item was not present, false otherwise.
bool remove(int val) Removes an item val from the multiset if present. Returns true if the item was present, false otherwise. Note that if val has multiple occurrences in the multiset, we only remove one of them.
int getRandom() Returns a random element from the current multiset of elements (it's guaranteed that at least one element exists when this method is called). The probability of each element being returned is linearly related to the number of same values the multiset contains.
You must implement the functions of the class such that each function works in average O(1) time complexity.

 

Example 1:

Input
["RandomizedCollection", "insert", "insert", "insert", "getRandom", "remove", "getRandom"]
[[], [1], [1], [2], [], [1], []]
Output
[null, true, false, true, 2, true, 1]

Explanation
RandomizedCollection randomizedCollection = new RandomizedCollection();
randomizedCollection.insert(1);   // return True. Inserts 1 to the collection. Returns true as the collection did not contain 1.
randomizedCollection.insert(1);   // return False. Inserts another 1 to the collection. Returns false as the collection contained 1. Collection now contains [1,1].
randomizedCollection.insert(2);   // return True. Inserts 2 to the collection, returns true. Collection now contains [1,1,2].
randomizedCollection.getRandom(); // getRandom should return 1 with the probability 2/3, and returns 2 with the probability 1/3.
randomizedCollection.remove(1);   // return True. Removes 1 from the collection, returns true. Collection now contains [1,2].
randomizedCollection.getRandom(); // getRandom should return 1 and 2 both equally likely.
 

Constraints:

-231 <= val <= 231 - 1
At most 2 * 105  calls will be made to insert, remove, and getRandom.
There will be at least one element in the data structure when getRandom is called.
*/








/*
Here is the trick to remove in constant time.
Assume that the order of elements does not matter.
This is what you need to pay attention to.

Suppose you have a vector (not indices, but actual values in those positions)

0 1 2 3 4 5 6
and you want to remove the value 3. You can turn this into

0 1 2 6 4 5
in O(1) without any issues. (Again assuming that we are not concerned about maintaining any ordering, we are just looking to delete the value 3 in constant time)

Here is the pseudo-code

If the element you are trying to remove is the last element in the vector, remove it, done, ELSE,
Read the last element of the vector and write it over the element-to-be-removed. (swap is O(1))
Now remove the last element of the vector. (C++ pop_back() in a vector is O(1))
That is exactly the trick we are using here, only that we need to update our hashmap as well.
*/

class RandomizedCollection {
	unordered_map<int, unordered_set<int>> indices;
	vector<int> A;
public:
	/** Initialize your data structure here. */
	RandomizedCollection() {}
	
	/** Inserts a value to the collection.
	Returns true if the collection did not already contain the specified element. */
	bool insert(int val) {
		bool ans = indices[val].size() == 0;
		indices[val].insert(A.size());
		A.push_back(val);
		return ans;
	}
	
	/** Removes a value from the collection.
	Returns true if the collection contained the specified element. */
	bool remove(int val) {
		if (indices[val].empty()) return false;
		// if last ele is to be deleted, simply pop back
		if (A.back() == val) {
			A.pop_back();
			indices[val].erase(A.size());
			return true;
		}
		int lastEle = A.back();
		int lastEleIndex = A.size()-1;
		int valIndex = *(indices[val].begin());
		// remove from val's list
		indices[val].erase(valIndex);
		// update index list of lastElement
		indices[lastEle].erase(lastEleIndex);
		indices[lastEle].insert(valIndex);
		// put lastEle in place of val, and pop back
		A[valIndex] = lastEle;
		A.pop_back();
		return true;
	}
	
	/** Get a random element from the collection. */
	int getRandom() {
		int index = rand() % A.size();
		return A[index];
	}
};

/**
 * Your RandomizedCollection object will be instantiated and called as such:
 * RandomizedCollection* obj = new RandomizedCollection();
 * bool param_1 = obj->insert(val);
 * bool param_2 = obj->remove(val);
 * int param_3 = obj->getRandom();
 */