// https://leetcode.com/problems/snapshot-array/

class SnapshotArray {
	int id;
	unordered_map<int, unordered_map<int,int>> M;
public:
	SnapshotArray(int length) {
		this->id = 0;
	}
	
	void set(int index, int val) {
		M[id][index] = val;
	}
	
	int snap() {
		int ans = id++;
		M[id] = M[id-1];
		return ans;
	}
	
	int get(int index, int snap_id) {
		return M[snap_id][index];
	}
};

/**
 * Your SnapshotArray object will be instantiated and called as such:
 * SnapshotArray* obj = new SnapshotArray(length);
 * obj->set(index,val);
 * int param_2 = obj->snap();
 * int param_3 = obj->get(index,snap_id);
 */