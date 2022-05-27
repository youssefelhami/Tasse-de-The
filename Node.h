#pragma once
#include <iostream>
#include <string>
#include <time.h>
#include "fort.hpp"
#include <vector>
using namespace std;
class node
{
public:
    node(int num, std::string task, std::string category, int cnt, bool check = false);
    int number;
    int ID;
    tm timer;
    std::string task;
    std::string category;
    node* next = nullptr;
    vector<string> subtasks;
    node* prev = nullptr;
    int notification;
    bool has_subtasks();
    bool completed;
    void set_timer(int year, int month, int day, int hour, int min);
    bool check_alarm();
    //friend std::ostream& operator<<(std::ostream& out, node);
};
