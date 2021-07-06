// https://leetcode.com/problems/finding-mk-average/

/*
You are given two integers, m and k, and a stream of integers. You are tasked to implement a data structure that calculates the MKAverage for the stream.

The MKAverage can be calculated using these steps:

If the number of the elements in the stream is less than m you should consider the MKAverage to be -1. Otherwise, copy the last m elements of the stream to a separate container.
Remove the smallest k elements and the largest k elements from the container.
Calculate the average value for the rest of the elements rounded down to the nearest integer.
Implement the MKAverage class:

MKAverage(int m, int k) Initializes the MKAverage object with an empty stream and the two integers m and k.
void addElement(int num) Inserts a new element num into the stream.
int calculateMKAverage() Calculates and returns the MKAverage for the current stream rounded down to the nearest integer.
 

Example 1:

Input
["MKAverage", "addElement", "addElement", "calculateMKAverage", "addElement", "calculateMKAverage", "addElement", "addElement", "addElement", "calculateMKAverage"]
[[3, 1], [3], [1], [], [10], [], [5], [5], [5], []]
Output
[null, null, null, -1, null, 3, null, null, null, 5]

Explanation
MKAverage obj = new MKAverage(3, 1); 
obj.addElement(3);		// current elements are [3]
obj.addElement(1);		// current elements are [3,1]
obj.calculateMKAverage(); // return -1, because m = 3 and only 2 elements exist.
obj.addElement(10);	   // current elements are [3,1,10]
obj.calculateMKAverage(); // The last 3 elements are [3,1,10].
						  // After removing smallest and largest 1 element the container will be [3].
						  // The average of [3] equals 3/1 = 3, return 3
obj.addElement(5);		// current elements are [3,1,10,5]
obj.addElement(5);		// current elements are [3,1,10,5,5]
obj.addElement(5);		// current elements are [3,1,10,5,5,5]
obj.calculateMKAverage(); // The last 3 elements are [5,5,5].
						  // After removing smallest and largest 1 element the container will be [5].
						  // The average of [5] equals 5/1 = 5, return 5
 

Constraints:

3 <= m <= 105
1 <= k*2 < m
1 <= num <= 105
At most 105 calls will be made to addElement and calculateMKAverage.
*/





/*
---- CORRECT BUT TLE -----
*/
class MKAverage {
	int m, k;
	long sum;
	queue<int> q;
	multiset<int> s1, s2, s3;
public:
	MKAverage(int m, int k) {
		this->m = m;
		this->k = k;
		this->sum = 0;
	}
	
	void addElement(int num) {
		if (q.size() >= m) deleteElement();

		q.push(num);
		s3.insert(num);
		
		if (s3.size() > k) {
			auto itr = s3.begin(); // smallest element
			s2.insert(*itr);
			sum += *itr;
			s3.erase(itr);
		}
		if (s2.size() > (m - 2*k)) {
			auto itr = s2.begin(); // smallest element
			s1.insert(*itr);
			sum -= *itr;
			s2.erase(itr);
		}
	}

	void deleteElement() {
		int x = q.front(); q.pop();
		if (s1.count(x)) {
			s1.erase(s1.lower_bound(x));
		}
		else if (s2.count(x)) {
			sum -= x;
			s2.erase(s2.lower_bound(x));
			// pull greatest ele from lower set
			auto itr = --s1.end();
			s2.insert(*itr);
			sum += *itr;
			s1.erase(itr);
		}
		else if (s3.count(x)) {
			s3.erase(s3.lower_bound(x));
			// pull greatest ele from lower set
			auto itr = --s2.end();
			s3.insert(*itr);
			sum -= *itr;
			s2.erase(itr);
			
			// pull greatest ele from lower set
			itr = --s1.end();
			s2.insert(*itr);
			sum += *itr;
			s1.erase(itr);
		}
	}
	
	int calculateMKAverage() {
		if (q.size() < m) return -1;
		else return sum / (m - 2*k);
	}
};

/**
 * Your MKAverage object will be instantiated and called as such:
 * MKAverage* obj = new MKAverage(m, k);
 * obj->addElement(num);
 * int param_2 = obj->calculateMKAverage();
 
 m = 3, k = 1
 
 17 74 8 33 15 64
 */




