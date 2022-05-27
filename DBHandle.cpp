//
// Created by Ali Ayad on 12/03/2021.
//
#include<iostream>
#include "DBHandle.h"
#include <string>

DBHandle::DBHandle(std::string u){
    url = u;
};

json DBHandle::constructJSON(std::vector<std::vector<std::string>> arr) {
    json res;
    json subTask;
    if (!arr.empty()) {
        for (int i = 0; i < arr.size(); i++) {
            res[i]["taskPriority"] = arr[i][0];
            res[i]["tid"] = arr[i][1];
            res[i]["content"] = arr[i][2];
            res[i]["category"] = arr[i][3];
            res[i]["taskDay"] = arr[i][4];
            res[i]["taskMonth"] = arr[i][5];
            res[i]["taskYear"] = arr[i][6];
            res[i]["taskHour"] = arr[i][7];
            res[i]["taskMinute"] = arr[i][8];
            res[i]["taskSecond"] = arr[i][9];
            res[i]["taskChecked"] = arr[i][10];
            res[i]["taskSubs"] = subTask.parse(arr[i][11]);
        }
    }
    else{
        res = {};
    }
    return res;
}

cpr::Response DBHandle::fetchTasks() {
    std::string fetchURL = url + "tasks/all";
    cpr::AsyncResponse fr = cpr::GetAsync(cpr::Url(fetchURL));
    fr.wait(); // This waits until the request is complete
    cpr::Response r = fr.get(); // Since the request is complete, this returns immediately
//    std::cout << r.text << std::endl;
    return r;

//    std::string fetchURL = url + "tasks/all";
//    cpr::AsyncResponse fr = cpr::GetAsync(cpr::Url{fetchURL.c_str() });
//    std::cout << "fetchTasks Loading....." << std::endl;
//    cpr::Response r = fr.get();
//    std::cout << "Finished loading..." << r.text <<  std::endl;
////    cpr::Response r = cpr::Get(cpr::Url{fetchURL.c_str()});
////    json j = json::parse(r.text);
//    return r;
}

void DBHandle::create2DVector(std::vector<std::vector<std::string>>& data, std::vector<std::string>*a, std::vector<std::string> *b, std::vector<std::string> *c,
                  std::vector<std::string> *d, std::vector<std::string> *e){
    if(a != nullptr){
        data.push_back(a[0]);
    }
    if(b != nullptr){
        data.push_back(b[0]);
    }
    if(c != nullptr){
        data.push_back(c[0]);
    }
    if(d != nullptr){
        data.push_back(d[0]);
    }
    if(e != nullptr){
        data.push_back(e[0]);
    }
}

void DBHandle::printDB(){
    cpr::Response x = fetchTasks();
    json j = json::parse(x.text);
    for(auto & i : j){
        std::cout << i << std::endl;
    }
}

cpr::Response DBHandle::emptyDB() {
    std::string fetchURL = url + "tasks/delete";
    cpr::AsyncResponse fr = cpr::PostAsync(cpr::Url(fetchURL));
    fr.wait(); // This waits until the request is complete
    cpr::Response r = fr.get(); // Since the request is complete, this returns immediately
//    std::cout << r.text << std::endl;
    return r;
}

void DBHandle::printStatusCode(int x) {
    if(x == 200){
        cout << "Success!" << endl;
    }
    else
    {
        cout << "Error code: " << x << endl;
    }
}

cpr::Response DBHandle::insertTask(const json& data) {
    std::string fetchURL = url + "task/add";
    cpr::AsyncResponse fr = cpr::PostAsync(
            cpr::Url{fetchURL.c_str() },
            cpr::Body{data.dump()},
            cpr::Header{{"Content-Type", "application/json"}}
    );
    fr.wait();
    cpr::Response r = fr.get(); // Since the request is complete, this returns immediately
    return r;
//    cpr::Response r = Post(cpr::Url{fetchURL.c_str()},
//                           cpr::Body{data.dump()},
//                           cpr::Header{{"Content-Type", "application/json"}});



//    else{
//        std::cout << "An error occurred while inserting the data " << std::endl << std::endl << "For debugging: " << std::endl << "code: " << j["code"] << std::endl  << "response: " << j["response"] << std::endl <<  "body: " << j["body"] << std::endl;
//    }
}

void DBHandle::printVector(std::vector<std::vector<std::string>> x){
    for(int i = 0; i < x.size(); i++){
        for(int y = 0; y < x[i].size(); y++){
            std::cout << "Element [" << i << "][" << y <<  "]: " << x[i][y] << std::endl;
        }
    }
}

void DBHandle::printJSON(json x) {
    for(auto & i : x){
        std::cout << i << std::endl;
    }
}



void DBHandle::initLinkedList(json DBData, LinkedList* list, int& count) {
    int temp = 0;
    bool noSubs;
    vector<string> subtasks;
    if(!DBData.empty()){
        std::cout << "Populating " << DBData.size() << " records from the database!" << std::endl;
        for(auto & i : DBData){
            if (temp < i["tID"].get<int>()){
                temp = i["tID"].get<int>();
            }

            if(i["taskSubs"].size() < 0){
                noSubs = true;
            }

            else{
                noSubs = false;
            }



            list->add_node(i["priority"].get<int>(),
                  i["tID"].get<int>(),
                  i["task"].get<std::string>(),
                  i["category"].get<std::string>(),
                  i["taskDay"].get<int>(), ((i["taskMonth"].get<int>()) - 1), ((i["taskYear"].get<int>()) - 1900),
                  i["taskHour"].get<int>(),
                  i["taskMinute"].get<int>(),
                  i["taskChecked"].get<int>()
            );

            if(!noSubs){
                int id = i["tID"];
                for(auto & i: i["taskSubs"]){
                    list->add_subtask(id, i);
                }
            }

//                        list->add_node((int)i["priority"], (int)i["tID"], i["task"], i["category"], (int)i["taskDay"]
//            , ((int)i["taskMonth"]) - 1, ((int)i["taskYear"] - 1900), (int)i["taskHour"], (int)i["taskMinute"]);
        }

        temp++;
    }
    else{
        temp = 1;
    }
    count = temp;
}

std::string DBHandle::getURL(){
    return url;
}

int DBHandle::requestCheck(json req){
    if (req["code"] == 200 && req["response"] == "success") {
        return 200;
    }
    else{
        return req["code"];
    }
}