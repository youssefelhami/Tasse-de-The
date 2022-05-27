#include "LinkedList.h"
#include <iomanip>
#include "fort.hpp"
#include <nlohmann/json.hpp>
#include <vector>
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

using namespace std;
LinkedList::LinkedList() {
    head = nullptr;
    tail = nullptr;
}

void LinkedList::edit_node(int num, int ID, std::string tsk, std::string ctg, int day, int month, int year, int hour, int minute) {
    if (head == nullptr) return;
    node* temp = search_with_value(ID);
    if (!temp) return;
    temp->task = tsk;
    temp->number = num;
    temp->category = ctg;
    temp->set_timer(year, month, day, hour, minute);
}

string stringify(const vector<string>& v)
{
    stringstream ss;
    ss << "{\"subtasks\":[\"";
    for (size_t i = 0; i < v.size(); i++) {
        if (i != 0) ss << "\"";
        ss << v[i];
        if (i < v.size() - 1){
            ss << "\",";
        }else{
            ss << "\"";
        }
    }
    ss << "]}";
    return ss.str();
}

void LinkedList::add_node(int num, int ID, std::string tsk, std::string ctg, int day, int month, int year, int hour, int minute, bool completed) {
    if (head == nullptr) {
        head = new node(num, tsk, ctg, ID, completed);
//        head = new node(num, tsk, ctg, ID, completed);
        head->set_timer(year, month, day, hour, minute);
        head->prev = head->next = nullptr;
        tail = head;
    }
    else {
        node* temp;
        temp = head;
        while (temp->next) {
            temp = temp->next;
        }
        temp->next = new node(num, tsk, ctg, ID, completed);
        temp->next->set_timer(year, month, day, hour, minute);
        temp->next->prev = temp;
        tail = temp->next;
    }
}

std::vector<std::vector<std::string>> LinkedList::exportNode(int index) {
    vector<vector<string>> exportedList;
    node* temp = find_index(index);
    while (temp != nullptr) {
        vector<string> vNode;
        vNode.push_back(to_string(temp->number));
        vNode.push_back(to_string(temp->ID));
        vNode.push_back(temp->task);
        vNode.push_back(temp->category);
        vNode.push_back(to_string(temp->timer.tm_mday));
        vNode.push_back(to_string((temp->timer.tm_mon) + 1));
        vNode.push_back(to_string((temp->timer.tm_year) + 1900));
        vNode.push_back(to_string(temp->timer.tm_hour));
        vNode.push_back(to_string(temp->timer.tm_min));
        vNode.push_back(to_string(0));
        vNode.push_back(to_string(temp->completed));
        if(temp->subtasks.size() > 0){
            vNode.push_back(stringify(temp->subtasks));
        }else{
            vNode.emplace_back("[]");
        }
        exportedList.push_back(vNode);
        temp = temp->next;
    }
    return exportedList;
}

string LinkedList::display_list(int index, string condition) {
    if (!head) {
        return "The list is empty";
    }
    node* temp = find_index(index);
    fort::char_table table;
    table << fort::header;
    table[0][0] = "ID";
    table[0][1] = "Priority";
    table[0][2] = "Category";
    table[0][3] = "Description";
    table[0][4] = "Date(d/m/y)";
    table[0][5] = "Time(h:m)";
    table[0][6] = "Status";
    table << fort::endr;
    string day, month, year, hour, minute, status;
    if (condition == "All") {
        while (temp != nullptr) {
            day = to_string(temp->timer.tm_mday);
            month = to_string((temp->timer.tm_mon) + 1);
            year = to_string((temp->timer.tm_year) + 1900);
            hour = to_string(temp->timer.tm_hour);
            minute = to_string(temp->timer.tm_min);
            if (temp->completed == false) {
                status = "Incomplete";
            }
            else
            {
                status = "Complete";
            }
            table << temp->ID << temp->number << temp->category << temp->task << day + "/" + month + '/' + year << hour + ':' + minute << status << fort::endr;
            temp = temp->next;
        }
    }
    else if (condition == "Completed") {
        while (temp != nullptr) {
            day = to_string(temp->timer.tm_mday);
            month = to_string((temp->timer.tm_mon) + 1);
            year = to_string((temp->timer.tm_year) + 1900);
            hour = to_string(temp->timer.tm_hour);
            minute = to_string(temp->timer.tm_min);
            if (temp->completed == false) {
                status = "Incomplete";
            }
            else
            {
                status = "Complete";
            }
            if (status == "Complete")table << temp->ID << temp->number << temp->category << temp->task << day + "/" + month + '/' + year << hour + ':' + minute << status << fort::endr;
            temp = temp->next;
        }
    }
    else if (condition == "Incomplete") {
        while (temp != nullptr) {
            day = to_string(temp->timer.tm_mday);
            month = to_string((temp->timer.tm_mon) + 1);
            year = to_string((temp->timer.tm_year) + 1900);
            hour = to_string(temp->timer.tm_hour);
            minute = to_string(temp->timer.tm_min);
            if (temp->completed == false) {
                status = "Incomplete";
            }
            else
            {
                status = "Complete";
            }
            if (status == "Incomplete")table << temp->ID << temp->number << temp->category << temp->task << day + "/" + month + '/' + year << hour + ':' + minute << status << fort::endr;
            temp = temp->next;
        }
    }
    else {
        while (temp != nullptr) {
            day = to_string(temp->timer.tm_mday);
            month = to_string((temp->timer.tm_mon) + 1);
            year = to_string((temp->timer.tm_year) + 1900);
            hour = to_string(temp->timer.tm_hour);
            minute = to_string(temp->timer.tm_min);
            if (temp->completed == false) {
                status = "Incomplete";
            }
            else
            {
                status = "Complete";
            }
            if (temp->category == condition)table << temp->ID << temp->number << temp->category << temp->task << day + "/" + month + '/' + year << hour + ':' + minute << status << fort::endr;
            temp = temp->next;
        }
    }
    return table.to_string();
}

/*void LinkedList::print_backward() {
    if (!tail) {
        std::cout << "The list is empty" << std::endl;
        return;
    }
    node* temp = tail;
    int counter = 0;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 11);
    std::cout << std::setw(10) << "Task ID: " << std::setw(25) << "Task Priority: " << std::setw(25) << "Task Category: " << std::setw(35) << "Task Description: " << std::endl;
    std::cout << std::string(95, '-') << std::endl;
    SetConsoleTextAttribute(hConsole, 15);
    while (temp != nullptr) {
        std::cout << std::setw(10) << (counter++) + 1 << std::setw(25) << temp->number << std::setw(25) << temp->category << std::setw(35) << temp->task << std::endl;
        temp = temp->prev;
    }
}*/

void LinkedList::complete_node(int id) {
    node* temp = search_with_value(id);
    temp->completed = true;
}

void LinkedList::push_node(int num, std::string tsk) {
    node* temp = new node(num, tsk, "", 0);
    if (!head) {
        head = tail = temp;
        return;
    }
    head->prev = temp;
    temp->next = head;
    head = temp;
}

bool LinkedList::insert_node(int num, const int& index) {
    int counter = 0;
    node* temp = head;
    node* add_this = new node(num, "", "", 0);
    while (temp != nullptr && counter < index - 1) {
        temp = temp->next;
        counter++;
    }
    if (temp == nullptr || counter != index - 1) {
        return false;
    }
    add_this->next = temp->next;
    temp->next->prev = add_this;
    add_this->prev = temp;
    temp->next = add_this;
    return true;
}

void LinkedList::add_subtask(int id, string task) {
    if (head == nullptr) return;
    node* parent = search_with_value(id);
    if (!parent) return;
    parent->subtasks.push_back(task); return;
}

void LinkedList::remove_subtask(int parent_id, int subtask_id) {
    if (head == nullptr) return;
    node* parent = search_with_value(parent_id);
    if (!parent) return;
    if (!parent->has_subtasks()) return;
    if (parent->subtasks.size() < subtask_id) return;
    parent->subtasks.erase(parent->subtasks.begin() + subtask_id);
}


string LinkedList::show_subtasks(int taskID) {
    node* parent = search_with_value(taskID);
    if (!parent) return "This Task does not Exist";
    if (!parent->has_subtasks()) return "There are no subtasks for this task";
    else{
        fort::char_table table;
        table << fort::header;
        table[0][0] = "Subtask ID";
        table[0][1] = "Subtask Description";
        table << fort::endr;
        for (auto i : parent->subtasks){
            int count = 1;
            table << count << i<<fort::endr;
        }
        return table.to_string();
    }
}

void LinkedList::delete_ID(const int ID)
{
        node* temp = search_with_value(ID);
        if (temp == nullptr) return;
        if (n_nodes() == 1)
        {
            head = nullptr;
            return;
        }

        if (temp == head)
        {
            head->next->prev = nullptr;
            head = head->next;
            delete(temp);
            return;
        }
        if (temp != nullptr) {
            temp->prev->next = temp->next;
            if (temp->next) {
                temp->next->prev = temp->prev;
            }
            delete (temp);
        }
}
void LinkedList::delete_index(const int& index = NULL) {
    if (index == 0) {
        node* temp = head;
        head->next->prev = nullptr;
        head = head->next;
        delete(temp);
        return;
    }
    else if (index != NULL) {
        node* temp = head;
        for (int i = 0; i < index; i++) {
            if (temp->next) { temp = temp->next; }
        }
        temp->prev->next = temp->next;
        if (temp->next) {
            temp->next->prev = temp->prev;
        }
        delete(temp);
    }
}

node* LinkedList::pop_node() {
    node* pop = tail;
    tail->prev->next = nullptr;
    tail = tail->prev;
    return pop;
}

void LinkedList::emptyList(){
    node* curr;
    node* prev;
    curr = prev = head;
    while(curr != nullptr){
        prev = curr;
        delete(prev);
        curr = curr->next;
    }
    head = tail = nullptr;
    delete(curr);
}

node* LinkedList::search_with_value(const int& val) {
    node* temp = head;
    while (temp)
    {
        if (temp->ID == val) {
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}
void LinkedList::node_swap(node* left, node* right)
{
    node** p1pn;
    node** p1np;
    node** p2pn;
    node** p2np;
    node* temp;
    if (head == NULL || left == NULL || right == NULL || right == left)
        return;
    if (head == right)
        p1pn = &head;
    else
        p1pn = &right->prev->next;
    if (head == left)
        p2pn = &head;
    else
        p2pn = &left->prev->next;
    if (right->next == NULL) {
        p1np = &tail;
        tail = right;
    }
    else
        p1np = &right->next->prev;

    if (left->next == NULL) {
        p2np = &tail;
        tail = left;
    }
    else
        p2np = &left->next->prev;

    *p1pn = left;
    *p1np = left;
    *p2pn = right;
    *p2np = right;
    temp = right->prev;
    right->prev = left->prev;
    left->prev = temp;
    temp = right->next;
    right->next = left->next;
    left->next = temp;
}
node* LinkedList::find_index(int i)
{
    node* temp = head;
    for (int k = 0; k < i; k++) temp = temp->next;
    return temp;
}

void LinkedList::swap_index(int i, int j)
{
    node* left = find_index(i);
    node* right = find_index(j);
    node_swap(left, right);
}

int LinkedList::n_nodes() // calculates number of nodes
{
    if (head == 0) return 0;
    int n = 1;
    node* temp = head;
    while (temp->next != nullptr) {
        temp = temp->next;
        n++;
    }
    return n;
}

void LinkedList::sort_priority(int high_low) //bubble sort
{
    int n = n_nodes();
    if (n < 1) return;
    node* temp1 = head;
    node* temp2 = head;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++)
        {
            temp1 = find_index(i);
            temp2 = find_index(j);
            if (temp2->number < temp1->number) {
                swap_index(i, j);
            }
        }
    }
    // 0 is low to high 1 is high to low;
    if (high_low)
    {
        for (int i = 0; i < n / 2; i++) swap_index(i, n - i - 1);
    }
}

int LinkedList::smaller(node* temp1, node* temp2)
{
    if (temp1->timer.tm_year != temp2->timer.tm_year)
    {
        if (temp1->timer.tm_year < temp2->timer.tm_year)
            return 1;
        else return 0;
    }
    else if (temp1->timer.tm_mon != temp2->timer.tm_mon)
    {
        if (temp1->timer.tm_mon < temp2->timer.tm_mon)
            return 1;
        else return 0;
    }
    else if (temp1->timer.tm_mday != temp2->timer.tm_mday)
    {
        if (temp1->timer.tm_mday < temp2->timer.tm_mday)
            return 1;
        else return 0;
    }
    else if (temp1->timer.tm_hour != temp2->timer.tm_hour)
    {
        if (temp1->timer.tm_hour < temp2->timer.tm_hour)
            return 1;
        else return 0;
    }
    else if (temp1->timer.tm_min != temp2->timer.tm_min)
    {
        if (temp1->timer.tm_min < temp2->timer.tm_min)
            return 1;
        else return 0;
    }
    else return 0;
}

bool LinkedList::check_notifications()
{
#ifdef __APPLE__
    usleep(1000);
#else
    Sleep(1000);
#endif

    node* temp = head;

    if (head == nullptr) return false;
    for (int i = 0; i < n_nodes(); i++)
    {
        if (temp->check_alarm()) return true;
        temp = temp->next;
    }
    return false;
}


void LinkedList::sort_time(int high_low) //bubble sort
{
    int n = n_nodes();
    if (n < 1) return;
    node* temp1 = head;
    node* temp2 = head;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++)
        {
            temp1 = find_index(i);
            temp2 = find_index(j);
            if (smaller(temp2, temp1)) {
                swap_index(i, j);
            }
        }
    }
    // 0 is low to high 1 is high to low;
    if (high_low)
    {
        for (int i = 0; i < n / 2; i++) swap_index(i, n - i - 1);
    }
}



/*std::ostream& operator<<(std::ostream& out, LinkedList object) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 11);
    std::cout << std::string(144, '-') << std::endl;
    std::cout << "|" << std::setfill(' ') << std::setw(10) << "|" << "Task ID" << "|" << std::setfill(' ') << std::setw(20) << "|" << "Task Priority" << "|" << std::setfill(' ') << std::setw(20) << "|" << "Task Category" << "|" << std::setfill(' ') << std::setw(30) << "|" << "Task Description" << "|" << setw(10) << "|" << "Date" << "|" << std::setfill(' ') << std::setw(20) << "|" << "Time" << "|" << std::setw(10) << "|" << std::endl;
    std::cout << std::string(144, '-') << std::endl;
    SetConsoleTextAttribute(hConsole, 15);
    int n = object.n_nodes();
    for (int i = 0; i < n; i++)
        cout << object.print_forward(i);
    return out;
}*/