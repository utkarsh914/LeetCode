// https://leetcode.com/problems/circular-array-loop/

class Solution {
public:
	bool circularArrayLoop(vector<int>& n) {
		int size = n.size();
		bool vis[size + 1];
		
		for (int i=0; i < size-1; i++) {
			memset(vis, 0, sizeof(vis));
			int j = i, steps = 0;
			while (!vis[j]) {
				vis[j] = true;
				j = (j + n[j]) % size;
				if (j<0) j += size;
				if (n[i]>0 != n[j]>0) break; // if different direction
				if (i==j && ++steps>1) return true;
			}
		}
		
		return false;
	}
};







/*
Just think it as finding a loop in Linkedlist, except that loops with only 1 element do not count.
Use a slow and fast pointer, slow pointer moves 1 step a time while fast pointer moves 2 steps a time.
If there is a loop (fast == slow), we return true, else if we meet element with different directions,
then the search fail, we set all elements along the way to 0.
Because 0 is fail for sure so when later search meet 0 we know the search will fail.
*/

public class Solution {
	int len;
	/**
	 * Moves the pointer 'i' ahead one iteration.
	 */
	private int advance(int[] nums, int i) {
		i += nums[i];
		if (i < 0) i += len;
		else if (i > len - 1) i %= len;
		return i;
	}
	
	public boolean circularArrayLoop(int[] nums) {
		// Handle bad input
		if (nums == null || nums.length < 2) return false;
		
		len = nums.length;
		
		/**
		 * Check every possible start location.
		 * We may start at a short-loop, for instance, but the Array
		 * may still contain a valid loop.
		 */
		for (int i = 0; i < len; i++) {
			/**
			 * We set elements to 0 which are on known non-loop paths.
			 * So, if we encounter a 0, we know we're not on a loop path.
			 * So, move to the next start location in the list.
			 */
			if (nums[i] == 0) continue;
			
			// Stagger our starts, so we don't conclude we've found a loop,
			// as we might otherwise when slow == fast.
			int slow = i, fast = advance(nums, slow);
			
			/** 
			 * Whether i is positive or negative defines our direction, so if
			 * the directions differ, so too will the signs.
			 * If the signs differ, we can't be in a 'forward' or a 'backward'
			 * loop, so we exit the traverse.
			 */
			while (nums[i] * nums[fast] > 0 &&
					nums[i] * nums[advance(nums, fast)] > 0) {
				if (slow == fast) {
					if (slow == advance(nums, slow)) break; // 1-element loop
					return true;
				}
				slow = advance(nums, slow);
				fast = advance(nums, advance(nums, fast));
			}
			
			/**
			 * If we're here, we didn't find a loop, so we know this path
			 * doesn't have a loop, so we re-traverse it until we reverse
			 * direction or encounter a '0' element.
			 * During the re-traverse, we set each element we see to 0.
			 */
			slow = i;
			int sgn = nums[i];
			while (sgn * nums[slow] > 0) {
				int tmp = advance(nums, slow);
				nums[slow] = 0;
				slow = tmp;
			}
		}
		
		// We've tested the whole array and have not found a loop,
		// therefore there isn't one, so return false.
		return false;
	}
}