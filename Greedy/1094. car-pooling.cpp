// https://leetcode.com/problems/car-pooling/

/*
You are driving a vehicle that has capacity empty seats initially available for passengers.  The vehicle only drives east (ie. it cannot turn around and drive west.)

Given a list of trips, trip[i] = [num_passengers, start_location, end_location] contains information about the i-th trip: the number of passengers that must be picked up, and the locations to pick them up and drop them off.  The locations are given as the number of kilometers due east from your vehicle's initial location.

Return true if and only if it is possible to pick up and drop off all passengers for all the given trips. 

Example 1:

Input: trips = [[2,1,5],[3,3,7]], capacity = 4
Output: false
Example 2:

Input: trips = [[2,1,5],[3,3,7]], capacity = 5
Output: true
*/






class Solution {
public:
	bool carPooling(vector<vector<int>>& T, int capacity) {
		vector<int> sitting(1001);
		for (auto& t : T) {
			int& start = t[1], &end = t[2], &n = t[0];
			// passengers get down on end
			sitting[start] += n, sitting[end] -= n;
		}

		for (int i = 0; i < 1001; i++) {
			if (i > 0) sitting[i] += sitting[i-1];
			if (sitting[i] > capacity)
				return false;
		}

		return true;
	}
};