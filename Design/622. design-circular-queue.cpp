// https://leetcode.com/problems/design-circular-queue/

class MyCircularQueue {
	int size, maxSize, head, tail;
	vector<int> q;
public:
	MyCircularQueue(int k) {
		this->size = 0;
		this->maxSize = k;
		this->q.resize(k);
		this->head = 0;
		this->tail = 0;
	}
	
	bool enQueue(int value) {
		if (isFull()) return false;
		q[tail] = value;
		tail = (tail + 1) % maxSize;
		size++;
		return true;
	}
	
	bool deQueue() {
		if (isEmpty()) return false;
		head = (head + 1) % maxSize;
		size--;
		return true;
	}
	
	int Front() {
		if (size == 0) return -1;
		return q[head];
	}
	
	int Rear() {
		if (size == 0) return -1;
		int i = (tail-1 + maxSize) % maxSize;
		return q[i];
	}
	
	bool isEmpty() {
		return size == 0;
	}
	
	bool isFull() {
		return size == maxSize;
	}
};

/**
 * Your MyCircularQueue object will be instantiated and called as such:
 * MyCircularQueue* obj = new MyCircularQueue(k);
 * bool param_1 = obj->enQueue(value);
 * bool param_2 = obj->deQueue();
 * int param_3 = obj->Front();
 * int param_4 = obj->Rear();
 * bool param_5 = obj->isEmpty();
 * bool param_6 = obj->isFull();
 */
/*
2 0 0
*/
