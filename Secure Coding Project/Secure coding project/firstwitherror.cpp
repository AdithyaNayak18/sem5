#include <iostream>

class Node {
public:
    int data;
    Node* next;

    Node(int value) : data(value), next(nullptr) {}
};

class LinkedList {
private:
    Node* head;

public:
    LinkedList() : head(nullptr) {}

    ~LinkedList() {
        clear();
    }

    // Insert a node at the end
    void insert(int value) {
        Node* newNode = new Node(value);
        if (!head) {
            head = newNode;
        } else {
            Node* temp = head;
            while (temp->next) {
                temp = temp->next;
            }
            temp->next = newNode;
        }
    }

    // Delete a node with a specific value (intentionally introduces a dangling pointer)
    void deleteValueWithBug(int value) {
        if (!head) return;

        if (head->data == value) {
            Node* temp = head;
            head = head->next;

            // Delete the node
            delete temp;

            // Debugging: Access the dangling pointer
            std::cout << "DEBUG: Accessing dangling pointer (head node): " << temp->data << std::endl; // Bug!
            return;
        }

        Node* current = head;
        while (current->next && current->next->data != value) {
            current = current->next;
        }

        if (current->next) {
            Node* temp = current->next;
            current->next = temp->next;

            // Delete the node
            delete temp;

            // Debugging: Access the dangling pointer
            std::cout << "DEBUG: Accessing dangling pointer (middle node): " << temp->data << std::endl; // Bug!
        }
    }

    // Clear the entire linked list
    void clear() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }

    // Display the linked list
    void display() const {
        Node* temp = head;
        while (temp) {
            std::cout << temp->data << " -> ";
            temp = temp->next;
        }
        std::cout << "nullptr\n";
    }
};

int main() {
    LinkedList list;

    // Insert some elements
    list.insert(10);
    list.insert(20);
    list.insert(30);
    list.display();

    // Delete a node and demonstrate the dangling pointer
    list.deleteValueWithBug(20);

    // Clear the list
    list.clear();
    list.display();

    return 0;
}
