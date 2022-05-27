#define NOMINMAX
#include <iostream>
#include "LinkedList.h"
#include "Node.h"
#include <string>
#include <iomanip>
#include <thread>
#include "DBHandle.h"
#include <vector>
#include <nlohmann/json.hpp>
#include "fort.hpp"
#include "termcolor.hpp"
#include <unistd.h>
string condition = "All";
using json = nlohmann::json;

int tskID = 1;

using namespace std;

template <typename T>
void checkVariables(T& var, string message){
    while (cout << message && !(cin >> var)) {
        cin.clear(); //clear bad input flag
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); //discard input
        cout << "Invalid input; please re-enter.\n";
    }
}

void checkVariables(string& var, std::string message){
    while (cout << message && !(getline(cin, var))) {
        cin.clear(); //clear bad input flag
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); //discard input
        cout << "Invalid input; please re-enter. \n";
    }
}

bool inRange(int x,int low, int high){
    return ((x-low) <= (high-low));
}

template <typename T>
void checkVariables(T& var, string message, int min, int max){
    while (cout << message && !(cin >> var))
    {
        cin.clear(); //clear bad input flag
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); //discard input
        cout << "Invalid input; please re-enter.\n";
    }
    while(var < min || var > max){
        cout << "Range invalid; please re-enter.\n";
        cin >> var;
    }
}

vector<vector<string>> taskReq;

std::vector<std::vector<std::string>> exportedNode;

#ifdef _WIN32
void check_alerts(LinkedList * todo, int * command)
{
    while (true)
    {
        *time = *time + 1;
        if (todo->check_notifications()) ShowWindow(GetConsoleWindow(), SW_RESTORE);
        if (*time > *backround) ShowWindow(GetConsoleWindow(), SW_RESTORE);
        if (*command == -1)
            break;
    }
}
#endif


void todo_list_thread(LinkedList *todo_list, int* command, DBHandle *db)
{
    cout << termcolor::green << "Loading..." << endl;
    cpr::Response tempJS = db->fetchTasks();
    db->initLinkedList(json::parse(tempJS.text), todo_list, tskID);
    while (*command != -1) {
        #ifdef __APPLE__
        system("clear");
        #elif _WIN32
        system("cls");
        #endif

        vector<string> taskArr;
        string table;
        cout <<termcolor::magenta<< setw(50) << "Welcome to the TODO List application" << endl;
        cout << "We are now entering the terminal verion of the todo list: " << endl;

        table = todo_list->display_list(0,condition);
        cout <<termcolor::green<< table << endl;
        cout <<termcolor::reset<< "Please choose an intruction from the following list: " << endl;
        cout << "1-> Add a new task \n2-> Delete an existing task with ID \n3-> Edit a task\n4-> Sort list by priority (descending)\n5-> Sort list by priority (ascending)\n6-> Sort list by soonest task\n7-> Mark task as completed\n8-> Show all completed tasks\n9-> Show all incompleted tasks\n10-> Show tasks in specific category\n11-> Restore to default\n12-> Add Subtask\n13-> Remove Subtask\n14-> Show Subtasks\n15-> Refresh\n-1->Terminate program" << endl;        cout << "Enter command: ";
        cin >> *command;
        switch (*command) {
            case 1: {
                int val, day, month, year, hour, minute;
                string task, ctg;
//                cout << "Enter task description: ";
                cin.ignore((numeric_limits<streamsize>::max)(), '\n');
                checkVariables(task, "Enter task description: ");
                checkVariables(ctg, "Enter task category: ");
                checkVariables(val, "Enter task priority: ");
                cout << "Date/Time \n";
                checkVariables(day, "Enter day (1-31): ",1,31);
                checkVariables(month, "Enter month (1-12): ", 1 ,12);
                checkVariables(year, "Enter year (1900+): ", 1900, 999999);
                checkVariables(hour, "Enter hour (0-23): ", 0,23);
                checkVariables(minute, "Enter minute (0-59): ",0,59);

//                getline(cin, task);
//                cout << "Enter task priority: ";
//                cin >> val;
//                cout << "Enter task category: ";
//                cin >> ctg;
//                cout << "DATE/TIME " << endl;
//                cout << "Enter day: ";
//                cin >> day;
//                cout << "Enter month (1-12): ";
//                cin >> month;
//                cout << "Enter year (1900+): ";
//                cin >> year;
//                cout << "Enter hour (0-23): ";
//                cin >> hour;
//                cout << "Enter minute (0-59): ";
//                cin >> minute;

                taskArr.push_back(to_string(val));
                taskArr.push_back(to_string(tskID));
                taskArr.push_back(task);
                taskArr.push_back(ctg);
                taskArr.push_back(to_string(day));
                taskArr.push_back(to_string(month));
                taskArr.push_back(to_string(year));
                taskArr.push_back(to_string(hour));
                taskArr.push_back(to_string(minute));
                taskArr.push_back(to_string(0));
                taskArr.push_back(to_string(false));
                taskArr.push_back("{}");
                db->create2DVector(taskReq, &taskArr);
                json req = db->constructJSON(taskReq);
                cout << termcolor::green << "Loading..." << endl;
                cpr::Response reqCode = db->insertTask(req);
                auto reqRes = json::parse(reqCode.text);
                int responseCode = db->requestCheck(reqRes);
                db->printStatusCode(responseCode);
                taskReq.clear();
                todo_list->add_node(val, tskID, task, ctg, day, month - 1, year - 1900, hour, minute);
                tskID++;
                break;
            }
            case 2: {
                int del_id;
//                cout << "Enter the task ID you want to delete: " << endl;
//                cin >> del_id;
                checkVariables(del_id, "Enter the task ID you want to delete: ");
                todo_list->delete_ID(del_id);
                exportedNode = todo_list->exportNode(0);
                cpr::Response reqCode = db->emptyDB();
                auto reqRes = json::parse(reqCode.text);
                int responseCode = db->requestCheck(reqRes);
                db->printStatusCode(responseCode);

                // Insert the populated records
                if (exportedNode.size() > 0) {
                    json dReq = db->constructJSON(exportedNode);
                    reqCode = db->insertTask(dReq);
                    reqRes = json::parse(reqCode.text);
                    responseCode = db->requestCheck(reqRes);
                }
                break;
            }
            case 3: {
                int i = 0;
                cout << "Which task do you want to edit " << endl;
                cout << "'''ENTER ID'''" << endl;
                cin >> i;
                int val, day, month, year, hour, minute;
                string task, ctg;
//                cout << "Enter task description: ";
                cin.ignore((numeric_limits<streamsize>::max)(), '\n');
                checkVariables(task, "Enter task description: ");
                checkVariables(ctg, "Enter task category: ");
                checkVariables(val, "Enter task priority: ");
                cout << "Date/Time \n";
                checkVariables(day, "Enter day (1-31): ",1,31);
                checkVariables(month, "Enter month (1-12): ", 1 ,12);
                checkVariables(year, "Enter year (1900+): ", 1900, 999999);
                checkVariables(hour, "Enter hour (0-23): ", 0,23);
                checkVariables(minute, "Enter minute (0-59): ",0,59);
//                getline(cin, task);
//                cout << "Enter task priority: ";
//                cin >> val;
//                cout << "Enter task category: ";
//                cin >> ctg;
//                cout << "DATE/TIME " << endl;
//                cout << "Enter day: ";
//                cin >> day;
//                cout << "Enter month (1-12): ";
//                cin >> month;
//                cout << "Enter year (1900+): ";
//                cin >> year;
//                cout << "Enter hour (0-23): ";
//                cin >> hour;
//                cout << "Enter minute (0-59): ";
//                cin >> minute;
                todo_list->edit_node(val, i, task, ctg, day, month - 1, year - 1900, hour, minute);
                exportedNode = todo_list->exportNode(0);
                //resetting IDs
                cpr::Response reqCode = db->emptyDB();
                auto reqRes = json::parse(reqCode.text);
                int responseCode = db->requestCheck(reqRes);
                db->printStatusCode(responseCode);
                // Inserting edited records
                json req = db->constructJSON(exportedNode);
                reqCode = db->insertTask(req);
                reqRes = json::parse(reqCode.text);
                responseCode = db->requestCheck(reqRes);
                db->printStatusCode(responseCode);
                //            int reqCode = db->insertTask(req);
                //            if(reqCode == 200){
                //                cout << "Task edited successfully!" << endl;
                //            }
                break;
            }
            case 4:
                todo_list->sort_priority(1);
                break;
            case 5:
                todo_list->sort_priority(0);
                break;
            case 6:
                todo_list->sort_time(0);
                break;
                /*else if (*command == 9) {
                    mciSendString("open \"Alarm.mp3\" type mpegvideo alias mp3", NULL, 0, NULL);
                    mciSendString("play mp3", NULL, 0, NULL);
                    PlaySound("TF050.WAV", NULL, SND_SYNC);
                    PlaySound("TF050.WAV", NULL, SND_SYNC);
                    PlaySound("TF050.WAV", NULL, SND_SYNC);
                    Sleep(1500);
                    cout << "Audio file playing...\n\n"<<endl;
                    system("PAUSE");
                }*/
            case 7: {
                int id;
//                cout << "Enter Node ID: " << endl;
//                cin >> id;
                checkVariables(id, "Enter Node ID: ");

                todo_list->complete_node(id);
                cpr::Response reqCode = db->emptyDB();
                auto reqRes = json::parse(reqCode.text);
                int responseCode = db->requestCheck(reqRes);
                exportedNode = todo_list->exportNode(0);
                json dReq = db->constructJSON(exportedNode);

                reqCode = db->insertTask(dReq);
                reqRes = json::parse(reqCode.text);
                responseCode = db->requestCheck(reqRes);
                break;
            }
            case 8:
                condition = "Completed";
                break;
            case 9:
                condition = "Incomplete";
                break;
            case 10:
                cout << "Enter category";
                cin >> condition;
                break;
            case 11:
                condition = "All";
                break;
            case 12: {
                int taskID;
                string subtask;
                checkVariables(taskID, "Enter task ID: ");
                cin.ignore((numeric_limits<streamsize>::max)(), '\n');
                checkVariables(subtask, "Enter subtask: ");
                todo_list->add_subtask(taskID, subtask);

                cpr::Response reqCode = db->emptyDB();
                auto reqRes = json::parse(reqCode.text);
                int responseCode = db->requestCheck(reqRes);
                exportedNode = todo_list->exportNode(0);
                json dReq = db->constructJSON(exportedNode);

                reqCode = db->insertTask(dReq);
                reqRes = json::parse(reqCode.text);
                responseCode = db->requestCheck(reqRes);


                break;
            }
            case 13:{
                int taskID, subtaskNum;
                checkVariables(taskID, "Enter task ID: ");
                checkVariables(subtaskNum, "Enter subtask number: ");
                todo_list->remove_subtask(taskID, subtaskNum);
                cpr::Response reqCode = db->emptyDB();
                auto reqRes = json::parse(reqCode.text);
                int responseCode = db->requestCheck(reqRes);
                exportedNode = todo_list->exportNode(0);
                json dReq = db->constructJSON(exportedNode);

                reqCode = db->insertTask(dReq);
                reqRes = json::parse(reqCode.text);
                responseCode = db->requestCheck(reqRes);
                break;
            }
            case 14:{
                int taskID;
                checkVariables(taskID, "Enter task ID: ");
                string subList = todo_list->show_subtasks(taskID);
                cout << termcolor::yellow << subList << endl;
                #ifdef __APPLE__ \
                    system( "read -n 1 -s -p \"Press any key to continue...\"" );
                #elif _WIN32
                    system("pause");
                #endif
                break;
            }
            case 15:
                todo_list->emptyList();
                cout << termcolor::green << "Loading..." << endl;
                tempJS = db->fetchTasks();
                db->initLinkedList(json::parse(tempJS.text), todo_list, tskID);
                break;
            // god mode - deletes all the records
            case -3000:
                cpr::Response reqCode = db->emptyDB();
                auto reqRes = json::parse(reqCode.text);
                int responseCode = db->requestCheck(reqRes);
                todo_list->emptyList();
                tempJS = db->fetchTasks();
                db->initLinkedList(json::parse(tempJS.text), todo_list, tskID);
        }
    }
}

int main() {


    int command = NULL;
    LinkedList todo_list;

    DBHandle db("https://tasse-de-the-web-h5bxp.ondigitalocean.app/");
//    DBHandle db("http://localhost:8080/");

    thread t1{ [&]() {todo_list_thread(&todo_list, &command, &db); } };
    #ifdef _WIN32
    thread t2{ [&]() {check_alerts(&todo_list, &command); } };
    #endif
    t1.join();
    #ifdef _WIN32
    t2.join();
    #endif
    cout << "Thank you!" << endl;
}

