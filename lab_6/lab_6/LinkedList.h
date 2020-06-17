#pragma once

#include <fstream>
#include <string>
#include <vector>

using namespace std;

const int MAX_LINKED_LIST_SIZE = 10000;

struct Node 
{
    Node() : m_next(NULL) { }

    Node(const std::string& val) : m_val(val), m_next(NULL) { }

    // «начение узла
    std::string m_val;

    // ”казатель на следующий узел
    Node* m_next;
};

class LinkedList
{
public:
    LinkedList();
    void append(const std::string& val);
    void remove();
    bool checkSize();
    void writeAndClearList(int fileNum);
    Node* getHead();
    int getSize();
    bool isEnd();
    void itIsEnd();
    
private:
    Node* m_head;
    int m_size;
    bool m_end;
};
