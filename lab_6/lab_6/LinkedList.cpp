#include "LinkedList.h"
#include <iostream>
#include <string> 



    LinkedList::LinkedList() : m_head(NULL), m_size(0) {
	}

    void LinkedList::append(const std::string& val) {
       
        Node* node = new Node(val);      
        node->m_next = m_head;
        m_head = node;
        m_size++;
    }

    void LinkedList::remove() {
        if (m_head) { 
            Node* newHead = m_head->m_next;
            delete m_head;
            m_head = newHead;
            m_size--;
        }
    }

    bool LinkedList::checkSize() {
        if (m_size < MAX_LINKED_LIST_SIZE) {
            return true;
        }
        return false;
    }

    void LinkedList::writeAndClearList(int fileNum) {
        ofstream out("log" + std::to_string(fileNum) + ".txt");
        std::vector<std::string> v;
        while (m_head) {           
            v.push_back(m_head->m_val);
            remove();
        }
        std::reverse(v.begin(), v.end());
        for (std::string el: v) {
            out << el << "\n";
        }
        out.close();
    }

    Node* LinkedList::getHead() {
        return m_head;
    }