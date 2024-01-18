#ifndef TURING_MACHINE_DoublyLinkedList_HPP
#define TURING_MACHINE_DoublyLinkedList_HPP
#include<string>
#include<iostream>
#include<vector>

template<typename T>
struct LinkedNode{
    T value;
    LinkedNode* next;
    LinkedNode* prev;

    LinkedNode(T _value, LinkedNode* _next = nullptr, LinkedNode* _prev = nullptr):
            value(_value), next(_next), prev(_prev){}
};


template<typename T>
class DoublyLinkedList{
private:

    LinkedNode<T>* head;
    LinkedNode<T>* tail;

public:

    DoublyLinkedList();
    DoublyLinkedList(const DoublyLinkedList& other);
    DoublyLinkedList& operator=(const DoublyLinkedList& other);
    ~DoublyLinkedList();

    bool empty() const;

    void push_back(const T&);
    void push_front(const T&);

    void pop_back();
    void pop_front();

    //access methods O(1)
    T& front();
    const T& front() const;

    T& back();
    const T& back() const;

    void free();

public:
    class Iterator{
    private:
        friend class DoublyLinkedList;

        LinkedNode<T>* currentNode;

    public:
        bool valid(){
            return currentNode != nullptr;
        }

        T& operator* (){
            return currentNode->value;
        }

        const T& operator* () const{
            return currentNode->value;
        }

        Iterator& operator++(){
            if(!valid()){
                return *this;
            }

            currentNode = currentNode->next;
            return *this;
        }

        Iterator operator++(int){
            if(!valid()){
                return *this;
            }

            Iterator toStore = *this;
            ++(*this);
            return toStore;
        }

        Iterator& operator--(){
            if(!valid()){
                return *this;
            }

            currentNode = currentNode->prev;
            return *this;
        }

        Iterator operator--(int){
            if(!valid()){
                return *this;
            }

            Iterator toStore = *this
                    --(*this);
            return toStore;
        }

        bool operator == (const Iterator& other) const{
            return currentNode == other.currentNode;
        }

        bool operator !=(const Iterator& other) const{
            return !(*this == other);
        }

        Iterator(LinkedNode<T>* _currentNode = nullptr): currentNode(_currentNode){}
    };

    //Iterators
    inline Iterator begin(){
        return Iterator(head);
    }

    inline Iterator begin() const{
        return Iterator(head);
    }

    inline Iterator end(){
        return Iterator();
    }

    inline Iterator end() const{
        return Iterator();
    }

    inline Iterator last(){
        return Iterator(tail);
    }

    inline Iterator last() const{
        return Iterator(tail);
    }


    void push_after(Iterator, const T&);
    void push_before(Iterator, const T&);
    void delete_before(Iterator);
    void delete_after(Iterator);
    void delete_at(Iterator);

    //custom
    DoublyLinkedList makeList(const std::vector<T>&);

private:
    void copyFrom(const DoublyLinkedList& other);
};

template<typename T>
void DoublyLinkedList<T>::free() {
    while (head != nullptr) {
        LinkedNode<T>* temp = head;
        head = head->next;
        delete temp;
    }
    tail = nullptr;
}

template<typename T>
void DoublyLinkedList<T>::copyFrom(const DoublyLinkedList<T>& other) {
    head = tail = nullptr;
    for (LinkedNode<T>* cur = other.head; cur != nullptr; cur = cur->next) {
        push_back(cur->value);
    }
}

template<typename T>
DoublyLinkedList<T>::DoublyLinkedList(){
    head = tail = nullptr;
}

template<typename T>
DoublyLinkedList<T>::DoublyLinkedList(const DoublyLinkedList<T>& other){
    copyFrom(other);
}

template<typename T>
DoublyLinkedList<T>& DoublyLinkedList<T>::operator=(const DoublyLinkedList<T>& other){
    if(this != &other){
        free();
        copyFrom(other);
    }
    return *this;
}

template<typename T>
DoublyLinkedList<T>::~DoublyLinkedList(){
    free();
}

template<typename T>
T& DoublyLinkedList<T>::front(){
    if(empty()){
        throw std::runtime_error("Attempt to access element from an empty list!");
    }
    return head->value;
}

template<typename T>
const T& DoublyLinkedList<T>::front() const{
    if(empty()){
        throw std::runtime_error("Attempt to access element from an empty list!");
    }
    return head->value;
}

template<typename T>
T& DoublyLinkedList<T>::back(){
    if(empty()){
        throw std::runtime_error("Attempt to access element from an empty list!");
    }
    return tail->value;
}

template<typename T>
const T& DoublyLinkedList<T>::back() const{
    if(empty()){
        throw std::runtime_error("Attempt to access element from an empty list!");
    }
    return tail->value;
}

template<typename T>
bool DoublyLinkedList<T>::empty() const{
    return head == nullptr;
}
template<typename T>
void DoublyLinkedList<T>::push_back(const T& value) {
    if (empty()) {
        head = tail = new LinkedNode<T>(value);
    } else {
        tail->next = new LinkedNode<T>(value, nullptr, tail);
        tail = tail->next;
    }
}

template<typename T>
void DoublyLinkedList<T>::push_front(const T& value) {
    if (empty()) {
        head = tail = new LinkedNode<T>(value);
    } else {
        head->prev = new LinkedNode<T>(value, head, nullptr);
        head = head->prev;
    }
}

template<typename T>
void DoublyLinkedList<T>::pop_back() {
    if (empty()) {
        throw std::runtime_error("Attempt to pop from an empty list!");
    }

    LinkedNode<T>* toDelete = tail;
    tail = tail->prev;

    if (tail) {
        tail->next = nullptr;
    } else {
        head = nullptr;
    }

    delete toDelete;
}

template<typename T>
void DoublyLinkedList<T>::pop_front() {
    if (empty()) {
        throw std::runtime_error("Attempt to pop from an empty list!");
    }

    LinkedNode<T>* toDelete = head;
    head = head->next;

    if (head) {
        head->prev = nullptr;
    } else {
        tail = nullptr;
    }

    delete toDelete;
}


template<typename T>
void DoublyLinkedList<T>::push_after(Iterator it, const T& value) {
    if (!it.valid()) throw std::runtime_error("Invalid iterator");

    LinkedNode<T>* newNode = new LinkedNode<T>(value, it.currentNode->next, it.currentNode);

    if (it.currentNode->next) {
        it.currentNode->next->prev = newNode;
    } else {
        tail = newNode;
    }

    it.currentNode->next = newNode;
}

template<typename T>
void DoublyLinkedList<T>::push_before(Iterator it, const T& value) {
    if (!it.valid()) throw std::runtime_error("Invalid iterator");

    if (it.currentNode == head) {
        push_front(value);
        return;
    }

    Iterator prevIt = --Iterator(it);
    push_after(prevIt, value);
}

template<typename T>
void DoublyLinkedList<T>::delete_at(Iterator it) {
    if (!it.valid()) throw std::runtime_error("Invalid iterator");

    if (it.currentNode == head) {
        pop_front();
        return;
    }

    if (it.currentNode == tail) {
        pop_back();
        return;
    }

    it.currentNode->prev->next = it.currentNode->next;
    it.currentNode->next->prev = it.currentNode->prev;

    delete it.currentNode;
}

template<typename T>
void DoublyLinkedList<T>::delete_before(Iterator it) {
    if (!it.valid() || it.currentNode == head) throw std::runtime_error("Invalid operation");

    delete_at(--it);
}

template<typename T>
void DoublyLinkedList<T>::delete_after(Iterator it) {
    if (!it.valid() || it.currentNode == tail) throw std::runtime_error("Invalid operation");

    delete_at(++it);
}

template<typename T>
DoublyLinkedList<T> DoublyLinkedList<T>::makeList(const std::vector<T>& container) {
    DoublyLinkedList<T> list;
    for (const T& element : container) {
        list.push_back(element);
    }
    return list;
}


#endif //TURING_MACHINE_DoublyLinkedList_HPP
