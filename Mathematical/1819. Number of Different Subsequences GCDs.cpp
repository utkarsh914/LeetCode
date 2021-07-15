// https://leetcode.com/problems/number-of-different-subsequences-gcds/

/*
You are given an array nums that consists of positive integers.

The GCD of a sequence of numbers is defined as the greatest integer that divides all the numbers in the sequence evenly.

For example, the GCD of the sequence [4,6,16] is 2.
A subsequence of an array is a sequence that can be formed by removing some elements (possibly none) of the array.

For example, [2,5,10] is a subsequence of [1,2,1,2,4,1,5,10].
Return the number of different GCDs among all non-empty subsequences of nums.

 

Example 1:


Input: nums = [6,10,3]
Output: 5
Explanation: The figure shows all the non-empty subsequences and their GCDs.
The different GCDs are 6, 10, 3, 2, and 1.
Example 2:

Input: nums = [5,15,40,5,6]
Output: 7
 

Constraints:

1 <= nums.length <= 105
1 <= nums[i] <= 2 * 105
*/







/*
for every possible value x of gcd (from 1 to max_element),
I check which numbers (say 'y') in the array are divisible by x,
and keep a gcd of all those numbers.

If the gcd of all those nums is equal to x,
then x can be counted, otherwise not.

example -
consider some random array.
let x = 2, and we get [2, 6, 12] as 'y's which are in our array
now, gcd of <2,6,12> is 2 only. so, 2 can be counted.

but,
let x = 2, and we get [6, 12] as 'y's,
now gcd of <6, 12> is 6, which != x.
so, 2 can't be counted in this case.

this case will be countd automatically
when x will be taken as 6 in further iterations.
*/
class Solution {
public:
	int countDifferentSubsequenceGCDs(vector<int>& nums) {
		int limit = *max_element(nums.begin(), nums.end());
		vector<bool> exists(limit+1, false);
		for (int n : nums) exists[n] = true;
		
		int count = 0;
		for (int x = 1; x <= limit; x++) {
			int gcd = 0;
			for (int y = x; y <= limit; y += x) {
				if (exists[y] == true)
					gcd = __gcd(gcd, y);
			}
			if (gcd == x)
				count++;
		}
		
		return count;
	}
};


/*
-------- MORE DETAILED ---------


since the Max Value possible is 2*10^5, this is the max gcd.
Hence We can iterate over all possible gcd values and check whether
they can be a gcd of a subsequence.

So the question becomes,
Given a number x, check whether there exists a subsequence such that
x is a gcd of that subsequence.
(If we do this for all x, we can count the unique gcd values).

Now, x can only be a gcd of numbers which are multiples of x.
For example, if x = 5 then it can only be a gcd of a subsequence
containting elements 5, 10, 15, 20, 25 ....

Now not all of these 5, 10, 15, 20, 25... would be given in the inital array.
So we can hash which ones are present in the given array to check
if we can ever make that value be part of the subsequence.
For example if the intial array is <5,15> then we can't use 10.

Now, For all the valid numbers we can pick from x to LIMIT are the ones :
a) Which are multiples of x (Forced because of the way for loop is written)
b) must exist in array nums (Checked using a hash)

Now x can only be a gcd, if gcd of these valid values is same as x.

If nums is <3,6,12> then
for x = 2, we find two valid values <6,12> but gcd(6,12) is 6.
Hence 2 can never be a gcd of any resulting subsequence.
For = 6,
valid values are <6,12> and gcd = 6. So 6 will be added to answer set.

For x = 3, valid values are <3,6,12> gcd = 3. will be added to answer set.

for x = 5 valid values are <>. will NOT be added.

for x = 12, valid values are <12> , gcd = 12. will be added.

(The confusing part maybe
	"why should gcd of all these valid numbers be same as x?"
	This is because the valid set can never have values less than x.
	So either the gcd > x or its equal to x.
	If we use up all the valid values and still can't get gcd x,
	then there exists no number that can help us get gcd = x,
	hence x can't be a unique gcd.
	If gcd = x, then we must have gotten a subsequence
	such that gcd of that subseq. is x.
)

Another example, for x = 2, in the nums = <6,8,24>
valid values are <6,8,24> and gcd = 2.
Note that gcd(6,8) = 2, now even if we take a gcd of <6,8>
with any other valid number (multiple of 2) like 24 in this case,
we won't get anything lower than 2 as gcd.

In the solution, the outer loop fixes our "x"
and the inner loop goes over all the valid values.
*/