#include "Node.h"
#include <iomanip>
#include "termcolor.hpp"
#pragma comment(lib, "Winmm.lib")

node::node(int num, std::string tsk, std::string ctg, int cnt, bool chec) {
    task = tsk;
    ID = cnt;
    number = num;
    category = ctg;
    notification = 1;
    completed = chec;
    prev = nullptr;
    next = nullptr;
    timer = { 0 };
    subtasks = {};
}

/*std::ostream& operator<<(std::ostream& out, node const object) {
	out << "|" << std::setfill(' ') << std::setw(5) << "|" << object.ID << "|" << std::setfill(' ') << std::setw(20) << "|" << object.number << "|" << std::setfill(' ') << std::setw(20) << "|" << object.category << "|" << std::setfill(' ') << std::setw(30) << "|" << object.task << "|" << std::setw(10) << "|" << object.timer.tm_mday << "/" << object.timer.tm_mon + 1 << "/" << object.timer.tm_year + 1900 << "|" << std::setfill(' ') << std::setw(20) << "|" << object.timer.tm_hour << ":" << object.timer.tm_min << "|" << std::setw(10) << "|" <<  std::endl;
	return out;
}*/

void node::set_timer(int year, int month, int day, int hour, int min)
{
    timer.tm_sec = 0;
    timer.tm_min = min;
    timer.tm_hour = hour;
    timer.tm_mday = day;
    timer.tm_mon = month;
    timer.tm_year = year;
}

bool node::has_subtasks() {
    if (!this)return false;
    if (subtasks.size() == 0) return false;
    return true;
}

bool node::check_alarm()
{
    time_t now;
    now = time(0);
    if (difftime(now, mktime(&timer)) <= 10 && difftime(now, mktime(&timer)) >= -10 &&notification !=-1 &&completed == false && timer.tm_year > 0)
    {
        notification--;
        if (notification == -1)
        {
            fort::char_table table;
            table << fort::header;
            table[0][0] = "ID";
            table[0][1] = "Priority";
            table[0][2] = "Category";
            table[0][3] = "Description";
            table[0][4] = "Date(d/m/y)";
            table[0][5] = "Time(h:m)";
            table << fort::endr;
            string day, month, year, hour, minute;
            day = to_string(this->timer.tm_mday);
            month = to_string((this->timer.tm_mon) + 1);
            year = to_string((this->timer.tm_year) + 1900);
            hour = to_string(this->timer.tm_hour);
            minute = to_string(this->timer.tm_min);
            cout << termcolor::red << "This Task is Due now" << endl;
            table << this->ID << this->number << this->category << this->task << day + "/" + month + '/' + year << hour + ':' + minute << fort::endr;
            cout << termcolor::red << endl << table.to_string() << endl;
            cout << termcolor::reset;
        }

        return true;
    }
    return false;
}