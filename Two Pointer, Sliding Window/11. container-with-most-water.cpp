// https://leetcode.com/problems/container-with-most-water/

/*
for every element in height array, we find the largest container we can make,
that has height equal to current element. So, we need to find left max, and right max for this ele
and area will be diff bw left-max/right-mx indices * height of current element;

we can store left and right max for every element, and then do the calculation,
but we can also do it in one pass using 2 pointers

similar to largest rectangle in a histogram
keep track of left max, and right max value;

if left ele is smaller than or equal to right val,
it is right time to update the value corresponding to left.
Bcz at this time there will be max diff bw left and right ptr,
so we get the widest container with height = height[i], and width = (j-i);

similarly, for other case, it would be right time to update for height[j];
*/


class Solution {
public:
	int maxArea(vector<int>& height) {
		int i = 0, j = height.size()-1;
		int lmax = i, rmax = j;
		int maxWater = 0;
		
		while (i < j) {
			if (height[i] > height[lmax]) lmax = i;
			if (height[j] > height[rmax]) rmax = j;
			if (height[i] <= height[j])
				maxWater = max(maxWater, height[i++]*(rmax-lmax));
			else
				maxWater = max(maxWater, height[j--]*(rmax-lmax));
		}
		
		return maxWater;
	}
};


/*
tracking left max and right max isn't necessary
instead use i, j itself in place of lmax/rmax
*/
class Solution {
public:
	int maxArea(vector<int>& h) {
		int i = 0, j = h.size()-1, maxArea = 0;
		while (i < j) {
			if (h[i] <= h[j]) {
				int curArea = h[i] * (j-i);
				maxArea = max(maxArea, curArea);
				i++;
			} else {
				int curArea = h[j] * (j-i);
				maxArea = max(maxArea, curArea);
				j--;
			}
		}
		return maxArea;
	}
};



/*
Start by evaluating the widest container,using the first and the last line.
All other possible containers are less wide, so to hold more water, they need to be higher.
Thus, after evaluating that widest container, skip lines at both ends that don't support a higher height.
Then evaluate that new container we arrived at. Repeat until there are no more possible containers left.
*/
C++

int maxArea(vector<int>& height) {
	int water = 0;
	int i = 0, j = height.size() - 1;
	while (i < j) {
		int h = min(height[i], height[j]);
		water = max(water, (j - i) * h);
		while (height[i] <= h && i < j) i++;
		while (height[j] <= h && i < j) j--;
	}
	return water;
}


/*
Idea / Proof: move the smaller indices inside, since you've already considered the max contanier it can make.
And any further container made by this smaller index will certainly be smaller capacity
(as it will be less wider than currently)

The widest container (using first and last line) is a good candidate, because of its width.
Its water level is the height of the smaller one of first and last line.
All other containers are less wide and thus would need a higher water level in order to hold more water.
The smaller one of first and last line doesn't support a higher water level and can thus be safely removed from further consideration.
Implementation: (Python)

class Solution:
	def maxArea(self, height):
		i, j = 0, len(height) - 1
		water = 0
		while i < j:
			water = max(water, (j - i) * min(height[i], height[j]))
			if height[i] < height[j]:
				i += 1
			else:
				j -= 1
		return water
*/