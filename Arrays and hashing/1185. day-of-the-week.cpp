
/*
https://leetcode.com/problems/day-of-the-week/

Given a date, return the corresponding day of the week for that date.
The input is given as three integers representing the day, month and year respectively.
Return the answer as one of the following values:
{"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"}.

Example 1:
Input: day = 31, month = 8, year = 2019
Output: "Saturday"

// *************** APPROACH *****************
start your list of day names with the known date of "today", e.g. "Saturday".
Then, find the number of days since the start of the valid range for both your known date and the input date.
Note, the code considers 1, 1, 1971 to be 1 day after the start and so on.
*/

class Solution {
public:
	string dayOfTheWeek(int day, int month, int year) {
		string days[] = {"Saturday", "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday"};
		int daysTillNow = countDays(9, 1, 2021);
		int daysTillGiven = countDays(day,month,year);
		int diff = (daysTillGiven - daysTillNow) % 7;
		if (diff < 0) diff += 7;
		return days[diff];
	}
	
	bool isleap(int y) {
		return y%400==0 or (y%4==0 && y%100!=0);
	}
	
	// calculates no. of days passed from a base date e.g. 01-01-1970
	int countDays(int day, int month, int year) {
		int monthDays[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
		int daysPassed = 0;
		for (int i=1970; i<year; i++)
			daysPassed += 365 + isleap(i);
		for (int i=0; i<month-1; i++)
			daysPassed += monthDays[i];
		if (month > 2)
			daysPassed += isleap(year);
		daysPassed += day;
		return daysPassed;
	}
};