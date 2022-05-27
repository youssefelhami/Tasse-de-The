#include "Node.h"
#include <iostream>
//#include <Windows.h>
#include <vector>
#pragma once
class LinkedList
{
public:
    // constructor
    LinkedList();
    //members
    // public
    void add_node(int, int, std::string, std::string, int, int , int , int , int, bool = false);

    void edit_node(int, int, std::string, std::string, int , int, int, int , int);

    void push_node(int, std::string);

    void complete_node(int);

    string display_list(int,string);

    bool insert_node(int, const int&);

    void emptyList();

    void delete_index(const int&);

    node* pop_node();
    std::vector<std::vector<std::string>> exportNode(int);
    node* search_with_value(const int&);
    void delete_ID(const int ID);
    void node_swap(node* left, node* right);
    void sort_time(int high_low);
    void swap_index(int i, int j);
    node* find_index(int i);
    int smaller(node* temp1, node* temp2);
    int n_nodes();
    void add_subtask(int, string);
    void remove_subtask(int, int);
    std::string show_subtasks(int);
    void sort_priority(int high_low);
    bool check_notifications();
    string vectorStringify(vector<string>);
    //friend std::ostream& operator<<(std::ostream& out, LinkedList);
    // private
private:
    node* head;
    node* tail;
    //methods
    // public
};
