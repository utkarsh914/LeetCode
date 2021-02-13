// https://leetcode.com/problems/stone-game-vi/

/*
Intuition
Sort stones by their sum value for Alice and Bob.
If a stone is super valued for Alice, Alice wants to take it.
If a stone is super valued for Bob, Alice also wants to take it.
Because she doesn't want Bob to take it.


Explanation
Here is more convinced explanation.
Assume a stone valued [a,b] for Alice and Bod.
Alice takes it, worth a for Alice,
Bob takes it, worth b for Bob,
we can also consider that it worth -b for Alice.
The difference will be a+b.
That's the reason why we need to sort based on a+b.
And Alice and Bob will take one most valued stone each turn.
*/

class Solution {
public:
	int stoneGameVI(vector<int>& aliceV, vector<int>& bobV) {
		multimap<int, pair<int,int>, greater<int>> map;
		for (int i=0; i<aliceV.size(); i++) {
			map.insert({ aliceV[i] + bobV[i], {aliceV[i], bobV[i]} });
		}

		int alice=0, bob=0, i=0;
		for (auto& p:map) {
			if (i%2 == 0) alice += p.second.first;
			else bob += p.second.second;
			i++;
		}

		return alice==bob ? 0 : alice>bob ? 1 : -1;
	}
};


// *************** O(1) extra space **************
