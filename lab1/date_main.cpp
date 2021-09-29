#include "date.h"
#include "matrix.h"
#include "graph.h"

Date::Date(int year, int month, int day, int hour, int min, int sec) {
    isLeapYear = isLeap(year);
    this->year = year;

    if (month > 12 || month <= 0) {
        std::cout << "Incorrect month" << std::endl;
        this->month = 1;
    }
    else
        this->month = month;

    if (day > maxDay()) {
        std::cout << "Incorrect day" << std::endl;
        this->day = 1;
    }
    else
        this->day = day;

    if (hour > 24 || hour < 0) {
        std::cout << "Incorrect hour " << std::endl;
        this->hour = 1;
    }
    else
        this->hour = hour;
    if (min > 60 || min < 00) {
        std::cout << "Incorrent minutes" << std::endl;
        this->min = 1;
    }
    else
        this->min = min;
    if (sec > 60 || sec < 0) {
        std::cout << "Incorrect sec" << std::endl;
        this->sec = 1;
    }
    else
        this->sec = sec;

    dayOfTheWeek();
    counterOfDaysAtYear();
}



Date::Date(int year, int month, int day) {
    isLeapYear = isLeap(year);

    this->year = year;

    if (month > 12 || month <= 0) {
        std::cout << "Incorrect month" << std::endl;;
        this->month = 1;
    }
    else
        this->month = month;

    if (day > maxDay()) {
        std::cout << "Incorrect day" << std::endl;
        this->day = 1;
    }
    else
        this->day = day;

    hour = min = sec = 1;

    dayOfTheWeek();
    counterOfDaysAtYear();
}



//Zellers algorithm
void Date::dayOfTheWeek() {
    int temp_year = year;
    int code_month;
    if (month > 2)
        code_month = month; //for march to december month code is same as month
    else {
        code_month = 12 + month;  //for Jan and Feb, month code will be 13 and 14
        temp_year--;//decrease year for month Jan and Feb
    }
    int first_temp = temp_year % 100;
    int second_temp = temp_year / 100;
    int index = (day + floor((13 * code_month + 1) / 5) + first_temp + floor(first_temp / 4) + floor(second_temp / 4) + (5 * second_temp));
    index = index % 7;
    indexTheDayOfWeek = index;
}


void Date::counterOfDaysAtYear() {
    int daysOfMonth[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
    if (isLeapYear) {
        daysOfMonth[1] = 29;
    }
    int counter = 0;
    for (int i = 0; i < month - 1; i++) {
        counter += daysOfMonth[i];
    }
    counter += day;
    countDayYear = counter;
}



bool Date::isLeap(int y)const {
    return ((y % 4 == 0 && y % 100 != 0) || y % 400 == 0);
}

int Date::maxDay() const {
    int days[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
    if (isLeapYear)
        days[1] = 29;
    return days[month - 1];
}




long long Date::countSecForData()const {
    long long counter = countDayYear * 24 * 60 * 60 + hour * 60 * 60 + min * 60 + sec;
    for (int i = 1; i < year; i++) {
        if ((i % 4 == 0 && i % 100 != 0) || i % 400 == 0)
            counter += 366 * 24 * 60 * 60;
        else
            counter += 365 * 24 * 60 * 60;

    }
    return counter;
}


void Date::createNewDataBySec(long long current_sec) {
    year = month = 1;
    while (current_sec >= 365 * 24 * 60 * 60) {
        if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) {
            if (current_sec >= 366 * 24 * 60 * 60) {
                current_sec -= 366 * 24 * 60 * 60;
            }
        }
        else {
            current_sec -= 365 * 24 * 60 * 60;
        }
        year++;
    }
    isLeapYear = isLeap(year);

    int counter_days = current_sec / 60 / 60 / 24;
    int array_days_month[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    if (isLeapYear)
        array_days_month[1] = 29;
    for (int i = 0; counter_days > array_days_month[i]; i++) {
        counter_days -= array_days_month[i];
        month++;
    }
    day = counter_days;


    sec = current_sec % 60;
    current_sec /= 60;
    min = current_sec % 60;
    current_sec /= 60;
    hour = current_sec % 24;
    dayOfTheWeek();
    counterOfDaysAtYear();
}



//DAY OF WEEK WITH boost::DateTime
//const static std::string daysOfWeek[] = {
//    "Sunday",
//    "Monday",
//    "Tuesday",
//    "Wednesday",
//    "Thursday",
//    "Friday",
//    "Saturday"
//};
//
//int getDayOfWeekIndex(int day, int month, int year) {
//    boost::gregorian::date d(year, month, day);
//    std::cout<<daysOfWeek[d.day_of_week()];
//}
//

