#include <iostream>
#include <utility>
#include <reference_counting.h>

using std::cout;
using std::endl;

template<typename T>
class LinkedList {
private:

    class Node {
    public:
        GCPointer<Node> next;
        T data;

        explicit Node(T data, GCPointer<Node> next = GCPointer<Node>(nullptr)) : data{data}, next{std::move(next)} {
            cout << "Node constructed" << endl;
        }

        ~Node() {
            cout << "Node destroyed" << endl;
        }
    };

    GCPointer<Node> head, tail;

public:

    LinkedList() : head{GCPointer<Node>(nullptr)}, tail{GCPointer<Node>(nullptr)} {}

    void add(T element) {
        if (head.pointer() == nullptr) {
            head = new Node(element);
            tail = head;
        } else {
            Node *node = new Node(element);
            tail->next = node;
            tail = node;
        }
    }

    void print() const {
        GCPointer<Node> cur = head;
        cout << '[';
        while (cur->next.pointer() != nullptr) {
            cout << cur->data << ", ";
            cur = cur->next;
        }
        cout << cur->data << ']' << endl;
    }

};


int main() {
    LinkedList<int> list{};

    for (int i = 0; i < 5; ++i) {
        list.add(i);
    }

    list.print();

    return 0;
}