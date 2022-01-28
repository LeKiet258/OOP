#pragma once
#include<iostream>
#include<vector>

using namespace std;

bool isLeapYear(int year) {
    if (year % 400 == 0)
        return true;

    if (year % 100 == 0)
        return false;

    if (year % 4 == 0)
        return true;
    return false;
}
