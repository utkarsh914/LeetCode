// https://leetcode.com/problems/car-fleet/

/*
N cars are going to the same destination along a one lane road.
The destination is target miles away.

Each car i has a constant speed speed[i] (in miles per hour),
and initial position position[i] miles towards the target along the road.

A car can never pass another car ahead of it, but it can catch up to it,
and drive bumper to bumper at the same speed.

The distance between these two cars is ignored
they are assumed to have the same position.

A car fleet is some non-empty set of cars driving at the same position and same speed.
Note that a single car is also a car fleet.

If a car catches up to a car fleet right at the destination point,
it will still be considered as one car fleet.

How many car fleets will arrive at the destination?


Example 1:

Input: target = 12, position = [10,8,0,5,3], speed = [2,4,1,1,3]
Output: 3
Explanation:
The cars starting at 10 and 8 become a fleet, meeting each other at 12.
The car starting at 0 doesn't catch up to any other car, so it is a fleet by itself.
The cars starting at 5 and 3 become a fleet, meeting each other at 6.
Note that no other cars meet these fleets before the destination, so the answer is 3.
*/




/*
first sort by distance from target

now, the idea is that if any car A has a car B ahead of it,
such that B will take more or equal time to reach the target, than A.
Then, car A will be added in the fleet of B.

create a time array.
traverse from back, and whenever we find a new max time,
it will be one fleet
*/
class Solution {
public:
	int carFleet(int target, vector<int>& position, vector<int>& speed) {
		int size = speed.size();
		vector<array<int,2>> cars(size);
		for (int i=0; i < size; i++)
			cars[i] = {position[i], speed[i]};
		sort(cars.begin(), cars.end());

		vector<double> times(size);
		for (int i=0; i < size; i++) {
			times[i] = double(target - cars[i][0]) / double(cars[i][1]);
		}

		int fleets = 0; double maxTime = -1.0;
		for (int i=size-1; i >= 0; i--) {
			if (long(times[i]*1e6) > long(maxTime*1e6)) {
				maxTime = times[i];
				fleets++;
			}
		}

		return fleets;
	}
};

/*
alternative explanation

Sort cars by the start positions pos
Loop on each car from the end to the beginning
Calculate its time needed to arrive the target
cur records the current biggest time (the slowest)

If another car needs less or equal time than cur,
it can catch up this car fleet.

If another car needs more time,
it will be the new slowest car,
and becomes the new lead of a car fleet.
*/