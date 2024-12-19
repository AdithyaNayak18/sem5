#include <iostream>
#include <memory> // For smart pointers in C++

class Node {
public:
    int data;
    Node* next;

    Node(int value) : data(value), next(nullptr) {}
};

class LinkedList {
private:
    Node* head;

    // Utility function to delete a node safely
    void deleteNodeSafely(Node*& node) {
        if (node) {
            delete node;
            node = nullptr; // Avoid dangling pointer
        }
    }

public:
    LinkedList() : head(nullptr) {}

    ~LinkedList() {
        clear(); // Free all allocated memory
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

    // Delete a node with a specific value
    void deleteValue(int value) {
        if (!head) {
            std::cerr << "List is empty. Nothing to delete.\n";
            return;
        }

        if (head->data == value) {
            Node* temp = head;
            head = head->next;
            deleteNodeSafely(temp);
            return;
        }

        Node* current = head;
        Node* prev = nullptr;

        while (current && current->data != value) {
            prev = current;
            current = current->next;
        }

        if (current) {
            prev->next = current->next;
            deleteNodeSafely(current);
        } else {
            std::cerr << "Value not found in the list.\n";
        }
    }

    // Clear the entire linked list
    void clear() {
        Node* current = head;
        while (current) {
            Node* temp = current;
            current = current->next;
            deleteNodeSafely(temp);
        }
        head = nullptr; // Set head to nullptr after clearing
    }

    // Display the linked list
    void display() const {
        if (!head) {
            std::cout << "List is empty.\n";
            return;
        }
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

    // Inserting elements
    list.insert(10);
    list.insert(20);
    list.insert(30);
    list.display();

    // Deleting a node
    list.deleteValue(20);
    list.display();

    // Clearing the list
    list.clear();
    list.display();

    return 0;
}
