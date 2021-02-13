// https://leetcode.com/problems/two-city-scheduling/

/*
How much money can we save if we fly a person to A vs. B? To minimize the total cost,
we should fly the person with the maximum saving to A, and with the minimum - to B.
*/

class Solution {
public:
	int twoCitySchedCost(vector<vector<int>>& c) {
		sort(c.begin(), c.end(), [](auto& c1, auto& c2)->bool {
			return c1[0]-c1[1] < c2[0]-c2[1];
		});
		int cost = 0;
		for (int i=0; i<c.size(); i++) {
			if (i<c.size()/2)
				cost += c[i][0];
			else
				cost += c[i][1];
		}
		return cost;
	}
};

/*
Optimized Solution
Actually, we do not need to perfectly sort all cost differences, we just need the biggest savings (to fly to A)
to be in the first half of the array. So, we can use the quick select algorithm (nth_element in C++)
and use the middle of the array as a pivot.
*/
class Solution {
public:
	int twoCitySchedCost(vector<vector<int>>& c) {
		nth_element(c.begin(), c.begin()+c.size()/2, c.end(), [](auto& c1,auto& c2)->bool {
			return c1[0]-c1[1] < c2[0]-c2[1];
		});

		int cost = 0;
		for (int i=0; i<c.size(); i++) {
			if (i<c.size()/2)
				cost += c[i][0];
			else
				cost += c[i][1];
		}

		return cost;
	}
};


/*
Those who find it hard understanding the significance of the difference :-
For every person we have to select either city A or City B for sure.
But the case is we can only send half of the people to A and remaining to B.
Example we have 100 people we have to send 50 to A and 50 to B.
once we sent 50 people to A we have no other option but to send remaining to B,
and pay the price of B. So the 50 A we selected should be such that
the price of B corresponding to those A should be as higher than A
as possible(ie, B-A should be as high as possible) so (Avoiding that B is most beneficial for us ).
Hence we are taking difference.
*/