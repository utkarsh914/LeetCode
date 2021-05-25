// https://leetcode.com/problems/closest-dessert-cost/

class Solution {
public:
	int closestCost(vector<int>& base, vector<int>& topping, int target) {
		int ans = INT_MAX, diff = INT_MAX;

		// pick every base, and then pick remaining target from toppings
		// whichever ans is closest, update the answer accordingly
		for (int i = 0; i < base.size(); i++) {
			/*
			curcost is the total cost if I pick current base
			and then move forward to pick from toppings
			If base cost >= target, we sure don't need to add any topping
			So, in this case, we don't backtrack on toppings
			*/
			int curCost = base[i] >= target ? base[i]
				: base[i] + backtrack(topping, 0, 0, target - base[i]);
			int curdiff = abs(curCost - target);
			if (curdiff < diff)
				ans = curCost, diff = curdiff;
			else if (curdiff == diff and curCost < ans)
				ans = curCost, diff = curdiff;
		}

		return ans;
	}

	int backtrack(vector<int>& cost, int st, int sum, int target) {
		if (st == cost.size()) return sum;

		int c[3];
		// try all 3 picks
		c[0] = backtrack(cost, st+1, sum, target); // don't take
		c[1] = backtrack(cost, st+1, sum + cost[st], target); // take once
		c[2] = backtrack(cost, st+1, sum + 2*cost[st], target); // take twice

		// check which of the 3 picks above helps us reach the closest to target
		int ans = INT_MAX, diff = INT_MAX;
		for (int i = 0; i < 3; i++) {
			int curdiff = abs(c[i] - target);
			if (curdiff < diff)
				ans = c[i], diff = curdiff;
			else if (curdiff == diff and c[i] < ans)
				ans = c[i], diff = curdiff;
		}

		return ans;
	}
};








/*
there are 3 ways to add toppings:
1)add one topping to the base_i
2)add 2 toppings to base_i
3)add no toppings to a base_i
we can easily implement this with recursion since we have 3 choices at each instant.

We will take now a particular base and start adding toppings to it by the above ways

Also i have made a utility function(closest()) that takes in 2 arguments and tells the closest among them to target.

Please do upvote if you liked,it gives me lot of motivation.
Also comment what you couldn't understand
*/
class Solution {
public:
	int target;
	int closest(int a, int b){ 
		if (a == 0) return b;
		if (b == 0) return a;
		if (abs(target-a) == abs(target-b))
			return a < b ? a : b;
		return abs(target-a) < abs(target-b) ? a : b;
	}
	
	int dfs(vector<int>& top, int i, int sum){
		if (i >= top.size()) return sum;

		int a = dfs(top, i+1, sum+top[i]);
		int b = dfs(top, i+1, sum+(top[i]*2));
		int c = dfs(top, i+1, sum);

		return closest(a, closest(b, c));
	}
	
	int closestCost(vector<int>& base, vector<int>& top, int t) {
		target = t;//i made target global so that i don't need to pass it in any function
		int ans = 0;
		for (int i = 0; i < base.size(); i++){
			ans = closest(dfs(top, 0, base[i]), ans);
		}
		return ans;
	}
};