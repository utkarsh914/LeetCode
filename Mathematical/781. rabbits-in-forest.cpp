// https://leetcode.com/problems/rabbits-in-forest/

/*
In a forest, each rabbit has some color. Some subset of rabbits (possibly all of them) tell you how many other rabbits have the same color as them. Those answers are placed in an array.

Return the minimum number of rabbits that could be in the forest.

Examples:
Input: answers = [1, 1, 2]
Output: 5
Explanation:
The two rabbits that answered "1" could both be the same color, say red.
The rabbit than answered "2" can't be red or the answers would be inconsistent.
Say the rabbit that answered "2" was blue.
Then there should be 2 other blue rabbits in the forest that didn't answer into the array.
The smallest possible number of rabbits in the forest is therefore 5: 3 that answered plus 2 that didn't.

Input: answers = [10, 10, 10]
Output: 11

Input: answers = []
Output: 0
*/



/*
The basic thought is: if answers[i] == anwers[j], we take them as the same color as far as possible.

If x+1 rabbits have same color, then we get x+1 rabbits who all answer x.
now n rabbits answer x.
If n % (x + 1) == 0, we need n / (x + 1) groups of x + 1 rabbits.
If n % (x + 1) != 0, we need n / (x + 1) + 1 groups of x + 1 rabbits.

the number of groups is math.ceil(n / (x + 1))
*/
class Solution {
public:
	int numRabbits(vector<int>& answers) {
		unordered_map<int, int> f;
		for (int x : answers) f[x]++;
		int rabbits = 0;
		for (auto& p : f) {
			// casting x as double is necessary to get ceil operation correct
			double x = p.first, n = p.second;
			rabbits += (x+1) * ceil(n / (x+1));
		}
		return rabbits;
	}
};




class Solution {
public:
	int numRabbits(vector<int>& answers) {
		unordered_map<int, int> f;
		for (int a : answers)
			f[a+1]++;
		int rabbits = 0;
		for (auto& p : f) {
			int x = p.first, y = p.second;
			while (y > 0) {
				rabbits += x;
				y -= x;
			}
		}
		return rabbits;
	}
};