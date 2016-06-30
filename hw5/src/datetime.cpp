#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>
#include <sstream>
#include <ctime>
#include <iomanip>
#include <stdio.h>
#include <stdlib.h>
#include "../lib/datetime.h"
using namespace std;

DateTime::DateTime()
{
	hour = 0;
	min = 0;
	sec = 0;
	year = 0;
	month = 0;
	day = 0;
}

DateTime::DateTime(int hh, int mm, int ss, int year_, int month_, int day_)
{
	hour = hh;
	min = mm;
	sec = ss;
	year = year_;
	month = month_;
	day = day_;
}

bool DateTime::operator<(const DateTime& other) const
{
	if(year < other.year) {return true;}
	else if(year == other.year){
		if(month < other.month) {return true;}
		else if(month == other.month){
			if(day < other.day) {return true;}
			else if(day == other.day) {
				if(hour < other.hour) {return true;}
				else if (hour == other.hour){
					if(min < other.min){return true;}
					else if(min == other.min){
						if(sec <= other.sec){return true;}
						else if(sec == other.sec){
							return true; //list as consecutive if equal timestamp??
						}
					}
				}
			}
		}

	}
	// else{
		return false;
	// }
}

std::ostream& operator<<(std::ostream& os, const DateTime& other)
{
	os << other.year << "-";
	os << setfill('0') << setw(2) << other.month << "-";
	os << setfill('0') << setw(2) << other.day << " ";

	os << setfill('0') << setw(2)<< other.hour << ":";
	os << setfill('0') << setw(2) << other.min << ":";
	os << setfill('0') << setw(2) << other.sec;

	return os;
}

std::istream& operator>>(std::istream& is, DateTime& dt)
{
	/*is >> dt.year;
	is >> dt.month;
	is >> dt.day;

	is >> dt.hour;
	is >> dt.min;
	is >> dt.sec;
*/
	//HAVENT CHECKED FOR ERROR CHECK (CHECK HEADER FILE FOR DETAILS)!!!!!!!
	// ^^^^^^^^^^^^^
	string temp_str1;
	string temp_str2;
	string date_placeholder;
	string time_placeholder;

	is>>temp_str1;
	date_placeholder = temp_str1.substr(0,4);
	stringstream s1(date_placeholder);
	s1>>dt.year;
	if (s1.fail()){
		time_t rawtime;
 		struct tm * timeinfo;

  		time (&rawtime);
  		timeinfo = localtime(&rawtime);

  		dt.year = timeinfo->tm_year + 1900;
	}
	s1.clear();

	date_placeholder = temp_str1.substr(5, 7);
	s1.str(date_placeholder);
	s1>>dt.month;
	if (s1.fail()){
		time_t rawtime;
 		struct tm * timeinfo;

  		time (&rawtime);
  		timeinfo = localtime(&rawtime);

  		dt.month = timeinfo->tm_mon + 1;
	}
	s1.clear();

	date_placeholder = temp_str1.substr(8, 9);
	s1.str(date_placeholder);
	s1>>dt.day;
	if (s1.fail()){
		time_t rawtime;
 		struct tm * timeinfo;

  		time (&rawtime);
  		timeinfo = localtime(&rawtime);

  		dt.month = timeinfo->tm_wday + 1;
	}
	s1.clear();
				//cout << year << " " << day << endl;
						
	is>>temp_str2;

	time_placeholder = temp_str2.substr(0,2);
	stringstream s2(time_placeholder);
	s2>>dt.hour;
	if (s2.fail()){
		time_t rawtime;
 		struct tm * timeinfo;

  		time (&rawtime);
  		timeinfo = localtime(&rawtime);

  		dt.hour = timeinfo->tm_hour + 1;
	}
	s2.clear();

	time_placeholder = temp_str2.substr(3, 5);
	s2.str(time_placeholder);
	s2>>dt.min;
	if (s2.fail()){
		time_t rawtime;
 		struct tm * timeinfo;

  		time (&rawtime);
  		timeinfo = localtime(&rawtime);

  		dt.min = timeinfo->tm_min + 1;
	}
	s2.clear();

	time_placeholder = temp_str2.substr(6, 7);
	s2.str(time_placeholder);
	s2>>dt.sec;
	if (s2.fail()){
		time_t rawtime;
 		struct tm * timeinfo;

  		time (&rawtime);
  		timeinfo = localtime(&rawtime);

  		dt.sec = timeinfo->tm_sec - 1;
	}
	s2.clear();
							//cout << hr << " " << min << endl;
						


	return is;

}






