// https://leetcode.com/problems/matchsticks-to-square/

/*
You are given an integer array matchsticks where matchsticks[i]
is the length of the ith matchstick.
You want to use all the matchsticks to make one square.
You should not break any stick, but you can link them up,
and each matchstick must be used exactly one time.

Return true if you can make this square and false otherwise.

 

Example 1:


Input: matchsticks = [1,1,2,2,2]
Output: true
Explanation: You can form a square with length 2, one side of the square came two sticks with length 1.
Example 2:

Input: matchsticks = [3,3,3,3,4]
Output: false
Explanation: You cannot find a way to form a square with all the matchsticks.
 

Constraints:

1 <= matchsticks.length <= 15
0 <= matchsticks[i] <= 109
*/








/*
--------- NAIVE -- TLE --------


Treat the matchsticks as an array. Can we split the array into 4 equal halves?
Every matchstick can belong to either of the 4 sides. We don't know which one. Maybe try out all options!
For every matchstick, we have to try out each of the 4 options i.e. which side it can belong to. We can make use of recursion for this.
We don't really need to keep track of which matchsticks belong to a particular side during recursion. We just need to keep track of the length of each of the 4 sides.
When all matchsticks have been used we simply need to see the length of all 4 sides. If they're equal, we have a square on our hands!
*/
class Solution {
	int T;
public:
	bool makesquare(vector<int>& A) {
		int sum = accumulate(A.begin(), A.end(), 0);
		if (sum % 4 != 0) return false;
		this->T = sum / 4;
		return backtrack(A, 0, 0, 0, 0, 0);
	}

	bool recur(vector<int>& A, int start, int s1, int s2, int s3, int s4) {
		if (start == A.size())
			return s1 == T and s2 == T and s3 == T and s4 == T;

		return
			recur(A, start+1, s1+A[start], s2, s3, s4) or
			recur(A, start+1, s1, s2+A[start], s3, s4) or
			recur(A, start+1, s1, s2, s3+A[start], s4) or
			recur(A, start+1, s1, s2, s3, s4+A[start]);
	}
};







class Solution {
public:
	bool makesquare(vector<int>& nums) {
		if(nums.size() < 4) return false;

		int sum = accumulate(nums.begin(), nums.end(), 0);
		if(sum % 4 != 0) return false; //If each side is not integer
		int side = sum / 4;
		// Optimize: Reverse sort so that bigger numbers get rejected early on
		// in the expansion tree
		sort(nums.begin(),nums.end(), greater<int>());
		//Optimize: If greatest match is bigger than the expected side
		if(nums.back() > side) return false;
		
		vector<int> sides(4, 0);
		return dfs(nums, sides, 0, side);
	}
	
	bool dfs(vector<int>& match, vector<int>& sides, int index, int side) {
		if (index==match.size())
			return allSidesEqual(sides);
		
		for (int i = 0; i < 4; i++) {
			if (sides[i] + match[index] > side) continue; //Optimize 1:
			if (seenBefore(sides, i)) continue; //Optimize 2:
			
			sides[i]+=match[index];
			if (dfs(match, sides, index+1, side))
				return true;
			sides[i]-=match[index];
		}

		return false;
	}
	
	inline bool allSidesEqual(vector<int>& sides) {
		return sides[0] == sides[1] && sides[1] == sides[2] && sides[2] == sides[3];
	}
	
	inline bool seenBefore(vector<int>& sides,int i) {
		for (int j = 0; j < i; j++)
			if (sides[j] == sides[i])
				return true;
		return false;
	}
};
/*
Optimize 2 handles following cases

lets say sides are currently : [5,7,5,9] , the next element is 3.
Therefore we will be applying dfs on the following:
[5+3,7,5,9]
[5,7+3,5,9]
[5,7,5+3,9]
[5,7,5,9+3]

First and third are basically the same, only in a different order. If in the first case, dfs returned false, the third case will return false too.
So we don't run dfs in third case.
*/