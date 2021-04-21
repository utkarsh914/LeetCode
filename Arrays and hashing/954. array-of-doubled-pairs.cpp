// https://leetcode.com/problems/array-of-doubled-pairs/

/*
Given an array of integers arr of even length,
return true if and only if it is possible to reorder it such that
arr[2 * i + 1] = 2 * arr[2 * i]
for every 0 <= i < len(arr) / 2.

Example 1:

Input: arr = [3,1,3,6]
Output: false
*/



/*
we basically need to verify that the array has size/2 groups
(a,b) such that a*2 = b, or b*2 = a

so we store fre of all elements in a map
then for each element, we find its pair, if we found it
we reduce freq of n and 2*n from map as we've found that pair.

at the end, map should be empty,
if size/2 number of pairs were found in total
*/
class Solution {
public:
	bool canReorderDoubled(vector<int>& a) {
		unordered_map<int, int> m;
		sort(a.begin(), a.end());
		for (int n : a) m[n]++;

		for (int n : a) {
			if (m.count(n) and m.count(2*n)) {
				if (--m[2*n] == 0) m.erase(2*n);
				if (--m[n] == 0) m.erase(n);
			}
		}

		return m.size() == 0;
	}
};



/*
O(1) space, two pointers


We sort the list (ascending) by absolute value and make sure the negative ones come before the positive ones.
Then we use two pointers. Since the values are ascending (by abs), the fast pointer never looks back and will only reach the end of the list if it falis to find a 2*x and returns false. When it does find a match, it marks the item with a dummy value so that the slow pointer can skip it.
Time is O(NlogN), Space is O(1).
*/

class Solution {
public:
	bool canReorderDoubled(vector<int>& a) {
		
		sort(a.begin(), a.end(), [](int& a, int& b) {
			if (a<0 && b>0) return true;
			if (a>0 && b<0) return false;
			return abs(a) < abs(b);
		});

		int dummy = INT_MAX, count = 0, size = a.size();
		for (int i=0, j=1; i < size; i++) {
			if (a[i] == dummy) continue;
			if (j <= i) j = i+1;
			while (j < size && a[i]*2 != a[j]) j++;
			if (j == size) return false;
			a[j] = dummy;
		}

		return true;
	}
};

