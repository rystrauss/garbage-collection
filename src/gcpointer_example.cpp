#include <iostream>
#include <utility>
#include <reference_counting.h>

using std::cout;
using std::endl;

/**
 * A simple node that contains data.
 *
 * @tparam T the type of data in the node
 */
template<typename T>
class Node {
public:
    GCPointer<Node> next;
    T data;

    explicit Node(T data, GCPointer<Node> next = GCPointer<Node>(nullptr)) : data{data}, next{std::move(next)} {
        cout << "Node constructed: " << data << endl;
    }

    ~Node() {
        cout << "Node destroyed: " << data << endl;
    }
};

/**
 * Simple linked list that uses GCPointers so that memory management does not need
 * to be a consideration in the implementation of the list.
 *
 * @tparam T the type of the elements in the list
 */
template<typename T>
class LinkedList {
private:

    GCPointer<Node<T>> head, tail;
    int size;

    GCPointer<Node<T>> get_node(int i) {
        GCPointer<Node<T>> cur = head;

        while (--i >= 0)
            cur = cur->next;

        return cur;
    }

public:

    LinkedList() : head{GCPointer<Node<T>>(nullptr)}, tail{GCPointer<Node<T>>(nullptr)}, size{0} {}

    void add(T element) {
        if (head.pointer() == nullptr) {
            head = new Node<T>(element);
            tail = head;
        } else {
            GCPointer<Node<T>> node{new Node<T>(element)};
            tail->next = node;
            tail = node;
        }
        ++size;
    }

    T remove(int i) {
        T data;

        if (i == 0) {
            data = head->data;
            head = head->next;
        } else {
            GCPointer<Node<T>> cur = get_node(i - 1);
            data = cur->next->data;
            cur->next = cur->next->next;
        }

        size--;
        return data;
    }

    void print() const {
        GCPointer<Node<T>> cur = head;
        cout << '[';
        while (cur->next.pointer() != nullptr) {
            cout << cur->data << ", ";
            cur = cur->next;
        }
        cout << cur->data << ']' << endl;
    }

};


int main() {
    // Simple linked list example
    // Removed node is automatically garbage collected
    // All nodes are freed at the end of the program
    LinkedList<int> list{};

    for (int i = 0; i < 5; ++i) {
        list.add(i);
    }

    list.print();
    list.remove(3);
    list.print();

    // Reference Cycle
    // Based on the example from https://www.educative.io/courses/a-quick-primer-on-garbage-collection-algorithms/jR8ml
    GCPointer<Node<char>> a{new Node<char>{'A', GCPointer<Node<char>>{new Node<char>{'B', GCPointer<Node<char>>{
            new Node<char>{'D', GCPointer<Node<char>>{new Node<char>{'E'}}}}}}}};
    GCPointer<Node<char>> c{new Node<char>{'C', a->next->next}};
    a->next->next->next->next = a->next;

    cout << "\nMain method has finished.\n" << endl;

    return 0;
}