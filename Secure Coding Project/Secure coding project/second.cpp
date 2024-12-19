#include <iostream>
#include <memory>

class Node {
public:
    int data;
    std::unique_ptr<Node> next;

    Node(int value) : data(value), next(nullptr) {}
};

class LinkedList {
private:
    std::unique_ptr<Node> head;

public:
    void insert(int value) {
        // Manually create unique_ptr since make_unique isn't available
        std::unique_ptr<Node> newNode(new Node(value));
        if (!head) {
            head = std::move(newNode);
        } else {
            Node* temp = head.get();
            while (temp->next) {
                temp = temp->next.get();
            }
            temp->next = std::move(newNode);
        }
    }

    void display() const {
        Node* temp = head.get();
        while (temp) {
            std::cout << temp->data << " -> ";
            temp = temp->next.get();
        }
        std::cout << "nullptr\n";
    }
};

int main() {
    LinkedList list;
    list.insert(10);
    list.insert(20);
    list.insert(30);
    list.display();
    return 0;
}
