// https://leetcode.com/problems/design-browser-history/

class BrowserHistory {

	vector<string> history;
	int curr;

public:
	BrowserHistory(string homepage) {
		history.push_back(homepage);
		curr = 0;
	}
	
	void visit(string url) {
		if (curr < history.size()-1)
			history.erase(history.begin()+curr+1, history.end());
		history.push_back(url);
		curr = history.size()-1;
	}
	
	string back(int steps) {
		if (steps>curr) curr = 0;
		else curr -= steps;
		return history[curr];
	}
	
	string forward(int steps) {
		curr += steps;
		if (curr >= history.size())
			curr = history.size()-1;
		return history[curr];
	}
};

/**
 * Your BrowserHistory object will be instantiated and called as such:
 * BrowserHistory* obj = new BrowserHistory(homepage);
 * obj->visit(url);
 * string param_2 = obj->back(steps);
 * string param_3 = obj->forward(steps);
 */