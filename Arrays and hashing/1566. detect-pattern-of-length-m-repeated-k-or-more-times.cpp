/*
https://leetcode.com/problems/detect-pattern-of-length-m-repeated-k-or-more-times/


Given an array of positive integers arr,  find a pattern of length m that is repeated k or more times.
A pattern is a subarray (consecutive sub-sequence) that consists of one or more values, repeated multiple times consecutively without overlapping. A pattern is defined by its length and the number of repetitions.
Return true if there exists a pattern of length m that is repeated k or more times, otherwise return false. 

Example 1:

Input: arr = [1,2,4,4,4,4], m = 1, k = 3
Output: true
Explanation: The pattern (4) of length 1 is repeated 4 consecutive times. Notice that pattern can be repeated k or more times but not less.


// ******************* SOLUTION EXPLANATION *******************

(k-1) * m, as a halting condition for his code, because, the count variable is incrementing by one
each time arr[[i] and arr[j] are equal, not each time an equal subarray is found.
This means that once count reaches a value that is equal to
the length of the subarray, (m), multiplied by k-1,(because the first subarray was not included in the count),
then the code should stop and return true.
*/

class Solution {
public:
	bool containsPattern(vector<int>& a, int m, int k) {
		int count=0;
		for (int i=0; i+m<a.size(); i++) {
			if (a[i]==a[i+m]) count++;
			else count=0;
			if (count == (k-1)*m)
				return true;
		}
		return false;
	}
};
