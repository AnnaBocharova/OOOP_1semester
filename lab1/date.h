#pragma once
#pragma once
#include<iostream>
#include<fstream>
#include "graph.h"
#include "matrix.h"

class Records {
public:
    int year;
    int month;
    long long day;
    long long hour;
    long long min;
    long long sec;
    Records() = default;
    friend std::ostream& operator<< (std::ostream& output, const Records& data) {
        std::cout << "year= " << data.year << std::endl;
        std::cout << "mont= " << data.month << std::endl;
        std::cout << "day= " << data.day << std::endl;
        std::cout << "hour= " << data.hour << std::endl;
        std::cout << "minutes= " << data.min << std::endl;
        std::cout << "sec= " << data.sec << std::endl;
        std::cout << "_______________________________________________" << std::endl;
        return output;
    }

};

class Date {
private:
    int year;
    int month;
    int day;
    int hour;
    int min;
    int sec;


    int indexTheDayOfWeek;
    int countDayYear;
    bool isLeapYear;

    bool isLeap(int)const;
    int maxDay()const;

    void dayOfTheWeek();
    void counterOfDaysAtYear();


public:
    Date(int year, int month, int day, int hour, int min, int sec);
    Date(int year, int day, int month);
    Date() = default;

    long long countSecForData()const;
    void createNewDataBySec(long long newSec);

    friend bool operator==(const Date& first_data, const Date& second_data) {
        return (first_data.year == second_data.year && first_data.month == second_data.month && first_data.day == second_data.day
            && first_data.hour == second_data.hour && first_data.min == second_data.min && first_data.sec == second_data.sec);
    }
    friend bool operator>(const Date& first_data, const Date& second_data) {
        if (first_data == second_data)
            return false;
        if (first_data.year != second_data.year)
            return first_data.year > second_data.year;
        if (first_data.month != second_data.month)
            return first_data.month > second_data.month;
        if (first_data.day != second_data.day)
            return first_data.day > second_data.day;
        if (first_data.hour != second_data.hour)
            return first_data.hour > second_data.hour;
        if (first_data.min != second_data.min)
            return first_data.min > second_data.min;
        if (first_data.sec != second_data.sec)
            return first_data.sec > second_data.sec;
    }

    friend bool operator<(const Date& first_data, const Date& second_data) {
        return second_data > first_data;
    }

    friend Records operator- (const Date& first_date, const Date& second_date) {
        Records result{};
        if (second_date > first_date) {
            std::cout << "First date is less than second date" << std::endl;
            return result;
        }
        else {
            int distinction_year = first_date.year - second_date.year;
            result.sec = distinction_year * 365 * 24 * 60 * 60;

            long long first_sec = first_date.countDayYear * 24 * 60 * 60 + first_date.hour * 60 * 60 + first_date.sec;
            long long second_sec = second_date.countDayYear * 24 * 60 * 60 + second_date.hour * 60 * 60 + second_date.sec;

            for (int i = 0; i < first_date.year; i++) {
                if ((i % 4 == 0 && i % 100 != 0) || i % 400 == 0) {
                    if (i < second_date.year)
                        second_sec += 366 * 24 * 60 * 60;
                    first_sec += 366 * 24 * 60 * 60;
                }
                else {
                    if (i < second_date.year)
                        second_sec += 365 * 24 * 60 * 60;
                    first_sec += 365 * 24 * 60 * 60;
                }
            }

            result.sec = first_sec - second_sec;
            result.min = result.sec / 60;
            result.hour = result.min / 60;
            result.day = result.hour / 24;
            result.month = result.day / 31;
            result.year = result.year / 12;
            return result;
        }
    }

    friend Date& operator+(Date& date, const Records& record) {
        long long date_sec = date.countSecForData();
        long long result = date_sec + record.sec;
        date.createNewDataBySec(result);
        return date;
    }
    friend Date& operator-(Date& date, const Records& record) {
        long long date_sec = date.countSecForData();
        long long result = date_sec - record.sec;
        date.createNewDataBySec(result);
        return date;
    }

    friend Date& operator+=(Date& first_date, const Records& record) {
        long long date_sec = first_date.countSecForData();
        long long update_sec = date_sec + record.sec;
        first_date.createNewDataBySec(update_sec);
        return first_date;
    }
    friend Date& operator-=(Date& first_date, const Records& record) {
        long long date_sec = first_date.countSecForData();
        long long update_sec = date_sec - record.sec;
        first_date.createNewDataBySec(update_sec);
        return first_date;
    }

    friend std::istream& operator>>(std::istream& input, Date& date) {
        int new_year, new_month, new_day, new_hour, new_min, new_sec;
        std::cout << "Enter new date: " << std::endl;
        std::cout << "Enter year/month/day/hour/minutes/sec: " << std::endl;
        input >> new_year >> new_month, new_day >> new_hour >> new_min >> new_sec;
        Date new_date(new_year, new_month, new_day, new_hour, new_min, new_sec);
        date = new_date;
        return input;

    }


    friend std::ostream& operator<<(std::ostream& output, const Date& date) {
        std::string month_name[] = { "January","February","March","April","May","June","July","August","September","October","November","December" };
        std::string day_name[] = { "Saturday","Sunday","Monday","Tuesday", "Wednesday","Thursday","Friday" };
        output << date.day << "." << month_name[date.month - 1] << "." << date.sec << std::endl;
        output << "Day: " << day_name[date.indexTheDayOfWeek] << std::endl;
        output << "Time: ";
        if (date.hour < 10)
            output << 0;
        output << date.hour << ":";
        if (date.min < 10)
            output << 0;
        output << date.min << ":";
        if (date.sec < 10)
            output << 0;
        output << date.sec << std::endl;
        return output;


    }
};