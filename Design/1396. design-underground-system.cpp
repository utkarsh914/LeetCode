// https://leetcode.com/problems/design-underground-system/


/*
Implement the UndergroundSystem class:

void checkIn(int id, string stationName, int t)
A customer with a card id equal to id, gets in the station stationName at time t.
A customer can only be checked into one place at a time.
void checkOut(int id, string stationName, int t)
A customer with a card id equal to id, gets out from the station stationName at time t.
double getAverageTime(string startStation, string endStation)
Returns the average time to travel between the startStation and the endStation.
The average time is computed from all the previous traveling from startStation to endStation that happened directly.
Call to getAverageTime is always valid.
You can assume all calls to checkIn and checkOut methods are consistent.
If a customer gets in at time t1 at some station, they get out at time t2 with t2 > t1.
All events happen in chronological order.
*/

class UndergroundSystem {
	unordered_map<int, pair<string, int>> p;
	unordered_map<string, unordered_map<string, pair<double,double>>> d;
public:
	UndergroundSystem() {}
	
	void checkIn(int id, string station, int t) {
		p[id] = {station, t};
	}
	
	void checkOut(int id, string station, int t) {
		string from = p[id].first;
		int inTime = p[id].second;

		pair<double,double>& avg = d[from][station];
		avg = {avg.first + t - inTime, avg.second + 1};
	}
	
	double getAverageTime(string from, string to) {
		return d[from][to].first / d[from][to].second;
	}
};






/*
little cleverness in creating second map
use { key = from + "->" + to }
*/
class UndergroundSystem {
	unordered_map<int, pair<string, int>> p;
	unordered_map<string, pair<double,double>> d;
public:
	UndergroundSystem() {}
	
	void checkIn(int id, string station, int t) {
		p[id] = {station, t};
	}
	
	void checkOut(int id, string station, int t) {
		string from = p[id].first;
		int inTime = p[id].second;

		pair<double,double>& avg = d[from + "->" + station];
		avg = {avg.first + t - inTime, avg.second + 1};
	}
	
	double getAverageTime(string from, string to) {
		string key = from + "->" + to;
		return d[key].first / d[key].second;
	}
};


static auto _______ = [](){
	std::ios::sync_with_stdio(false);
	std::cin.tie(NULL);
	std::cout.tie(NULL);
	return 0;
}();

/**
 * Your UndergroundSystem object will be instantiated and called as such:
 * UndergroundSystem* obj = new UndergroundSystem();
 * obj->checkIn(id,stationName,t);
 * obj->checkOut(id,stationName,t);
 * double param_3 = obj->getAverageTime(startStation,endStation);
 */