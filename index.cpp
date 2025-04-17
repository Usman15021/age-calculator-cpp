#include <iostream>
#include <ctime>  // help to fectch the current date and time
#include <string> // help to use the or storing text like Name ect//

using namespace std;
int main()
{
  time_t now = time(0);                         // get the current date and time
  tm *current_time = localtime(&now);           // convert to readerable formate//
  int curr_day = current_time->tm_mday;         // get the current day of the month(1-31)//
  int curr_month = current_time->tm_mon + 1;    // get the current month (1-12, +1 because january = 0)//
  int curr_year = current_time->tm_year + 1900; // get the current year (1900 + year since 1900)//

  string name;
  cout << "Enter your name:";
  getline(cin, name); // Reads full name including spaces //

  int birth_day, birth_month, birth_year;
  cout << "Enter you birth date(dd mm yyyy):";
  cin >> birth_day >> birth_month >> birth_year; // <-- FIX: Added missing input

  bool valid_input = true;

  // check if month is valid (1-12)
  if (birth_month < 1 || birth_month > 12)
  {
    cout << "Invalid month! Please enter between 1-12.\n"; // FIX: Changed /n to \n
    valid_input = false;
  }

  int max_days;
  if (birth_month == 2) // check if the month is february //
  {
    // Leap year check: Divisible by 4 but not 100 unless also 400
    if ((birth_year % 4 == 0 && birth_year % 100 != 0) || (birth_year % 400 == 0)) // check if the year is leap year..//
    {
      max_days = 29; // february has 29 days in leap year//
    }
    else
    {
      max_days = 28; // february has 28 days in non-leap year//
    }
  }
  else if (birth_month == 4 || birth_month == 6 || birth_month == 9 || birth_month == 11)
  {
    max_days = 30; // april, june, september, november have 30 days//
  }
  else
  {
    max_days = 31; // all other months have 31 days//
  }

  if (birth_day < 1 || birth_day > max_days) // check if the day is valid //
  {
    cout << "Invalid day! this month has only " << max_days << " days.\n"; // FIX: Changed /n to \n
    valid_input = false;
  }

  if (!valid_input)
  {
    return 1;
  }

  int age_years = curr_year - birth_year;   // calculate the age in years//
  int age_month = curr_month - birth_month; // calculate the age in months//
  int age_days = curr_day - birth_day;      // calculate the age in days//

  // fix negative days (e.g if today is march 10 and birthday is march 20)
  if (age_days < 0)
  {
    age_month--; // borrow a month
    int prev_month = curr_month - 1;
    if (prev_month == 0) // wrap around to December if current month is January
    {
      prev_month = 12;
    }

    if (prev_month == 2)
    {
      // February: check if it's a leap year
      if ((curr_year % 4 == 0 && curr_year % 100 != 0) || (curr_year % 400 == 0))
      {
        age_days += 29; // borrow days from February in a leap year
      }
      else
      {
        age_days += 28; // borrow days from February in a non-leap year
      }
    }
    else if (prev_month == 4 || prev_month == 6 || prev_month == 9 || prev_month == 11)
    {
      age_days += 30; // borrow days from months with 30 days
    }
    else
    {
      age_days += 31; // borrow days from months with 31 days
    }
  }

  if (age_month < 0)
  {
    age_years--;
    age_month += 12;
  }

  cout << "\n====Age Calculator====\n";
  cout << "Name : " << name << endl;
  cout << "Birth Date: " << birth_day << "/" << birth_month << "/" << birth_year << endl;
  cout << "Current Date: " << curr_day << "/" << curr_month << "/" << curr_year << endl;
  cout << "--------------------------------\n";
  cout << " Your Age is: " << age_years << " years, " << age_month << " months, and " << age_days << " days\n"; // FIX: Added space before "days"
  cout << "=========\n";

  return 0;
}