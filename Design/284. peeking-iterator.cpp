// https://leetcode.com/problems/peeking-iterator/

/*
Given an Iterator class interface with methods: next() and hasNext(),
design and implement a PeekingIterator that support the peek() operation --
it essentially peek() at the element that will be returned by the next call to next().
*/

/*
 * Below is the interface for Iterator, which is already defined for you.
 * **DO NOT** modify the interface for Iterator.
 *
 *  class Iterator {
 *		struct Data;
 * 		Data* data;
 *		Iterator(const vector<int>& nums);
 * 		Iterator(const Iterator& iter);
 *
 * 		// Returns the next element in the iteration.
 *		int next();
 *
 *		// Returns true if the iteration has more elements.
 *		bool hasNext() const;
 *	};
 */

class PeekingIterator : public Iterator {
	int nextVal;
	bool hasNextVal;
public:
	PeekingIterator(const vector<int>& nums) : Iterator(nums) {
		hasNextVal = Iterator::hasNext();
		if (hasNextVal) nextVal = Iterator::next();
	}
	
	// Returns the next element in the iteration without advancing the iterator.
	int peek() {
		return nextVal;
	}
	
	// hasNext() and next() should behave the same as in the Iterator interface.
	// Override them if needed.
	int next() {
		int ans = nextVal;
		hasNextVal = Iterator::hasNext();
		if (hasNextVal) nextVal = Iterator::next();
		return ans;
	}
	
	bool hasNext() const {
		return hasNextVal;
	}
};





// parent class has a copy constructor, so make a copy, call its next and return the value
class PeekingIterator : public Iterator {
public:
	PeekingIterator(const vector<int>& nums) : Iterator(nums) {	}
	// Returns the next element in the iteration without advancing the iterator.
	int peek() {
		return Iterator(*this).next();
	}
};