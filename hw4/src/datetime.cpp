#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>
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
	else{
		return false;
	}
}

std::ostream& operator<<(std::ostream& os, const DateTime& other)
{
	os << other.year << "-";
	os << other.month << "-";
	os << other.day << " ";

	os << other.hour << "::";
	os << other.min << "::";
	os << other.sec;

	return os;
}

std::istream& operator>>(std::istream& is, DateTime& dt)
{
	is >> dt.year;
	is >> dt.month;
	is >> dt.day;

	is >> dt.hour;
	is >> dt.min;
	is >> dt.sec;

	//HAVENT CHECKED FOR ERROR CHECK (CHECK HEADER FILE FOR DETAILS)!!!!!!!
	// ^^^^^^^^^^^^^

	return is;

}






