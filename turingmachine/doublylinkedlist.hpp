//
// Created by Vily on 3.1.2024 г..
//

#ifndef TURING_MACHINE_DoublyLinkedList_HPP
#define TURING_MACHINE_DoublyLinkedList_HPP

template<typename T>
struct Node {
    T data;
    Node* next;
    Node* prev;

    Node(T val, Node* nxt = nullptr, Node* prv = nullptr) : data(val), next(nxt), prev(prv) {}
};

template<typename T>
class DoublyLinkedList {
public:
    Node<T>* head;
    Node<T>* tail;

    DoublyLinkedList() : head(nullptr), tail(nullptr) {}

    DoublyLinkedList(const DoublyLinkedList& other) : head(nullptr), tail(nullptr) {
        copyFrom(other);
    }

    ~DoublyLinkedList() {
        clear();
    }

    void insertBack(T val) {
        Node<T>* newNode = new Node<T>(val);
        if (!head) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }

    void clear() {
        Node<T>* current = head;
        while (current) {
            Node<T>* toDelete = current;
            current = current->next;
            delete toDelete;
        }
        head = tail = nullptr;
    }

private:
    void copyFrom(const DoublyLinkedList& other) {
        Node<T>* current = other.head;
        while (current) {
            insertBack(current->data);
            current = current->next;
        }
    }
};



#endif //TURING_MACHINE_DoublyLinkedList_HPP
