#pragma once

#include <iostream>

// Node class template
template <class T>
class Node {
public:
    T data;
    Node<T>* next;

    // Constructor to initialize the node with data
    Node(T value) : data(value), next(nullptr) {}
};

// LinkedList class template
template <class T>
class LinkedList {
private:
    Node<T>* head;

    // Helper function to copy list
    void copyList(const LinkedList<T>& other) {
        Node<T>* temp = other.head;
        while (temp != nullptr) {
            this->append(temp->data);
            temp = temp->next;
        }
    }


public:
    // Constructor to initialize the linked list
    LinkedList() : head(nullptr) {}

    // Copy constructor
    LinkedList(const LinkedList<T>& other) : head(nullptr) {
        copyList(other);
    }

    // Destructor to free memory
    ~LinkedList() {
        Node<T>* current = head;
        while (current != nullptr) {
            Node<T>* nextNode = current->next;

            // Special handling for pointers
            delete current->data;  // Delete the object pointed to by data
            delete current;  // Delete the node itself
            current = nextNode;
        }
        head = nullptr;
    }

    // Function to add a node to the end of the list
    void append(T value);

    // Function to delete a node with a specific value
    void remove(T value);

    // Overloaded += operator to append an element
    LinkedList<T>& operator+=(const T& value) {
        append(value);
        return *this;
    }

    Node<T>* getNode(int index) const;

    Node<T>* getHead() const;

    void display() const;

    // Overloaded = operator for assigning one list to another
    LinkedList<T>& operator=(const LinkedList<T>& other) {
        if (this != &other) {
            // Clear the current list
            Node<T>* current = head;
            while (current != nullptr) {
                Node<T>* nextNode = current->next;
                delete current;
                current = nextNode;
            }
            head = nullptr;

            // Copy elements from the other list
            copyList(other);
        }
        return *this;
    }

    friend std::ostream& operator<<(std::ostream& os, const LinkedList<T>& list) {
        Node<T>* temp = list.head;
        while (temp != nullptr) {
            os << *(temp->data);  // Dereference the pointer to access the object
            os << " -> ";
            temp = temp->next;
        }
        os << "nullptr";
        return os;
    }

};


template<class T>
void LinkedList<T>::append(T value)
{
    Node<T>* newNode = new Node<T>(value);
    if (head == nullptr) {
        head = newNode;
    }
    else {
        Node<T>* temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}


template <class T>
void LinkedList<T>::remove(T value) {
    if (head == nullptr) return;

    if (head->data == value) {
        Node<T>* temp = head;
        head = head->next;
        delete temp;
        return;
    }

    Node<T>* current = head;
    Node<T>* prev = nullptr;
    while (current != nullptr && current->data != value) {
        prev = current;
        current = current->next;
    }

    if (current == nullptr) return; // Value not found

    prev->next = current->next;
    delete current;
}

template <class T>
Node<T>* LinkedList<T>::getNode(int index) const {
    Node<T>* temp = head;
    int currentIndex = 0;
    while (temp != nullptr) {
        if (currentIndex == index) {
            return temp;
        }
        temp = temp->next;
        currentIndex++;
    }
    return nullptr;  // Return nullptr if index is out of bounds
}

template<class T>
inline Node<T>* LinkedList<T>::getHead() const
{
    return head;
}

template <class T>
void LinkedList<T>::display() const {
    Node<T>* temp = head;
    int index = 0;
    while (temp != nullptr) {
        std::cout << index++ << ": " << *(temp->data) << std::endl;
        temp = temp->next;
    }
}
