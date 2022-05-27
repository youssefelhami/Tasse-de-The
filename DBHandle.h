//
// Created by Ali Ayad on 12/03/2021.
//

#pragma once

#include <string>
#include <vector>
#include <cpr/cpr.h>
#include <nlohmann/json.hpp>
#include "LinkedList.h"

using json = nlohmann::json;

class DBHandle {

public:
    DBHandle(std::string url);
    cpr::Response fetchTasks();
    void printDB();
    cpr::Response emptyDB();
    int requestCheck(json);
    void printStatusCode(int);
    cpr::Response insertTask(const json&);
    static void create2DVector(std::vector<std::vector<std::string>>& data, std::vector<std::string>*a = nullptr, std::vector<std::string> *b = nullptr, std::vector<std::string> *c = nullptr,
                               std::vector<std::string> *d = nullptr, std::vector<std::string> *e = nullptr);
//    static void create2DVector(
//            std::vector<std::vector<std::string>>&, std::vector<std::string>*, std::vector<std::string> *,
//            std::vector<std::string> *,std::vector<std::string> *, std::vector<std::string> *);
    json constructJSON(std::vector<std::vector<std::string>>);
    std::string getURL();
    static void printJSON(json);
    static void initLinkedList(json, LinkedList*, int&);
    static void printVector(std::vector<std::vector<std::string>>);
private:
    std::string url;

};