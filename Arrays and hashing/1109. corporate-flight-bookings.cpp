// https://leetcode.com/problems/corporate-flight-bookings/

/*

*/

/* it is a simple range update problem
My method -

I make a new array, which will finally have what values need to be incremented
on original array for every index. e.g. in orig array a[i] -> a[i]+myArr[i] after all range updates

for every range suppose we need to increment by x from index i to j(inclusive).
so I do myArr[i] += x, and myArr[j+1] -= x;
at the end, I make a presum on myArray.
This is the final array that we will be adding to original array to get our final answer

so, modify the final array a as
	a[i] = a[i]+myArr[i]


=========== QUOTED FROM GFG ===========

Create an array sum[] of size n and initialize all of its index with the value 0.
Now for each (start, end) index pair apply the given operation on the sum[] array.
The operations are: sum[start] += d and sum[end+1] -= d only if the index (end+1) exists.
Now, from the index i = 1 to n-1, accumulate the values in the sum[] array as: sum[i] += sum[i-1].
Finally for the index i = 0 to n-1, perform the operation: arr[i] += sum[i].
*/

class Solution {
public:
	vector<int> corpFlightBookings(vector<vector<int>>& bookings, int n) {
		vector<int> ans(n+1);
		for (auto& b : bookings) {
			int &i = b[0], &j = b[1];
			ans[i-1] += b[2];
			ans[j] -= b[2];
		}
		ans.pop_back();
		for (int i=1; i < ans.size(); i++)
			ans[i] += ans[i-1];
		return ans;
	}
};