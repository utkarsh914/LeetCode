// https://leetcode.com/problems/maximum-frequency-stack/

class FreqStack {
	// array <freq, timestamp, val>
	priority_queue<array<int,3>> pq;
	unordered_map<int, int> freq; // val -> freq
	int time;
public:
	FreqStack() {
		this->freq.clear();
		this->time = 0;
	}
	
	void push(int x) {
		pq.push({ ++freq[x], ++time, x });
	}
	
	int pop() {
		int ans = pq.top()[2];
		--freq[ans];
		pq.pop();
		return ans;
	}
};





// using custom comparator function with pq and hashmap
class FreqStack {
	
	class Comp {
	public:
		// if freq is same, compare on timestamp
		// else compare on freq
		bool operator() (array<int,3>& v1, array<int,3>& v2) {
			if (v1[1] == v2[1]) return v1[2] < v2[2];
			else return v1[1] < v2[1];
		}
	};
	// array -> <val, freq, timestamp>
	priority_queue<array<int,3>, vector<array<int,3>>, Comp> pq;
	unordered_map<int, int> freq;
	int time;
	
public:
	FreqStack() {
		this->freq.clear();
		this->time = 0;
	}
	
	void push(int x) {
		pq.push({ x, ++freq[x], ++time });
	}
	
	int pop() {
		int ans = pq.top()[0];
		--freq[ans];
		pq.pop();
		return ans;
	}
};

/**
 * Your FreqStack object will be instantiated and called as such:
 * FreqStack* obj = new FreqStack();
 * obj->push(x);
 * int param_2 = obj->pop();
 */