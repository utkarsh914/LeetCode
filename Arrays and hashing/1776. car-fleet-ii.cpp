// https://leetcode.com/problems/car-fleet-ii/

/*
There are n cars traveling at different speeds in the same direction along a one-lane road.
You are given an array cars of length n, where cars[i] = [positioni, speedi] represents:

positioni is the distance between the ith car and the beginning of the road in meters.
It is guaranteed that positioni < positioni+1.
speedi is the initial speed of the ith car in meters per second.
For simplicity, cars can be considered as points moving along the number line.
Two cars collide when they occupy the same position.
Once a car collides with another car, they unite and form a single car fleet.
The cars in the formed fleet will have the same position and the same speed,
which is the initial speed of the slowest car in the fleet.

Return an array answer, where answer[i] is the time, in seconds,
at which the ith car collides with the next car,
or -1 if the car does not collide with the next car.
Answers within 10-5 of the actual answers are accepted.


Example 1:

Input: cars = [[1,2],[2,1],[4,3],[7,2]]
Output: [1.00000,-1.00000,3.00000,-1.00000]
Explanation: After exactly one second, the first car will collide with the second car, and form a car fleet with speed 1 m/s. After exactly 3 seconds, the third car will collide with the fourth car, and form a car fleet with speed 2 m/s.
Example 2:

Input: cars = [[3,4],[5,4],[6,3],[9,1]]
Output: [2.00000,1.00000,1.50000,-1.00000]
*/











/*
We can simply ignore the merging of any car fleet, simply assume they cross each other.
Now the aim is to find the first car to the right,
which intersects with the current carbefore any other.

Assume we have already considered all cars to the right already,
now the current car is to be considered.
Let’s ignore all cars with speeds higher than the current car
since the current car cannot intersect with those ones.
Now, all cars to the right having speed strictly less than
current car are to be considered. Now, for two cars c1 and c2
with positions p1 and p2 (p1 < p2) and speed s1 and s2 (s1 > s2),
if c1 and c2 intersect before the current car and c2,
then c1 can never be the first car of intersection for
any car to the left of current car including current car.
So we can remove that car from our consideration.

We can see that we can maintain candidate cars in this way using a stack,
removing cars with speed greater than or equal to current car,
and then removing cars which can never be first point of intersection.
The first car after this process (if any) would be first point of intersection.
*/

/*
Explanation
We care about the collision time of the cars in front us.
We iteratre from the last to the first car,
and we main a stack of car indices,
where their collision time is strict decreasing.

Imagine a,b,c on the road
if the a catches b later than b catched c,
then a won't catch b but b+c.
*/
class Solution {
public:
	vector<double> getCollisionTimes(vector<vector<int>>& cars) {
		int size = cars.size();
		vector<double> times(size, -1);
		stack<int> stk;

		for (int i=size-1; i >= 0; i--) {
			int p = cars[i][0], s = cars[i][1];
			// remove those with greater speed
			// remove cars which can't ever be first point of intersection
			while (!stk.empty()) {
				int j = stk.top(), p2 = cars[j][0], s2 = cars[j][1];
				double time = double(p2 - p) / (s - s2);
				if (s2 >= s or (time >= times[j] and times[j] > 0))
					stk.pop();
				else break;
			}
			
			if (!stk.empty()) {
				int j = stk.top(), p2 = cars[j][0], s2 = cars[j][1];
				times[i] = double(p2 - p) / (s - s2);
			}

			stk.push(i);
		}

		return times;
	}
};