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
            cout << "Node constructed: " << data << endl;
        }

        ~Node() {
            cout << "Node destroyed: " << data << endl;
        }
    };

    GCPointer<Node> head, tail;
    int size;

    GCPointer<Node> get_node(int i) {
        GCPointer<Node> cur = head;

        while (--i >= 0)
            cur = cur->next;

        return cur;
    }

public:

    LinkedList() : head{GCPointer<Node>(nullptr)}, tail{GCPointer<Node>(nullptr)}, size{0} {}

    void add(T element) {
        if (head.pointer() == nullptr) {
            head = new Node(element);
            tail = head;
        } else {
            GCPointer<Node> node{new Node(element)};
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
            GCPointer<Node> cur = get_node(i - 1);
            data = cur->next->data;
            cur->next = cur->next->next;
        }

        size--;
        return data;
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
    list.remove(3);
    list.print();

    return 0;
}